#include "stdafx.h"
#include "CMainApp.h"

CMainApp::~CMainApp()
{
	Free();
}

HRESULT CMainApp::Ready_MainApp()
{
	m_hDC = GetDC(g_hWnd);
	srand(unsigned int(time(NULL)));

	m_pKeyMgr = CKeyManager::GetInstance();
	m_pSceneMgr = CSceneManager::GetInstance();
	m_pResourceMgr = CResourceManager::GetInstance();

	if (FAILED(m_pSceneMgr->Change_Scene(CSceneManager::SCENE_LOGO)))
		return E_FAIL;
	//if (FAILED(m_pSceneMgr->Change_Scene(CSceneManager::SCENE_TESTSTAGE)))
	//	return E_FAIL;
	//if (FAILED(m_pSceneMgr->Change_Scene(CSceneManager::SCENE_LOADING)))
	//	return E_FAIL;

	if (FAILED(m_pResourceMgr->Load_Bmp(L"Back", L"../../Binary/Resources/Back.bmp")))
		return E_FAIL;
	if (FAILED(m_pResourceMgr->Load_Bmp(L"MemDC", L"../../Binary/Resources/Back2.bmp")))
		return E_FAIL;

	if (AddFontResource(L"../../Binary/Font/NanumSquareEB.ttf") == 0)
		return E_FAIL;

	CSoundManager::GetInstance()->Ready_SoundManager();
	if (FAILED(CSoundManager::GetInstance()->Load_SoundFile("..\\..\\Binary\\Resources\\Sound\\")))
		return E_FAIL;

	CSoundManager::GetInstance()->Play_BGM(L"Tutorial.wav");

	return S_OK;
}

void CMainApp::Update_MainApp(const float& fTimeDelta)
{
	m_pSceneMgr->Update_Scene(fTimeDelta);
	m_pKeyMgr->UpdateKey();
}

void CMainApp::Render_MainApp()
{
	// Double Buffering
	RenderStart();
	m_pSceneMgr->Render_Scene(m_hBackDC);
	RenderEnd();
}

void CMainApp::RenderStart()
{
	m_hBackDC = m_pResourceMgr->Find_Bmp(L"Back");
	m_hMemDC = m_pResourceMgr->Find_Bmp(L"MemDC");
	BitBlt(m_hBackDC, 0, 0, WINCX, WINCY, m_hMemDC, 0, 0, SRCCOPY);
}

void CMainApp::RenderEnd()
{
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_hBackDC, 0, 0, SRCCOPY);
}

CMainApp* CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp;

	if (E_FAIL == pInstance->Ready_MainApp())
	{
		SafeDelete(pInstance);
		return pInstance;
	}

	return pInstance;
}

void CMainApp::Free()
{
	RemoveFontResource(L"../../Binary/Font/NanumSquareEB.ttf");

	ReleaseDC(g_hWnd, m_hDC);

	CKeyManager::GetInstance()->DestroyInstance();
	CTimeManager::GetInstance()->DestroyInstance();

	CMapManager::GetInstance()->DestroyInstance();
	CAnimationManager::GetInstance()->DestroyInstance();

	//
	CSceneManager::GetInstance()->DestroyInstance();
	CGameManager::GetInstance()->DestroyInstance();
	CRenderManager::GetInstance()->DestroyInstance();
	CResourceManager::GetInstance()->DestroyInstance();
	CSoundManager::GetInstance()->DestroyInstance();
}
