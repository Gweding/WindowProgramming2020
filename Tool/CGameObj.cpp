#include "pch.h"
#include "CGameObj.h"

CGameObj::CGameObj()
{
}

CGameObj::~CGameObj()
{
}

HRESULT CGameObj::Ready_GameObj()
{
	m_pKeyMgr = CKeyManager::GetInstance();
	m_pTimeMgr = CTimeManager::GetInstance();
	m_pSoundMgr = CSoundManager::GetInstance();
	m_pResourceMgr = CResourceManager::GetInstance();

	return NOERROR;
}

INT CGameObj::Update_GameObj(const float& fTimeDelta)
{
	return 0;
}

void CGameObj::Render_GameObj(HDC hdc)
{
}

void CGameObj::Update_Rect()
{
	m_tRect.left = LONG(m_tInfo.x - m_tInfo.cx * 0.5f);
	m_tRect.top = LONG(m_tInfo.y - m_tInfo.cy * 0.5f);
	m_tRect.right = LONG(m_tInfo.x + m_tInfo.cx * 0.5f);
	m_tRect.bottom = LONG(m_tInfo.y + m_tInfo.cy * 0.5f);
}

void CGameObj::Free()
{
}
