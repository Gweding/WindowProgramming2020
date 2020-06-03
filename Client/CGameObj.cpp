#include "stdafx.h"
#include "CGameObj.h"

CGameObj::CGameObj()
{
}

CGameObj::~CGameObj()
{
	Free();
}

HRESULT CGameObj::Ready_GameObj()
{
	m_pKeyMgr = CKeyManager::GetInstance();
	m_pTimeMgr = CTimeManager::GetInstance();
	m_pGameMgr = CGameManager::GetInstance();
	m_pResourceMgr = CResourceManager::GetInstance();
	m_pRenderMgr = CRenderManager::GetInstance();

	return S_OK;
}

void CGameObj::LateInit_GameObj()
{
	if (!m_bIsLateInit)
	{
		this->LateInit_GameObj();
		m_bIsLateInit = true;
	}
}

int CGameObj::Update_GameObj(const float& fTimeDelta)
{
	return OBJ_NOEVENT;
}

void CGameObj::Render_GameObj(HDC hDC)
{
}

void CGameObj::Update_Rect()
{
	m_tRect.left	= LONG(m_tInfo.x - m_tInfo.cx * 0.5f);
	m_tRect.top		= LONG(m_tInfo.y - m_tInfo.cy * 0.5f);
	m_tRect.right	= LONG(m_tInfo.x + m_tInfo.cx * 0.5f);
	m_tRect.bottom	= LONG(m_tInfo.y + m_tInfo.cy * 0.5f);
}

void CGameObj::Free()
{

}
