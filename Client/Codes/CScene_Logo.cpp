#include "stdafx.h"
#include "CScene_Logo.h"

#include "CTest.h"

CScene_Logo::CScene_Logo()
{
}

CScene_Logo::~CScene_Logo()
{
	Free();
}

HRESULT CScene_Logo::Ready_Scene()
{
	CScene::Ready_Scene();

	if (FAILED(m_pResourceMgr->Load_Sprite(L"Logo_KPU", L"../../Binary/Resources/Sprite/Loading/Logo_0.png")))
		return E_FAIL;
	if (FAILED(m_pResourceMgr->Load_Sprite(L"Logo_Team", L"../../Binary/Resources/Sprite/Loading/Logo_1.png")))
		return E_FAIL;

	m_strTag = L"Logo_Team";
	m_fSpeed = 150.f;

	return NOERROR;
}

HRESULT CScene_Logo::Update_Scene(const float& fTimeDelta)
{
	if (m_bSceneChange)
		return m_pSceneMgr->Change_Scene(CSceneManager::SCENE_LOADING);

	m_fAlpha += fTimeDelta * m_fSpeed;

	if (m_fAlpha > 255.f)
	{
		m_fAlpha = 255.f;
		m_fTime += fTimeDelta * 4.f;
		if (m_fTime > 1.f)
		{
			m_fTime = 0.f;
			m_fSpeed = -150.f;
		}
	}

	if (m_fAlpha < 0.f)
	{
		m_fAlpha = 0.f;
		m_fTime += fTimeDelta * 4.f;
		if (m_fTime > 1.f)
		{
			if (!m_bLogoEnd)
			{
				// 첫번째 이미지 끝
				m_fTime = 0.f;
				m_fSpeed = 150.f;
				m_strTag = L"Logo_KPU";
				m_bLogoEnd = true;
			}
			else
				m_bSceneChange = true;
		}
	}

	return CScene::Update_Scene(fTimeDelta);
}

HRESULT CScene_Logo::Render_Scene(HDC hDC)
{
	CImage* pImage = m_pResourceMgr->Find_Sprite(m_strTag);
	if (pImage != nullptr)
		pImage->AlphaBlend(hDC, 0, 0, (int)m_fAlpha);

	return CScene::Render_Scene(hDC);
}

CScene_Logo* CScene_Logo::Create()
{
	CScene_Logo* pInstance = new CScene_Logo();

	if (FAILED(pInstance->Ready_Scene()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CScene_Logo::Free()
{
	m_pGameMgr->Reset_OBJLIST();
}
