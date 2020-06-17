#include "stdafx.h"
#include "CBitmap.h"

CBitmap::CBitmap()
{
}

CBitmap::~CBitmap()
{
}

HRESULT CBitmap::Load_Bitmap(wstring strFilePath)
{
	HDC hDC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);
	m_hBitmap = (HBITMAP)LoadImage(NULL, strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	return NOERROR;
}

void CBitmap::Free()
{
	SelectObject(m_hMemDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}

CBitmap* CBitmap::Create(wstring strFilePath)
{
	CBitmap* pInstance = new CBitmap;
	
	if (FAILED(pInstance->Load_Bitmap(strFilePath)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
