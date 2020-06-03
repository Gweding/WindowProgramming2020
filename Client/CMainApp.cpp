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

	if (FAILED(m_pResourceMgr->Ready_ResourceManager()))
		return E_FAIL;

	m_pSceneMgr->Change_Scene(CSceneManager::SCENE_STAGE);

	m_pResourceMgr->Load_Bmp(L"../Bin/Resources/Back.bmp", L"Back");
	m_pResourceMgr->Load_Bmp(L"../Bin/Resources/Back.bmp", L"MemDC");

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
	ReleaseDC(g_hWnd, m_hDC);

	CKeyManager::GetInstance()->DestroyInstance();
	CTimeManager::GetInstance()->DestroyInstance();
	CGameManager::GetInstance()->DestroyInstance();
	CRenderManager::GetInstance()->DestroyInstance();
}
