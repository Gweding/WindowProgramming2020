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
	m_pSoundMgr = CSoundManager::GetInstance();

	m_pSceneMgr->Get_ChangeScene() = FALSE;

	m_hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("³ª´®½ºÄù¾î ExtraBold"));

	return NOERROR;
}

HRESULT CScene::Update_Scene(const float& fTimeDelta)
{
	return m_pGameMgr->Update_Object(fTimeDelta);
}

HRESULT CScene::Render_Scene(HDC hDC)
{
	if (m_pSceneMgr->Get_ChangeScene())
	{
		m_pSceneMgr->Change_Scene(m_pSceneMgr->Get_NextScene());
		return NOERROR;
	}

	return m_pRenderMgr->RenderObject(hDC);
}

void CScene::Free()
{
	SelectObject(GetDC(g_hWnd), m_oldFont);
	DeleteObject(m_hFont);
}

