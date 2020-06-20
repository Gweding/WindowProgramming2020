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
	m_tInfo.y = fStartY + 15;

	m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Idle_Head_L");

	return NOERROR;
}

int CPlayer::Update_GameObj(const float& fTimeDelta)
{
	Update_Key(fTimeDelta);

	if (m_bJump)
	{

		if(m_fJumpPower >= 0) 
			if(!m_bRight) m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Jump_Head_L");
			else m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Jump_Head_R");
		else 
			if (!m_bRight) m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Fall_Head_L");
			else m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Fall_Head_R");

		m_tInfo.y -= m_fJumpPower * fTimeDelta;
		CScrollManager::SetScrollPos(0, -m_fJumpPower * fTimeDelta);
		m_fJumpPower -= m_fJumpAccel * fTimeDelta;
		
	}
	else if (m_iDJump == 2)
	{
		if (m_fJumpPower >= 0)
			if (!m_bRight) m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Jump_Head_L");
			else m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Jump_Head_R");
		else
			if (!m_bRight) m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Fall_Head_L");
			else m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Fall_Head_R");

		m_tInfo.y -= m_fJumpPower * fTimeDelta;
		CScrollManager::SetScrollPos(0, -m_fJumpPower * fTimeDelta);
		m_fJumpPower -= m_fJumpAccel * fTimeDelta;
	}
	
	m_pAnimation->Update_GameObj(fTimeDelta);

	m_pAnimation->Update_Position(m_tInfo.x, m_tInfo.y);
	Update_Collision();

	m_pRenderMgr->AddBack_RenderList(this);

	return 0;
}

void CPlayer::Render_GameObj(HDC hDC)
{
	m_pAnimation->Render_GameObj(hDC);
}

int CPlayer::Update_Key(const float& fTimeDelta)
{
	if (m_pKeyMgr->KeyPressing(KEY_UP))
	{

		m_tInfo.y -= fTimeDelta * m_fSpeed;
		CScrollManager::SetScrollPos(0, -fTimeDelta * m_fSpeed);
	}

	if (m_pKeyMgr->KeyPressing(KEY_DOWN))
	{
		m_tInfo.y += fTimeDelta * m_fSpeed;
		CScrollManager::SetScrollPos(0, fTimeDelta * m_fSpeed);
	}

	if (m_pKeyMgr->KeyPressing(KEY_RIGHT))
	{
		m_bRight = TRUE;
		m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Walk_Head_R");
		m_tInfo.x += fTimeDelta * m_fSpeed;
		CScrollManager::SetScrollPos(fTimeDelta * m_fSpeed, 0);
	}
	if (m_pKeyMgr->KeyUp(KEY_RIGHT))
	{
		m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Idle_Head_R");
	}

	if (m_pKeyMgr->KeyPressing(KEY_LEFT))
	{
		m_bRight = FALSE;
		m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Walk_Head_L");
		m_tInfo.x -= fTimeDelta * m_fSpeed;
		CScrollManager::SetScrollPos(-fTimeDelta * m_fSpeed, 0);
	}
	if (m_pKeyMgr->KeyUp(KEY_LEFT))
	{
		m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Idle_Head_L");
	}

	if (m_pKeyMgr->KeyDown(KEY_PLAYERATTACK))
	{
		if (m_bJump)
		{
			
			if(!m_bRight) m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_JumpAttack_Head_L");
			else m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_JumpAttack_Head_R");
		}
		else
		{
			if(!m_bRight) m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Attack_Head_L");
			else m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Attack_Head_R");
		}
		//m_tInfo.x -= fTimeDelta * m_fSpeed;
		//CScrollManager::SetScrollPos(-fTimeDelta * m_fSpeed, 0);
	}
	
	if (m_pKeyMgr->KeyDown(KEY_PLAYERJUMP)) // 스페이스바를 누르면 대가리 교체
	{
		// 임시 점프
		if (!m_bJump)
		{
			m_bJump = true;
			m_iDJump = 1;
			TCHAR m_szData01[255];
			GetPrivateProfileString(_T("Jump"), _T("Accel"), NULL, m_szData01, 255, _T("../../Binary/Data/DebugData.ini"));
			m_fJumpAccel = (float)_tstof(m_szData01);
			GetPrivateProfileString(_T("Jump"), _T("Power"), NULL, m_szData01, 255, _T("../../Binary/Data/DebugData.ini"));
			m_fJumpPower = (float)_tstof(m_szData01);
		}
		else if(m_bJump && m_iDJump == 1)
		{
			m_bJump = true;
			m_iDJump = 2;
			TCHAR m_szData01[255];
			GetPrivateProfileString(_T("Jump"), _T("DAccel"), NULL, m_szData01, 255, _T("../../Binary/Data/DebugData.ini"));
			m_fJumpAccel = (float)_tstof(m_szData01);
			GetPrivateProfileString(_T("Jump"), _T("DPower"), NULL, m_szData01, 255, _T("../../Binary/Data/DebugData.ini"));
			m_fJumpPower = (float)_tstof(m_szData01);
		}
	}


	return 0;
}

int CPlayer::Update_Collision()
{
	for (auto pCollRect : m_pGameMgr->Get_MapCollider())
	{
		RECT tDstRect = pCollRect->tRect;					// 맵에 있는 렉트
		RECT tSrcRect = m_pAnimation->Get_CollRect();		// 플레이어 렉트
		RECT tTempRect = {};								// 겹친 렉트

		if (IntersectRect(&tTempRect, &tSrcRect, &tDstRect))
		{
			float fX = m_tInfo.x;
			float fY = m_tInfo.y;

			float fDstX = tDstRect.right - tDstRect.left;
			float fDstY = tDstRect.bottom - tDstRect.top;

			float fMoveX = tTempRect.right - tTempRect.left;
			float fMoveY = tTempRect.bottom - tTempRect.top;

			//위 아래 충돌
			if (fMoveX > fMoveY)
			{
				if (m_tInfo.y < (tDstRect.bottom + tDstRect.top) / 2)
				{
					// 위
					m_bJump = false;
					m_iDJump = 0;
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
		}
	}

	m_pAnimation->Update_Position(m_tInfo.x, m_tInfo.y);

	return 0;
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
