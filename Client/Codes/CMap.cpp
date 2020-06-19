#include "stdafx.h"
#include "CMap.h"

#include "CTile.h"
#include "CLayer.h"

CMap::CMap()
{
}

CMap::~CMap()
{
	Free();
}

HRESULT CMap::Ready_GameObj()
{
	CGameObj::Ready_GameObj();

	return NOERROR;
}

int CMap::Update_GameObj(const float& fTimeDelta)
{
	for (auto pLayer : m_lstLayer)
		pLayer->Update_GameObj(fTimeDelta);

	for (auto pTile : m_lstTile)
		pTile->Update_GameObj(fTimeDelta);

	if (m_pKeyMgr->KeyDown(KEY_COLLIDER))
		m_bRenderCollider = !m_bRenderCollider;

	return 0;
}

void CMap::Render_GameObj(HDC hDC)
{
	for (auto pLayer : m_lstLayer)
		pLayer->Render_GameObj(hDC);

	for (auto pTile : m_lstTile)
		pTile->Render_GameObj(hDC);

	if (m_bRenderCollider)
		Render_Collider(hDC);
}

void CMap::Render_Collider(HDC hDC)
{
	for (auto pCollRect : m_lstCollision)
	{
		if(pCollRect->iType == COLL_ALL)
			m_hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		else if (pCollRect->iType == COLL_JUMP)
			m_hPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
		else if (pCollRect->iType == COLL_INTERACT)
			m_hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));

		m_hOldPen = SelectObject(hDC, m_hPen);
		m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		m_hOldBrush = SelectObject(hDC, m_hBrush);
		Rectangle(hDC, pCollRect->tRect.left - int(CScrollManager::GetScrollPos(0)),
									pCollRect->tRect.top - int(CScrollManager::GetScrollPos(1)),
									pCollRect->tRect.right - int(CScrollManager::GetScrollPos(0)),
									pCollRect->tRect.bottom - int(CScrollManager::GetScrollPos(1)));
		SelectObject(hDC, m_hOldPen);
		SelectObject(hDC, m_hOldBrush);
		DeleteObject(m_hBrush);
		DeleteObject(m_hPen);
	}
}

HRESULT CMap::Add_Tile(CTile* pTile)
{
	if (pTile == nullptr)
		return E_FAIL;

	m_lstTile.emplace_back(pTile);

	return NOERROR;
}

HRESULT CMap::Add_Layer(CLayer* pLayer)
{
	if (pLayer == nullptr)
		return E_FAIL;

	m_lstLayer.emplace_back(pLayer);

	return NOERROR;
}

HRESULT CMap::Add_Collision(COLL_RECT* pRect)
{
	if (pRect == nullptr)
		return E_FAIL;

	m_lstCollision.emplace_back(pRect);

	return NOERROR;
}

CMap* CMap::Create()
{
	CMap* pInstance = new CMap;

	if (FAILED(pInstance->Ready_GameObj()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CMap::Free()
{
	for (auto pLayer : m_lstLayer)
		SafeDelete(pLayer);
	m_lstLayer.clear();

	for (auto pTile : m_lstTile)
		SafeDelete(pTile);
	m_lstTile.clear();

	for (auto pColl : m_lstCollision)
		SafeDelete(pColl);
	m_lstCollision.clear();
}
