#include "stdafx.h"
#include "CResourceManager.h"
#include "CBitmap.h"

IMPLEMENT_SINGLETON(CResourceManager)

CResourceManager::CResourceManager()
{
}

CResourceManager::~CResourceManager()
{
	Free();
}

HDC CResourceManager::Find_Bmp(wstring strImgKey)
{
	auto iter = m_mapBmp.find(strImgKey);

	if (m_mapBmp.end() == iter)
		return nullptr;

	return iter->second->Get_MemDC();
}

CImage* CResourceManager::Find_Sprite(wstring strImgKey)
{
	auto iter = m_mapSprite.find(strImgKey);

	if (m_mapSprite.end() == iter)
		return nullptr;

	return iter->second;
}

HRESULT CResourceManager::Load_Bmp(wstring strImgKey, wstring strFilePath)
{
	auto iter = m_mapBmp.find(strImgKey);

	if (iter == m_mapBmp.end())
	{
		CBitmap* pBitmap = CBitmap::Create(strFilePath);
		if (pBitmap == nullptr)
			return E_FAIL;
		m_mapBmp.emplace(strImgKey, pBitmap);
	}

	return NOERROR;
}

HRESULT CResourceManager::Load_Sprite(wstring strImgKey, wstring strFilePath)
{
	auto iter = m_mapSprite.find(strImgKey);

	if (iter == m_mapSprite.end())
	{
		CImage* pImage = new CImage;
		if (FAILED(pImage->Load(strFilePath.c_str())))
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
	{
		iter.second->Destroy();
		SafeDelete(iter.second);
	}
	m_mapSprite.clear();
}
