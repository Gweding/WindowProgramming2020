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
	m_tInfo.y = fStartY;

	//m_bJump = true;
	//m_fJumpAccel = -1000.f;

	m_pAnimation = m_pAnimationMgr->Find_Animation(L"Player_Walk_Head_L");

	return NOERROR;
}

int CPlayer::Update_GameObj(const float& fTimeDelta)
{
	Update_Key(fTimeDelta);

	if (m_bJump)
	{
		m_tInfo.y -= m_fJumpPower * fTimeDelta;
		m_fJumpPower -= m_fJumpAccel * fTimeDelta;
		CScrollManager::SetScrollPos(0, -m_fJumpPower * fTimeDelta);
	}


	m_pAnimation->Update_GameObj(fTimeDelta);

	Update_Collision();
	m_pAnimation->Update_Position(m_tInfo.x, m_tInfo.y);

	m_pRenderMgr->AddBack_RenderList(this);

	return 0;
}

void CPlayer::Render_GameObj(HDC hDC)
{
	//m_pImage.Draw(hDC, m_tRect);
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
		m_tInfo.x += fTimeDelta * m_fSpeed;
		CScrollManager::SetScrollPos(fTimeDelta * m_fSpeed, 0);
	}

	if (m_pKeyMgr->KeyPressing(KEY_LEFT))
	{
		m_tInfo.x -= fTimeDelta * m_fSpeed;
		CScrollManager::SetScrollPos(-fTimeDelta * m_fSpeed, 0);
	}

	if (m_pKeyMgr->KeyPressing(KEY_SPACE)) // �����̽��ٸ� ������ �밡�� ��ü
	{
		if (!m_bJump)
		{
			m_bJump = true;

			TCHAR m_szData01[255];
			GetPrivateProfileString(_T("Jump"), _T("Accel"), NULL, m_szData01, 255, _T("../../Binary/Data/DebugData.ini"));
			m_fJumpAccel = (float)_tstof(m_szData01);
			GetPrivateProfileString(_T("Jump"), _T("Power"), NULL, m_szData01, 255, _T("../../Binary/Data/DebugData.ini"));
			m_fJumpPower = (float)_tstof(m_szData01);
		}
	}

	return 0;
}

int CPlayer::Update_Collision()
{
	system("cls");

	for (auto pCollRect : m_pGameMgr->Get_MapCollider())
	{
		RECT tDstRect = pCollRect->tRect;	// �ʿ� �ִ� ��Ʈ
		RECT tSrcRect = m_pAnimation->Get_CollRect();		// �÷��̾� ��Ʈ
		RECT tTempRect = {};		// ��ģ ��Ʈ

		if (IntersectRect(&tTempRect, &tSrcRect, &tDstRect))
		{
			float fMoveX = tTempRect.right - tTempRect.left;
			float fMoveY = tTempRect.bottom - tTempRect.top;

			//cout << fMoveX << " // " << fMoveY << endl;
			cout << "����" << endl;

			if (pCollRect->iType != COLL_INTERACT)
			{
				// �浹�ؾ��ϴ� �ڽ�
				//�� �Ʒ� �浹
				if (fMoveX > fMoveY)
				{
					if (m_tInfo.y < (tDstRect.bottom + tDstRect.top) / 2)
					{
						// ��
						m_bJump = false;
						m_tInfo.y -= fMoveY;
						CScrollManager::SetScrollPos(0, -fMoveY);
					}
					else
					{
						// �Ʒ�
						m_tInfo.y += fMoveY;
						CScrollManager::SetScrollPos(0, fMoveY);
					}
				}
				//������ ���� �浹
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
			else
			{
				// ��ȣ�ۿ�
			}
		}
		else
			cout << "�̴�" << endl;
	}

	cout << "==========================" << endl;

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