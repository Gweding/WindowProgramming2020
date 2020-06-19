#include "..\..\Client\Codes\CTile.h"
#include "..\..\Client\Codes\CTile.h"
#include "pch.h"
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

	m_strTag = strTag;
	m_strPath = strPath;

	if (!m_pResourceMgr->Check_Sprite(m_strTag))
		m_pResourceMgr->Load_Sprite(m_strPath, m_strTag);

	m_tInfo.x = fX;
	m_tInfo.y = fY;
	m_tInfo.cx = TILE_SIZE;
	m_tInfo.cy = TILE_SIZE;
	CGameObj::Update_Rect();

	return NOERROR;
}

INT CTile::Update_GameObj(const float& fTimeDelta)
{
	CGameObj::Update_Rect();

	POINT pt = {};
	Update_Rect();
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	RECT temp = m_tRect;
	temp.left -= (int)CScrollManager::GetScrollPos(0);
	temp.right -= (int)CScrollManager::GetScrollPos(0);
	temp.top -= (int)CScrollManager::GetScrollPos(1);
	temp.bottom -= (int)CScrollManager::GetScrollPos(1);

	if (PtInRect(&temp, pt))
	{
		m_bSelected = true;
		if (m_pKeyMgr->KeyDown(KEY_RBUTTON))
			return OBJ_DEAD;
	}
	else
		m_bSelected = false;

	return 0;
}

void CTile::Render_GameObj(HDC hdc)
{
	CImage* pImage = m_pResourceMgr->Find_Sprite(m_strTag);
	pImage->Draw(hdc, (int)m_tRect.left - (int)CScrollManager::GetScrollPos(0), (int)m_tRect.top - (int)CScrollManager::GetScrollPos(1), (int)m_tInfo.cx, (int)m_tInfo.cy);

	if (m_bSelected)
	{
		pImage = m_pResourceMgr->Find_Sprite(L"SelectedTile");
		pImage->Draw(hdc, (int)m_tRect.left - (int)CScrollManager::GetScrollPos(0), (int)m_tRect.top - (int)CScrollManager::GetScrollPos(1), pImage->GetWidth() * 2.f, pImage->GetHeight() * 2.f);
	}
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
