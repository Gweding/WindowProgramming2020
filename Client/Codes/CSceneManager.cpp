#include "stdafx.h"
#include "CSceneManager.h"
#include "CScene.h"

#include "CScene_TestStage.h"

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

	if (m_eNextScene != m_eCurScene)
	{
		SafeDelete(m_pScene);
		CGameManager::GetInstance()->Reset_OBJLIST();

		switch (m_eNextScene)
		{
		case CSceneManager::SCENE_TESTSTAGE:
			m_pScene = CScene_TestStage::Create();
			break;
		default:
			break;
		}

		m_eCurScene = m_eNextScene;
	}

	return NOERROR;
}

void CSceneManager::Free()
{
	SafeDelete(m_pScene);
}
