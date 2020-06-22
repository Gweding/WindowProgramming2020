#include "stdafx.h"
#include "CSceneManager.h"
#include "CScene.h"

#include "CScene_Logo.h"
#include "CScene_Loading.h"

#include "CScene_TestStage.h"
#include "CScene_TutorialStage.h"
#include "CScene_Stage0.h"
#include "CScene_Stage1.h"
#include "CScene_Event.h"

IMPLEMENT_SINGLETON(CSceneManager)

CSceneManager::CSceneManager()
{
	m_eCurScene = SCENE_END;
	m_eNextScene = SCENE_END;
}

CSceneManager::~CSceneManager()
{
	Free();
}

HRESULT CSceneManager::Update_Scene(const float& fTimeDelta)
{
	return m_pScene->Update_Scene(fTimeDelta);
}

HRESULT CSceneManager::Render_Scene(HDC hdc)
{
	return m_pScene->Render_Scene(hdc);
}

HRESULT CSceneManager::Change_Scene(SCENE_ID eID)
{
	m_eNextScene = eID;
	m_bChangeScene = TRUE;

	if (m_eNextScene != m_eCurScene)
	{
		SafeDelete(m_pScene);
		CGameManager::GetInstance()->Reset_OBJLIST();
		CRenderManager::GetInstance()->Clear_RenderList();

		switch (m_eNextScene)
		{
		case CSceneManager::SCENE_LOGO:
			m_pScene = CScene_Logo::Create();
			break;
		case CSceneManager::SCENE_LOADING:
			m_pScene = CScene_Loading::Create();
			break;
		case CSceneManager::SCENE_TESTSTAGE:
			m_pScene = CScene_TestStage::Create();
			break;
		case CSceneManager::SCENE_TUTORIAL:
			m_pScene = CScene_TutorialStage::Create();
			break;
		case CSceneManager::SCENE_STAGE0:
			m_pScene = CScene_Stage0::Create();
			break;
		case CSceneManager::SCENE_STAGE1:
			m_pScene = CScene_Stage1::Create();
			break;
		case CSceneManager::SCENE_GAMEOVER0:
			m_pScene = CScene_Event::Create(0);
			break;
		case CSceneManager::SCENE_GAMEOVER1:
			m_pScene = CScene_Event::Create(1);
			break;
		case CSceneManager::SCENE_CLEAR:
			m_pScene = CScene_Event::Create(2);
			break;
		default:
			break;
		}

		if (m_pScene == nullptr)
		{
			MessageBox(g_hWnd, L"Failed To Create Scene Instance", L"ERROR", MB_OK);
			return E_FAIL;
		}

		m_eCurScene = m_eNextScene;
	}

	return NOERROR;
}

HRESULT CSceneManager::Change_NextScene()
{
	m_eNextScene = SCENE_ID(m_eCurScene + 1);
	return NOERROR;
}

void CSceneManager::Free()
{
	SafeDelete(m_pScene);
}
