#include "stdafx.h"
#include "CMapManager.h"

#include "CTile.h"
#include "CMap.h"
#include "CLayer.h"

IMPLEMENT_SINGLETON(CMapManager)

CMapManager::CMapManager()
{
}

CMapManager::~CMapManager()
{
	Free();
}

HRESULT CMapManager::Load_Map(wstring strTag, wstring strPath)
{
	std::locale::global(std::locale("Korean"));
#ifdef _UNICODE
	wifstream fin;
#else
	wifstream fin;
#endif // _UNICODE

	fin.open(strPath);

	if (fin.fail())
		return E_FAIL;

	CMap* pMap = CMap::Create();
	if (pMap == nullptr)
		return E_FAIL;

	while (true)
	{
		int iType;
		fin >> iType;

		if (fin.eof())
			break;

		if (iType == 0 || iType == 1)
		{
			// 레이어
			wstring strTemp = L"";
			wstring strTag = L"";
			wstring strPath = L"";
			float fSpeed = 0.f;
			float fSize[2] = {};
			float fPos[2] = {};
			fin >> strTemp >> strTag >> fSpeed >> fSize[0] >> fSize[1] >> strPath >> fPos[0] >> fPos[1];

			CLayer* pLayer = CLayer::Create(strTag, strPath, fSpeed, fSize[0], fSize[1], fPos[0], fPos[1]);
			if (pLayer == nullptr)
			{
				SafeDelete(pMap);
				return E_FAIL;
			}

			if (iType == 0)
				pLayer->Get_Cull() = false;
			else
				pLayer->Get_Cull() = true;

			if(FAILED(pMap->Add_Layer(pLayer)))
			{
				SafeDelete(pMap);
				return E_FAIL;
			}
		}
		else if (iType == 2)
		{
			// 타일
			int iCnt = 0;
			wstring strTemp = L"";
			fin >> iCnt >> strTemp;

			for (int i = 0; i < iCnt; ++i)
			{
				wstring strTag = L"";
				wstring strPath = L"";
				INFO tInfo = {};
				fin >> strTag >> tInfo.x >> tInfo.y >> tInfo.cx >> tInfo.cy >> strPath;

				CTile* pTile = CTile::Create(strTag, strPath, tInfo.x, tInfo.y);
				if (pTile == nullptr)
				{
					SafeDelete(pMap);
					return E_FAIL;
				}

				if (FAILED(pMap->Add_Tile(pTile)))
				{
					SafeDelete(pMap);
					return E_FAIL;
				}
			}
		}
		else
		{
			// 충돌
			int iCnt = 0;
			wstring strTemp = L"";
			fin >> iCnt >> strTemp;

			for (int i = 0; i < iCnt; ++i)
			{
				int iCollType;
				RECT tRect = {};
				fin >> iCollType >> tRect.left >> tRect.right >> tRect.top >> tRect.bottom;

				COLL_RECT* pRect = new COLL_RECT;
				pRect->iType = (COLL_TYPE)iCollType;
				pRect->tRect = tRect;

				if (FAILED(pMap->Add_Collision(pRect)))
				{
					SafeDelete(pMap);
					return E_FAIL;
				}
			}
		}
	}

	m_mapGameMap.emplace(strTag, pMap);

	fin.close();

	return NOERROR;
}

CMap* CMapManager::Find_Map(wstring strTag)
{
	auto iter = m_mapGameMap.find(strTag);

	if (iter == m_mapGameMap.end())
		return nullptr;

	return iter->second;
}

HRESULT CMapManager::Load_MapPath(wstring strPath)
{
	std::locale::global(std::locale("Korean"));
#ifdef _UNICODE
	wifstream fin;
#else
	wifstream fin;
#endif // _UNICODE

	fin.open(strPath);

	if (fin.fail())
		return E_FAIL;

	wstring strMapTag = L"";
	wstring strMapPath = L"";

	while (true)
	{
		fin >> strMapTag >> strMapPath;

		if (fin.eof())
			break;

		if (FAILED(Load_Map(strMapTag, strMapPath)))
			return E_FAIL;
	}

	fin.close();

	return NOERROR;
}

void CMapManager::Free()
{
	for (auto& iter : m_mapGameMap)
		SafeDelete(iter.second);
	m_mapGameMap.clear();
}
