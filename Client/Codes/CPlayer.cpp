#include "stdafx.h"
#include "CPlayer.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Free();
}

HRESULT CPlayer::Ready_GameObj(float fStartX, float fStartY)
{
	CGameObj::Ready_GameObj();

	m_tInfo.x = fStartX;
	m_tInfo.y = fStartY /*+ 15*/;
	m_tInfo.cx = 100.f;
	m_tInfo.cy = 100.f;

	m_bRight = true;
	m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Idle_Head_R");
	m_iCheck = IDLE;

	TCHAR m_szData01[255];
	GetPrivateProfileString(_T("Jump"), _T("Accel"), NULL, m_szData01, 255, _T("../../Binary/Data/DebugData.ini"));
	m_fJumpAccel = (float)_tstof(m_szData01);
	GetPrivateProfileString(_T("Jump"), _T("Power"), NULL, m_szData01, 255, _T("../../Binary/Data/DebugData.ini"));
	m_fJumpPower = (float)_tstof(m_szData01);
	
	m_fGravityAccel = 1000.f;
	m_fGravityPower = 0.f;

	CScrollManager::SetScrollValue(m_tInfo.x - 640.f, m_tInfo.y - 500.f);

	return NOERROR;
}

int CPlayer::Update_GameObj(const float& fTimeDelta)
{
	if (Update_State(fTimeDelta) == OBJ_DEAD)
		return OBJ_DEAD;

	m_pAnimation->Update_Position(m_tInfo.x, m_tInfo.y);

	if (m_bGravity)
	{
		if (!m_bJump)
		{
			m_tInfo.y -= m_fGravityPower * fTimeDelta;
			CScrollManager::SetScrollPos(0, -m_fGravityPower * fTimeDelta);
			m_fGravityPower -= m_fGravityAccel * fTimeDelta;
		}
	}
	else
		m_fGravityPower = 0.f;

	Update_Collision();						//  이번 프레임꺼

	m_pAnimation->Update_GameObj(fTimeDelta);
	CGameObj::Update_Rect();
	m_pRenderMgr->AddBack_RenderList(this);

	if (m_tInfo.y > 1500.f)
	{
		CSceneManager::GetInstance()->Get_ChangeScene() = TRUE;
		CSceneManager::GetInstance()->Get_NextScene() = CSceneManager::SCENE_GAMEOVER0;
	}

	return 0;
}

void CPlayer::Render_GameObj(HDC hDC)
{
	m_pAnimation->Render_GameObj(hDC);

	HPEN			m_hPen = CreatePen(PS_SOLID, 1, RGB(m_tColor.r, m_tColor.g, m_tColor.b));
	HGDIOBJ	m_hOldPen = SelectObject(hDC, m_hPen);
	HBRUSH		m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HGDIOBJ	m_hOldBrush = SelectObject(hDC, m_hBrush);
	Rectangle(hDC, (int)m_tRect.left - (int)CScrollManager::GetScrollPos(0)
								, (int)m_tRect.top - (int)CScrollManager::GetScrollPos(1)
								, (int)m_tRect.right - (int)CScrollManager::GetScrollPos(0)
								, (int)m_tRect.bottom - (int)CScrollManager::GetScrollPos(1));
	SelectObject(hDC, m_hOldPen);
	SelectObject(hDC, m_hOldBrush);
	DeleteObject(m_hBrush);
	DeleteObject(m_hPen);
}

int CPlayer::Update_Collision()
{
	bool bGravity = true;
	m_pAnimation->Update_Position(m_tInfo.x, m_tInfo.y);

	for (auto pCollRect : m_pGameMgr->Get_MapCollider())
	{
		RECT tDstRect = pCollRect->tRect;					// 맵에 있는 렉트
		RECT tSrcRect = m_pAnimation->Get_CollRect();		// 플레이어 렉트
		RECT tTempRect = {};								// 겹친 렉트

		if (pCollRect->iType == COLL_ALL)
		{
			if (IntersectRect(&tTempRect, &tSrcRect, &tDstRect))
			{
				bGravity = false;

				float fDstX = (float)tDstRect.right - tDstRect.left;
				float fDstY = (float)tDstRect.bottom - tDstRect.top;

				float fMoveX = (float)tTempRect.right - tTempRect.left;
				float fMoveY = (float)tTempRect.bottom - tTempRect.top;

				//위 아래 충돌
				if (fMoveX > fMoveY)
				{
					if (m_tInfo.y < (tDstRect.bottom + tDstRect.top) / 2)
					{
						// 위
						if (m_iCheck == FALL)
						{
							Change_State(IDLE);
							Restore_Jump();
						}
						m_tInfo.y -= fMoveY;
						CScrollManager::SetScrollPos(0, -fMoveY);
					}
					else
					{
						// 아래
						m_tInfo.y += fMoveY;
						CScrollManager::SetScrollPos(0, fMoveY);
					}
				}
				//오른쪽 왼쪽 충돌
				else
				{
					if (m_tInfo.x < (tDstRect.right + tDstRect.left) / 2)
					{
						m_tInfo.x -= fMoveX;
						CScrollManager::SetScrollPos(-fMoveX, 0);
					}
					else
					{
						m_tInfo.x += fMoveX;
						CScrollManager::SetScrollPos(fMoveX, 0);
					}
				}
				//cout << "이이이잉" << endl;
			}
		}
		else if (pCollRect->iType == COLL_INTERACT)
		{
			if (IntersectRect(&tTempRect, &tSrcRect, &tDstRect))
			{
				// 상호작용
				//cout << "호오오옹" << endl;
			}
		}
	}

	m_bGravity = bGravity;

	m_pAnimation->Update_Position(m_tInfo.x, m_tInfo.y);

	return bGravity;
}

int CPlayer::Update_State(const float& fTimeDelta)
{
	/*
	내가 고친것들 
	1. ChangeState 함수로 적용 (자세한건 해당함수 ㄱ)
	2. 왜 점프중일때 왼쪽 오른쪽 적용 안되도록했긔? m_bRight값 업데이트 해주는거 넣음
	3. 왼쪽 오른쪽 애니메이션 바뀔때 방향에 따라 한번만 바뀌게 (find 연산 많이듬)
	4. FALL 상태 따로 추가해둠 (애니메이션 바꿔주는거 땜시)

	+) 상태 업데이트 전에 왼쪽 오른쪽 먼저 바꿔주셈
		ChangeState 보면 알겠지만 왼쪽 오른쪽 따라 애니메이션 바뀌는거 다르게 해둠

	그래도 로직 잘 짜놓으셨네요 굳
	-최-
	*/

	switch (m_iCheck)
	{
	case IDLE:
		if (m_pKeyMgr->KeyPressing(KEY_LEFT))
		{
			m_bRight = false;
			Change_State(WALK);
		}
		if (m_pKeyMgr->KeyPressing(KEY_RIGHT))
		{
			m_bRight = true;
			Change_State(WALK);
		}
		if (m_pKeyMgr->KeyDown(KEY_PLAYERJUMP))
		{
			Change_State(JUMP);
		}
		if (m_pKeyMgr->KeyDown(KEY_PLAYERDASH))
		{
			Change_State(DASH);
		}
		if (m_pKeyMgr->KeyDown(KEY_PLAYERATTACK))
		{
			Change_State(ATTACK);
		}
		if (m_pKeyMgr->KeyDown(KEY_PLAYERSKILL1))
		{
			Change_State(SKILL1);
		}
		if (m_pKeyMgr->KeyDown(KEY_PLAYERSKILL2))
		{
			Change_State(SKILL2);
		}
		break;

	case WALK:
		if (!m_bRight)
		{
			if(m_bRight)
				m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Walk_Head_L");

			m_tInfo.x -= fTimeDelta * m_fSpeed;
			CScrollManager::SetScrollPos(-fTimeDelta * m_fSpeed, 0);
			if (m_pKeyMgr->KeyUp(KEY_LEFT))
			{
				m_bRight = FALSE;
				Change_State(IDLE);
			}
			if (m_pKeyMgr->KeyDown(KEY_PLAYERJUMP))
			{
				m_bRight = FALSE;
				Change_State(JUMP);
			}
			if (m_pKeyMgr->KeyDown(KEY_PLAYERSKILL1))
			{
				m_bRight = FALSE;
				Change_State(SKILL1);
			}
			if (m_pKeyMgr->KeyDown(KEY_PLAYERSKILL2))
			{
				m_bRight = FALSE;
				Change_State(SKILL2);
			}
			if (m_pKeyMgr->KeyDown(KEY_PLAYERATTACK))
			{
				m_bRight = FALSE;
				Change_State(ATTACK);
			}
		}
		else
		{
			if (!m_bRight)
				m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Walk_Head_R");

			m_tInfo.x += fTimeDelta * m_fSpeed;
			CScrollManager::SetScrollPos(fTimeDelta * m_fSpeed, 0);
			if (m_pKeyMgr->KeyUp(KEY_RIGHT))
			{
				m_bRight = true;
				Change_State(IDLE);
			}
			if (m_pKeyMgr->KeyDown(KEY_PLAYERJUMP))
			{
				m_bRight = TRUE;
				Change_State(JUMP);
			}
			if (m_pKeyMgr->KeyDown(KEY_PLAYERSKILL1))
			{
				m_bRight = TRUE;
				Change_State(SKILL1);
			}
			if (m_pKeyMgr->KeyDown(KEY_PLAYERSKILL2))
			{
				m_bRight = TRUE;
				Change_State(SKILL2);
			}
			if (m_pKeyMgr->KeyDown(KEY_PLAYERATTACK))
			{
				m_bRight = TRUE;
				Change_State(ATTACK);
			}
		}
		break;

	case JUMP:
		m_bJump = true;
		if (m_fJumpPower >= 0)
		{
			if (m_pKeyMgr->KeyPressing(KEY_LEFT))
			{
				if(!m_bRight)
					m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Jump_Head_L");
				m_bRight = false;
				m_tInfo.x -= fTimeDelta * m_fSpeed;
				CScrollManager::SetScrollPos(-fTimeDelta * m_fSpeed, 0);
			}
			if (m_pKeyMgr->KeyPressing(KEY_RIGHT))
			{
				if(m_bRight)
					m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Jump_Head_R");
				m_bRight = true;
				m_tInfo.x += fTimeDelta * m_fSpeed;
				CScrollManager::SetScrollPos(fTimeDelta * m_fSpeed, 0);
			}
		}
		else
			Change_State(FALL);

		m_tInfo.y -= m_fJumpPower * fTimeDelta;
		CScrollManager::SetScrollPos(0, -m_fJumpPower * fTimeDelta);
		m_fJumpPower -= m_fJumpAccel * fTimeDelta;

		if (m_pKeyMgr->KeyDown(KEY_PLAYERJUMP))
		{
			Change_State(DJUMP);
			Restore_Jump();
		}
		if (m_pKeyMgr->KeyDown(KEY_PLAYERATTACK))
		{
			Change_State(JMPATTACK);
		}
		break;

	case DJUMP:
		m_iDJump = 1;
		m_bJump = true;
		if (m_fJumpPower >= 0)
		{
			if (!m_bRight) m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Jump_Head_L");
			else m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Jump_Head_R");
			if (m_pKeyMgr->KeyPressing(KEY_LEFT))
			{
				if(m_bRight)
					m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Jump_Head_L");
				m_bRight = false;
				m_tInfo.x -= fTimeDelta * m_fSpeed;
				CScrollManager::SetScrollPos(-fTimeDelta * m_fSpeed, 0);
			}
			if (m_pKeyMgr->KeyPressing(KEY_RIGHT))
			{
				if(!m_bRight)	
					m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Jump_Head_R");
				m_bRight = true;
				m_tInfo.x += fTimeDelta * m_fSpeed;
				CScrollManager::SetScrollPos(fTimeDelta * m_fSpeed, 0);
			}
		}
		else
			Change_State(FALL);

		m_tInfo.y -= m_fJumpPower * fTimeDelta;
		CScrollManager::SetScrollPos(0, -m_fJumpPower * fTimeDelta);
		m_fJumpPower -= m_fJumpAccel * fTimeDelta;

		if (m_pKeyMgr->KeyDown(KEY_PLAYERATTACK))
		{
			Change_State(JMPATTACK);
		}
		break;

	case FALL:
		if (m_pKeyMgr->KeyPressing(KEY_LEFT))
		{
			if(m_bRight)
				m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Fall_Head_L");
			m_bRight = false;
			m_tInfo.x -= fTimeDelta * m_fSpeed;
			CScrollManager::SetScrollPos(-fTimeDelta * m_fSpeed, 0);
		}
		if (m_pKeyMgr->KeyPressing(KEY_RIGHT))
		{
			if(!m_bRight)
				m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Fall_Head_R");
			m_bRight = true;
			m_tInfo.x += fTimeDelta * m_fSpeed;
			CScrollManager::SetScrollPos(fTimeDelta * m_fSpeed, 0);
		}
		if (m_pKeyMgr->KeyDown(KEY_PLAYERJUMP))
		{
			if (m_iDJump == 0)
			{
				Restore_Jump();
				Change_State(DJUMP);
			}
		}

		m_tInfo.y -= m_fJumpPower * fTimeDelta;
		CScrollManager::SetScrollPos(0, -m_fJumpPower * fTimeDelta);
		m_fJumpPower -= m_fJumpAccel * fTimeDelta;

		break;

	case ATTACK:
		if (m_pAnimation->Check_FrameEnd())
		{
			Change_State(IDLE);
		}
		break;

	case JMPATTACK:
		if (m_pAnimation->Check_FrameEnd())
		{
			Change_State(DJUMP);
		}
		break;

	case DASH:
		if (m_bRight)
		{
			if(!m_bRight)
				m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Dash_Head_R");
			m_tInfo.x += fTimeDelta * m_fSpeed * 15;
			CScrollManager::SetScrollPos(fTimeDelta * m_fSpeed * 15, 0);
		}
		else
		{
			if(m_bRight)
				m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Dash_Head_L");
			m_tInfo.x -= fTimeDelta * m_fSpeed * 15;
			CScrollManager::SetScrollPos(-fTimeDelta * m_fSpeed * 15, 0);
		}

		if (m_pAnimation->Check_FrameEnd())
		{
			Change_State(IDLE);
		}
		break;

	case SKILL1:
		if (m_pAnimation->Check_FrameEnd())
		{
			Change_State(IDLE);
		}
		break;
	case SKILL2:
		if (m_pAnimation->Check_FrameEnd())
		{
			Change_State(IDLE);
		}
		break;
	}

	return 0;
}

void CPlayer::Restore_Jump()
{
	// 착지를 했을때에 대한 값 변경
	m_bJump = false;
	m_iDJump = 0;
	TCHAR m_szData01[255];
	GetPrivateProfileString(_T("Jump"), _T("Accel"), NULL, m_szData01, 255, _T("../../Binary/Data/DebugData.ini"));
	m_fJumpAccel = (float)_tstof(m_szData01);
	GetPrivateProfileString(_T("Jump"), _T("Power"), NULL, m_szData01, 255, _T("../../Binary/Data/DebugData.ini"));
	m_fJumpPower = (float)_tstof(m_szData01);
}

void CPlayer::Change_State(PLAYERSTATUS eState)
{
	// 바꾸려는 상태가 현상태와 같다면 return
	if (m_iCheck == eState)
		return;

	RECT tOriginRect = m_pAnimation->Get_OriginCollRect();

	switch (eState)
	{
	case IDLE:
		if (m_bRight) m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Idle_Head_R");
		else m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Idle_Head_L");
		break;
	case WALK:
		if(m_bRight)	m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Walk_Head_R");
		else m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Walk_Head_L");
		break;
	case JUMP:
		if (!m_bRight) m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Jump_Head_L");
		else m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Jump_Head_R");
		break;
	case DJUMP:
		if (!m_bRight) m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Jump_Head_L");
		else m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Jump_Head_R");
		break;
	case FALL:
		if (!m_bRight) m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Fall_Head_L");
		else m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Fall_Head_R");
		break;
	case ATTACK:
		if (m_bRight) m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Attack_Head_R");
		else m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Attack_Head_L");
		break;
	case JMPATTACK:
		if (m_bRight) m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_JumpAttack_Head_R");
		else m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_JumpAttack_Head_L");
		break;
	case DASH:
		if (m_bRight) m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Dash_Head_R");
		else m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Dash_Head_L");
		break;
	case SKILL1:
		if (m_bRight) m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Switch_R");
		else m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Switch_L");
		break;
	case SKILL2:
		if (m_bRight) m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Skill_R");
		else m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Skill_L");
		break;
	}

	if (m_pAnimation == nullptr)
		return;

	// 렉트의 차이 때문에 발생하는 위치 차이 오프셋으로 매꾸기
	RECT tNewRect = m_pAnimation->Get_OriginCollRect();
	int iOffsetX = (tNewRect.left - tOriginRect.left) + (tNewRect.right - tOriginRect.right);
	int iOffsetY = (tNewRect.bottom - tOriginRect.bottom) + (tNewRect.top - tOriginRect.top);
	m_tInfo.x -= iOffsetX;
	m_tInfo.y -= iOffsetY;

	// 위치 업데이트 한번 안해주면 쓰레기값 들어가더라
	m_pAnimation->Update_Position(m_tInfo.x, m_tInfo.y);

	m_iCheck = eState;
}

CPlayer* CPlayer::Create(float fStartX, float fStartY)
{
	CPlayer* pInstance = new CPlayer;

	if (FAILED(pInstance->Ready_GameObj(fStartX, fStartY)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CPlayer::Free()
{
}
