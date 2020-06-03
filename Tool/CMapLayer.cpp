#include "pch.h"
#include "CMapLayer.h"

CMapLayer::CMapLayer()
{
}

CMapLayer::~CMapLayer()
{
	Free();
}

HRESULT CMapLayer::Ready_GameObj(LAYER_TYPE eType)
{
	CGameObj::Ready_GameObj();

	m_eType = eType;

	return NOERROR;
}

INT CMapLayer::Update_GameObj(const float& fTimeDelta)
{
	switch (m_eType)
	{
	case LAYER_BACK:
	{
		m_tPosition.x = (int)-CScrollManager::GetScrollPos(0);
		m_tPosition.y = (int)-CScrollManager::GetScrollPos(1);
		break;
	}
	case LAYER_TILE:
	{

		break;
	}
	default:
		break;
	}

	return 0;
}

void CMapLayer::Render_GameObj(HDC hdc)
{
	if (!m_bRender)
		return;

	switch (m_eType)
	{
	case LAYER_BACK:
	{
		Graphics pGraphics(hdc);
		Image* pImage = m_pResourceMgr->Find_Sprite(m_strSpriteKey);
		pGraphics.DrawImage(pImage, m_tPosition.x, m_tPosition.y, pImage->GetWidth(), pImage->GetHeight());
		break;
	}
	case LAYER_TILE:
	{

		break;
	}
	default:
		break;
	}
}

CMapLayer* CMapLayer::Create(LAYER_TYPE eType)
{
	CMapLayer* pInstance = new CMapLayer;
	if (FAILED(pInstance->Ready_GameObj(eType)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CMapLayer::Free()
{
}
