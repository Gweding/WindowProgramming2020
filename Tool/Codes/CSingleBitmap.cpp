#include "pch.h"
#include "CSingleBitmap.h"

CSingleBitmap::CSingleBitmap()
{
}

CSingleBitmap::~CSingleBitmap()
{
}

HRESULT CSingleBitmap::LoadBmp(wstring strFilePath)
{
	HDC hDC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);
	m_hBitmap = (HBITMAP)LoadImage(NULL, strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	return NOERROR;
}

void CSingleBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}

CSingleBitmap* CSingleBitmap::Create(wstring strFilePath)
{
	CSingleBitmap* pInstance = new CSingleBitmap;
	
	if (FAILED(pInstance->LoadBmp(strFilePath)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
