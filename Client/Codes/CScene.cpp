#include "stdafx.h"
#include "CScene.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

HRESULT CScene::Ready_Scene()
{
	m_pKeyMgr = CKeyManager::GetInstance();
	m_pMapMgr = CMapManager::GetInstance();
	m_pGameMgr = CGameManager::GetInstance();
	m_pSceneMgr = CSceneManager::GetInstance();
	m_pRenderMgr = CRenderManager::GetInstance();
	m_pResourceMgr = CResourceManager::GetInstance();
	m_pAnimationMgr = CAnimationManager::GetInstance();

	return NOERROR;
}

HRESULT CScene::Update_Scene(const float& fTimeDelta)
{
	return m_pGameMgr->Update_Object(fTimeDelta);
}

HRESULT CScene::Render_Scene(HDC hDC)
{
	return m_pRenderMgr->RenderObject(hDC);
}

void CScene::Free()
{
}

