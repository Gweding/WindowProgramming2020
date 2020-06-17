#include "pch.h"
#include "CGrid.h"

CGrid::CGrid()
{
}

CGrid::~CGrid()
{
}

HRESULT CGrid::Ready_GameObj()
{
	CGameObj::Ready_GameObj();

	return NOERROR;
}

INT CGrid::Update_GameObj(const float& fTimeDelta)
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	// 1초에 500 이동
	float fMoveSpeed = 500.f * fTimeDelta;

	if (m_pKeyMgr->KeyPressing(KEY_LEFT))
		CScrollManager::SetScrollPos(-fMoveSpeed, 0.f);
	if (m_pKeyMgr->KeyPressing(KEY_UP))
		CScrollManager::SetScrollPos(0.f, -fMoveSpeed);
	if (m_pKeyMgr->KeyPressing(KEY_RIGHT))
		CScrollManager::SetScrollPos(fMoveSpeed, 0.f);
	if (m_pKeyMgr->KeyPressing(KEY_DOWN))
		CScrollManager::SetScrollPos(0.f, fMoveSpeed);

	return 0;
}

void CGrid::Render_GameObj(HDC hdc)
{
	if (!m_bRender)
		return;

	Graphics pGraphics(hdc);
	Pen pPen(Color(255, 30, 30, 30), 1.5f);

	for (UINT i = 0; i <= g_iGridX; ++i)
		pGraphics.DrawLine(&pPen, i * TILE_SIZE - CScrollManager::GetScrollPos(0), -CScrollManager::GetScrollPos(1), 
															i * TILE_SIZE - CScrollManager::GetScrollPos(0), g_iGridY * TILE_SIZE - CScrollManager::GetScrollPos(1));

	for (UINT i = 0; i <= g_iGridY; ++i)
		pGraphics.DrawLine(&pPen, -CScrollManager::GetScrollPos(0), i * TILE_SIZE - CScrollManager::GetScrollPos(1),
															g_iGridX * TILE_SIZE - CScrollManager::GetScrollPos(0), i * TILE_SIZE - CScrollManager::GetScrollPos(1));
}

CGrid* CGrid::Create()
{
	CGrid* pInstance = new CGrid;
	if (FAILED(pInstance->Ready_GameObj()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CGrid::Free()
{
}
