#include "stdafx.h"
#include "CScene_Loading.h"

CScene_Loading::CScene_Loading()
{
}

CScene_Loading::~CScene_Loading()
{
	Free();
}

HRESULT CScene_Loading::Ready_Scene()
{
	CScene::Ready_Scene();

	InitializeCriticalSection(&m_CriticalSection);
	m_hLoadingThread = (HANDLE)_beginthreadex(nullptr, 0, Load_Resource, this, 0, nullptr);

	if (FAILED(m_pResourceMgr->Load_Sprite_FromPath(L"../../Binary/Data/Path/ImagePath_Loading.dat")))
		return E_FAIL;

	m_hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("나눔스퀘어 ExtraBold"));

	m_strLoadingMessage = L"";

	return NOERROR;
}

HRESULT CScene_Loading::Update_Scene(const float& fTimeDelta)
{

	if (m_bLoadingEnd && !m_bTransition)
	{
		if (m_pKeyMgr->KeyDown(KEY_ENTER))
			m_bTransition = true;
	}

	if (!m_bLogoAniEnd)
		Update_LogoAnimation(fTimeDelta);

	if (m_bTransition)
	{
		m_strLoadingMessage = L"";
		m_fBackAlpha -= fTimeDelta * 300.f;
		m_fLogoAlpha = m_fBackAlpha;

		if (m_fBackAlpha < 0.f)
		{
			m_pSceneMgr->Change_Scene(CSceneManager::SCENE_TESTSTAGE);
			return NOERROR;
		}
	}

	return NOERROR;
}

HRESULT CScene_Loading::Render_Scene(HDC hDC)
{
	CImage* pImage = nullptr;
	
	pImage = m_pResourceMgr->Find_Sprite(L"Loading_Title");
	if (pImage != nullptr)
		pImage->AlphaBlend(hDC, 0, 0, (int)m_fBackAlpha);

	pImage = m_pResourceMgr->Find_Sprite(L"Loading_Logo");
	if (pImage != nullptr)
		pImage->AlphaBlend(hDC, 0, 0, (int)m_fLogoAlpha);

	if (m_bLogoAniEnd)
	{
		SetBkMode(hDC, 1);
		SetTextAlign(hDC, TA_CENTER);
		SetTextColor(hDC, RGB(255, 255, 255));
		m_oldFont = (HFONT)SelectObject(hDC, m_hFont);
		TextOut(hDC, 640, 620, m_strLoadingMessage.c_str(), (int)m_strLoadingMessage.length());
	}

	return NOERROR;
}

HRESULT CScene_Loading::Update_LogoAnimation(const float& fTimeDelta)
{
	m_fBackAlpha += fTimeDelta * 300.f;
	if (m_fBackAlpha > 255.f)
	{
		m_fBackAlpha = 255.f;
		m_fTime += fTimeDelta * 5.f;
	}

	if (m_fTime > 1.f)
	{
		m_fLogoAlpha += fTimeDelta * 300.f;
		if (m_fLogoAlpha > 255.f)
		{
			m_fLogoAlpha = 255.f;
			m_bLogoAniEnd = true;
			m_hLoadingThread = (HANDLE)_beginthreadex(nullptr, 0, Load_Resource, this, 0, nullptr);
		}
	}

	return NOERROR;
}

CScene_Loading* CScene_Loading::Create()
{
	CScene_Loading* pInstance = new CScene_Loading();

	if (FAILED(pInstance->Ready_Scene()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

unsigned int __stdcall CScene_Loading::Load_Resource(void* pParam)
{
	CScene_Loading* pLogo = reinterpret_cast<CScene_Loading*>(pParam);

	EnterCriticalSection(&pLogo->m_CriticalSection);

	if (FAILED(pLogo->m_pResourceMgr->Load_Sprite_FromPath(L"../../Binary/Data/Path/ImagePath_Effect.dat")))
	{
		pLogo->m_strLoadingMessage = L"이펙트 로드 실패";
		return E_FAIL;
	}

	if (FAILED(pLogo->m_pResourceMgr->Load_Sprite_FromPath(L"../../Binary/Data/Path/ImagePath_Map.dat")))
	{
		pLogo->m_strLoadingMessage = L"맵 로드 실패";
		return E_FAIL;
	}

	if (FAILED(pLogo->m_pResourceMgr->Load_Sprite_FromPath(L"../../Binary/Data/Path/ImagePath_Monster.dat")))
	{
		pLogo->m_strLoadingMessage = L"몬스터 로드 실패";
		return E_FAIL;
	}

	if (FAILED(pLogo->m_pResourceMgr->Load_Sprite_FromPath(L"../../Binary/Data/Path/ImagePath_Player.dat")))
	{
		pLogo->m_strLoadingMessage = L"플레이어 로드 실패";
		return E_FAIL;
	}

	if (FAILED(pLogo->m_pResourceMgr->Load_Sprite_FromPath(L"../../Binary/Data/Path/ImagePath_Tile.dat")))
	{
		pLogo->m_strLoadingMessage = L"타일 로드 실패";
		return E_FAIL;
	}

	if (FAILED(pLogo->m_pResourceMgr->Load_Sprite_FromPath(L"../../Binary/Data/Path/ImagePath_UI.dat")))
	{
		pLogo->m_strLoadingMessage = L"UI 로드 실패";
		return E_FAIL;
	}

	pLogo->m_strLoadingMessage = L"PRESS ENTER";
	pLogo->m_bLoadingEnd = true;

	LeaveCriticalSection(&pLogo->m_CriticalSection);

	return 0;
}

void CScene_Loading::Free()
{
	CloseHandle(m_hLoadingThread);
	DeleteCriticalSection(&m_CriticalSection);

	SelectObject(GetDC(g_hWnd), m_oldFont);
	DeleteObject(m_hFont);
}
