#include "pch.h"
#include "CResourceManager.h"
#include "CSingleBitmap.h"

IMPLEMENT_SINGLETON(CResourceManager)

CResourceManager::CResourceManager()
{
}

CResourceManager::~CResourceManager()
{
}

HRESULT CResourceManager::Ready_ResourceManager()
{
	GdiplusStartupInput tGdiplusStartup; if (::GdiplusStartup(&m_pGdiPlusTokenData, &tGdiplusStartup, NULL) != Ok) 
	{ 
		AfxMessageBox(_T("ERROR:Faield to initialize GDI+ library"));
		return E_FAIL; 
	}

	return NOERROR;
}

HDC CResourceManager::Find_Bmp(wstring strImgKey)
{
	auto iter = m_mapBmp.find(strImgKey);

	if (m_mapBmp.end() == iter)
		return nullptr;

	return iter->second->Get_MemDC();
}

Image* CResourceManager::Find_Sprite(wstring strImgKey)
{
	auto iter = m_mapSprite.find(strImgKey);

	if (m_mapSprite.end() == iter)
		return nullptr;

	return iter->second;
}

HRESULT CResourceManager::Load_Bmp(wstring strFilePath, wstring strImgKey)
{
	auto iter = m_mapBmp.find(strImgKey);

	if (iter == m_mapBmp.end())
	{
		CSingleBitmap* pBitmap = CSingleBitmap::Create(strFilePath);
		if (pBitmap == nullptr)
			return E_FAIL;
		m_mapBmp.emplace(strImgKey, pBitmap);
	}

	return NOERROR;
}

HRESULT CResourceManager::Load_Sprite(wstring strFilePath, wstring strImgKey)
{
	auto iter = m_mapSprite.find(strImgKey);

	if (iter == m_mapSprite.end())
	{
		Image* pImage = Image::FromFile(strFilePath.c_str());
		if (pImage == nullptr)
			return E_FAIL;
		m_mapSprite.emplace(strImgKey, pImage);
	}

	return NOERROR;
}

BOOL CResourceManager::Check_Bmp(wstring strImgKey)
{
	auto iter = m_mapBmp.find(strImgKey);

	if (iter == m_mapBmp.end())
		return FALSE;

	return TRUE;
}

BOOL CResourceManager::Check_Sprite(wstring strImgKey)
{
	auto iter = m_mapSprite.find(strImgKey);

	if (iter == m_mapSprite.end())
		return FALSE;

	return TRUE;
}

void CResourceManager::Free()
{
	for (auto& iter : m_mapBmp)
		SafeDelete(iter.second);
	m_mapBmp.clear();

	for (auto& iter : m_mapSprite)
		SafeDelete(iter.second);
	m_mapSprite.clear();

	GdiplusShutdown(m_pGdiPlusTokenData);
}
