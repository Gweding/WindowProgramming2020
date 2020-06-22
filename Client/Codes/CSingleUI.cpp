#include "stdafx.h"
#include "CPortal.h"
#include "CAnimation.h"

CPortal::CPortal()
{
}

CPortal::~CPortal()
{
	Free();
}

HRESULT CPortal::Ready_GameObj(float fStartX, float fStartY)
{
	CGameObj::Ready_GameObj();

	m_tInfo.x = fStartX;
	m_tInfo.y = fStartY /*+ 15*/;
	m_tInfo.cx = 100.f;
	m_tInfo.cy = 100.f;

	m_pAnimation = m_pAnimationMgr->Find_Animation(L"Portal");
	m_pAnimation->Update_Position(m_tInfo.x + 215.f * 0.5f, m_tInfo.y + 159.f * 0.5f);

	return S_OK;
}

int CPortal::Update_GameObj(const float& fTimeDelta)
{
	m_pAnimation->Update_GameObj(fTimeDelta);
	
	RECT temp;
	if (IntersectRect(&temp, &m_pAnimation->Get_CollRect(), &m_pGameMgr->Get_Player()->Get_Rect()))
		m_bRenderUI = true;
	else
		m_bRenderUI = false;

	CGameObj::Update_Rect();
	m_pRenderMgr->AddBack_RenderList(this);

	return OBJ_NOEVENT;
}

void CPortal::Render_GameObj(HDC hDC)
{
	//m_pAnimation->Render_GameObj(hDC);

	if (m_bRenderUI)
	{
		float fX = m_tInfo.x - CScrollManager::GetScrollPos(0);
		float fY = m_tInfo.y - CScrollManager::GetScrollPos(1);
		CImage* pImage = m_pResourceMgr->Find_Sprite(L"F");
		pImage->Draw(hDC, fX, fY, pImage->GetWidth(), pImage->GetHeight());
	}
}

CPortal* CPortal::Create(float fStartX, float fStartY)
{
	CPortal* pInstance = new CPortal;

	if (FAILED(pInstance->Ready_GameObj(fStartX, fStartY)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CPortal::Free()
{
}
