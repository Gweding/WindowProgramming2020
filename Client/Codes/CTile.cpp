#include "stdafx.h"
#include "CTile.h"

CTile::CTile()
{
}

CTile::~CTile()
{
}

HRESULT CTile::Ready_GameObj(wstring strTag, wstring strPath, float fX, float fY)
{
	CGameObj::Ready_GameObj();

	if (!m_pResourceMgr->Check_Sprite(strTag))
	{
		if (FAILED(m_pResourceMgr->Load_Sprite(strTag, strPath)))
			return E_FAIL;
	}

	m_strTag = strTag;

	m_tInfo.x = fX;
	m_tInfo.y = fY;
	m_tInfo.cx = TILE_SIZE;
	m_tInfo.cy = TILE_SIZE;
	CGameObj::Update_Rect();

	return NOERROR;
}

INT CTile::Update_GameObj(const float& fTimeDelta)
{
	if (0.f >= m_tInfo.x - CScrollManager::GetScrollPos(0) + 100.f ||
		0.f >= m_tInfo.y - CScrollManager::GetScrollPos(1) + 100.f ||
		(float)WINCX <= m_tInfo.x - CScrollManager::GetScrollPos(0) - 100.f ||
		(float)WINCY <= m_tInfo.y - CScrollManager::GetScrollPos(1) - 100.f)
		m_bRender = false;
	else
		m_bRender = true;

	CGameObj::Update_Rect();

	return 0;
}

void CTile::Render_GameObj(HDC hDC)
{
	if (!m_bRender)
		return;

	CImage* pImage = m_pResourceMgr->Find_Sprite(m_strTag);
	pImage->Draw(hDC, (int)m_tRect.left - (int)CScrollManager::GetScrollPos(0), (int)m_tRect.top - (int)CScrollManager::GetScrollPos(1), (int)m_tInfo.cx, (int)m_tInfo.cy);
}

CTile* CTile::Create(wstring strTag, wstring strPath, float fX, float fY)
{
	CTile* pInstance = new CTile;

	if (FAILED(pInstance->Ready_GameObj(strTag, strPath, fX, fY)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CTile::Free()
{
}
