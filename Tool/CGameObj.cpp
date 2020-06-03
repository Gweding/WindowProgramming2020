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

void CGameObj::Free()
{
}
