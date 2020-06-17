#include "pch.h"
#include "CProject.h"
#include "MainFrm.h"
#include "CToolMenu.h"

UINT g_iGridX;
UINT g_iGridY;

CProject::CProject()
{
	for (int i = 0; i < RENDER_END; ++i)
		m_bRender[i] = true;
}

CProject::~CProject()
{
	Free();
}

HRESULT CProject::Ready_Project()
{
	m_pKeyMgr = CKeyManager::GetInstance();
	m_pTimeMgr = CTimeManager::GetInstance();
	m_pSoundMgr = CSoundManager::GetInstance();
	m_pResourceMgr = CResourceManager::GetInstance();

	m_pSoundMgr->Ready_SoundManager();

	GdiplusStartupInput tGdiplusStartup; if (::GdiplusStartup(&m_pGdiPlusTokenData, &tGdiplusStartup, NULL) != Ok)
	{
		AfxMessageBox(_T("ERROR:Faield to initialize GDI+ library"));
		return E_FAIL;
	}

	m_pResourceMgr->Load_Bmp(L"../../Binary/Resources/Back.bmp", L"Back");
	m_pResourceMgr->Load_Bmp(L"../../Binary/Resources/Back.bmp", L"MemDC");

	m_pResourceMgr->Load_Sprite(L"../../Binary/Resources/Default.png", L"Default");
	m_pResourceMgr->Load_Sprite(L"../../Binary/Resources/SelectedTile.png", L"SelectedTile");
	m_pResourceMgr->Load_Sprite(L"../../Binary/Resources/Sprite/Tile/0_Tile01_0.png", L"0_Tile01_0");

	//
	m_pScene = CScene::Create();
	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CToolMenu* pMenu = dynamic_cast<CToolMenu*>(pFrameWnd->m_WndSplit.GetPane(0, 0));
	pMenu->m_pScene->m_pCurrScene = m_pScene;

	m_AnimationHwnd = pMenu->m_pMain->m_Animation.GetSafeHwnd();
	m_pAnimation = CAnimation::Create();
	pMenu->m_pMain->m_Animation.m_pCurrAnimation = m_pAnimation;

	return NOERROR;
}

INT CProject::Update_Project(const float& fTimeDelta)
{
	m_pKeyMgr->UpdateKey();
	m_pSoundMgr->Update_SoundManager();

	m_pScene->Update_GameObj(fTimeDelta);

	if (IsWindowVisible(m_AnimationHwnd))
		m_pAnimation->Update_GameObj(fTimeDelta);

	return 0;
}

void CProject::Render_Project(HDC hdc)
{
	HDC hBack = m_pResourceMgr->Find_Bmp(L"Back");
	HDC hMemDC = m_pResourceMgr->Find_Bmp(L"MemDC");

	BitBlt(hBack, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	Graphics Graphic(hBack);
	Graphic.Clear(Color(255, 255, 255));	// 백버퍼의 Gdi+ 비워주기

	//

	m_pScene->Render_GameObj(hBack);

	if (IsWindowVisible(m_AnimationHwnd))
		m_pAnimation->Render_GameObj(hBack);

	//

	BitBlt(hdc, 0, 0, WINCX, WINCY, hBack, 0, 0, SRCCOPY);
}

CProject* CProject::Create()
{
	CProject* pInstance = new CProject;

	if (FAILED(pInstance->Ready_Project()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CProject::Free()
{
	SafeDelete(m_pScene);
	GdiplusShutdown(m_pGdiPlusTokenData);

	CKeyManager::GetInstance()->DestroyInstance();
	CTimeManager::GetInstance()->DestroyInstance();
	CSoundManager::GetInstance()->DestroyInstance();
	CResourceManager::GetInstance()->DestroyInstance();
}
