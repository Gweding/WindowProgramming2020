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
	return NOERROR;
}

HRESULT CScene_Loading::Update_Scene(const float& fTimeDelta)
{
	return NOERROR;
}

HRESULT CScene_Loading::Render_Scene(HDC hDC)
{
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

	// Multi Texture Load
	//HRESULT hr = pLogo->m_pTextureMgr->LoadFromImgPath(L"../Data/ImgPath.txt");
	//FAILED_CHECK_RETURN(hr, 1);

	//pLogo->m_pTextureMgr->SetLoadingMessage(L"로딩 완료");

	LeaveCriticalSection(&pLogo->m_CriticalSection);

	return 0;
}

void CScene_Loading::Free()
{
	CloseHandle(m_hLoadingThread);
	DeleteCriticalSection(&m_CriticalSection);
}
