#include "stdafx.h"
#include "CScene_Event.h"

CScene_Event::CScene_Event()
{
}

CScene_Event::~CScene_Event()
{
	Free();
}

HRESULT CScene_Event::Ready_Scene(int iType)
{
	CScene::Ready_Scene();

	m_iType = iType;

	m_pSoundMgr->Stop_All();
	m_pSoundMgr->Play_Sound(L"Default_Dead.wav", CSoundManager::EFFECT); // 브금 시작

	return NOERROR;
}

HRESULT CScene_Event::Update_Scene(const float& fTimeDelta)
{
	if (m_iType != 2)
	{
		m_fTime += fTimeDelta;

		if (m_fTime > 0.5f)
		{
			m_fTime = 0.f;
			m_bRender = !m_bRender;
		}
	}

	return CScene::Update_Scene(fTimeDelta);
}

HRESULT CScene_Event::Render_Scene(HDC hDC)
{
	if (m_pKeyMgr->KeyDown(KEY_RESTART))
	{
		if (m_pSceneMgr->Get_LastScene() == CSceneManager::SCENE_STAGE0
			|| m_pSceneMgr->Get_LastScene() == CSceneManager::SCENE_STAGE1
			|| m_pSceneMgr->Get_LastScene() == CSceneManager::SCENE_TUTORIAL)
		{
			m_pSoundMgr->Stop_Sound(CSoundManager::BGM);
			m_pSoundMgr->Play_BGM(L"Chapter1.wav"); // 브금 시작
		}

		m_pSceneMgr->Change_LastScene();
		return NOERROR;
	}

	if (m_iType == 0)
	{
		CImage* pImage = m_pResourceMgr->Find_Sprite(L"GameOver_0");
		pImage->Draw(hDC, 0, 0);
	}
	else if (m_iType == 1)
	{
		CImage* pImage = m_pResourceMgr->Find_Sprite(L"GameOver_1");
		pImage->Draw(hDC, 0, 0);
	}
	else if (m_iType == 2)
	{
		CImage* pImage = m_pResourceMgr->Find_Sprite(L"Clear");
		pImage->Draw(hDC, 0, 0);
	}

	if (m_bRender)
	{
		wstring strOut = L"R을 눌러 재시작하세요";
		SetBkMode(hDC, 1);
		SetTextAlign(hDC, TA_CENTER);
		SetTextColor(hDC, RGB(213, 213, 213));
		m_oldFont = (HFONT)SelectObject(hDC, m_hFont);
		TextOut(hDC, 640, 666, strOut.c_str(), (int)strOut.length());
	}

	return CScene::Render_Scene(hDC);
}

CScene_Event* CScene_Event::Create(int iType)
{
	CScene_Event* pInstance = new CScene_Event();

	if (FAILED(pInstance->Ready_Scene(iType)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CScene_Event::Free()
{
	m_pImage.Destroy();
	m_pGameMgr->Reset_OBJLIST();
}
