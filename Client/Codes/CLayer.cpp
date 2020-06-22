#include "stdafx.h"
#include "CLayer.h"

CLayer::CLayer()
{
}

CLayer::~CLayer()
{
}

HRESULT CLayer::Ready_GameObj(wstring strTag, wstring strPath, float fSpeed, float fSizeX, float fSizeY, float fX, float fY)
{
	CGameObj::Ready_GameObj();

	if (!m_pResourceMgr->Check_Sprite(strTag))
	{
		if (FAILED(m_pResourceMgr->Load_Sprite(strTag, strPath)))
			return E_FAIL;
	}

	m_strTag = strTag;
	m_fSpeed = fSpeed;

	m_tInfo.x = fX;
	m_tInfo.y = fY;

	CImage* pImage = m_pResourceMgr->Find_Sprite(strTag);
	m_tInfo.cx = (float)pImage->GetWidth();
	m_tInfo.cy = (float)pImage->GetHeight();

	m_fSize[0] = fSizeX;
	m_fSize[1] = fSizeY;

	return NOERROR;
}

int CLayer::Update_GameObj(const float& fTimeDelta)
{
	if (m_bCull)
	{
		if (0.f >= m_tInfo.x - CScrollManager::GetScrollPos(0) + m_tInfo.cx * 2.f ||
			0.f >= m_tInfo.y - CScrollManager::GetScrollPos(1) + m_tInfo.cy * 2.f ||
			(float)WINCX <= m_tInfo.x - CScrollManager::GetScrollPos(0) - 10.f ||
			(float)WINCY <= m_tInfo.y - CScrollManager::GetScrollPos(1) - 10.f)
			m_bRender = false;
		else
			m_bRender = true;
	}
	else
		m_bRender = true;

	CGameObj::Update_Rect();

	return 0;
}

void CLayer::Render_GameObj(HDC hDC)
{
	if (!m_bRender)
		return;

	CGameObj::Update_Rect();
	CImage* pImage = m_pResourceMgr->Find_Sprite(m_strTag);
	pImage->Draw(hDC, m_tRect.left - int(CScrollManager::GetScrollPos(0) * m_fSpeed)
										, m_tRect.top - int(CScrollManager::GetScrollPos(1) * m_fSpeed)
										, (int)m_tInfo.cx * (int)m_fSize[0], (int)m_tInfo.cy * (int)m_fSize[1]);
}

CLayer* CLayer::Create(wstring strTag, wstring strPath, float fSpeed, float fSizeX, float fSizeY, float fX, float fY)
{
	CLayer* pInstance = new CLayer;

	if (FAILED(pInstance->Ready_GameObj(strTag, strPath, fSpeed, fSizeX, fSizeY, fX, fY)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CLayer::Free()
{
}
