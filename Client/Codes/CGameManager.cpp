#include "stdafx.h"
#include "CGameManager.h"

#include "CMap.h"

IMPLEMENT_SINGLETON(CGameManager)

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
	for (int i = 0; i < OBJID::OBJ_END; ++i)
	{
		for_each(m_ObjLst[i].begin(), m_ObjLst[i].end(), SafeDelete<CGameObj*>);
		m_ObjLst[i].clear();
	}
}

HRESULT CGameManager::Update_Object(const float& fTimeDelta)
{
	for (int i = 0; i < OBJID::OBJ_END; ++i)
	{
		OBJITER iter_begin = m_ObjLst[i].begin();
		OBJITER iter_end = m_ObjLst[i].end();

		for (; iter_begin != iter_end; )
		{
			int iEvent = (*iter_begin)->Update_GameObj(fTimeDelta);

			if (OBJ_DEAD == iEvent)
			{
				SafeDelete(*iter_begin);
				iter_begin = m_ObjLst[i].erase(iter_begin);
			}
			else
				++iter_begin;
		}
	}

	return NOERROR;
}

HRESULT CGameManager::Add_GameObject(OBJID eID, CGameObj* pGameObj)
{
	if (nullptr == pGameObj)
		return E_FAIL;

	m_ObjLst[eID].push_back(pGameObj);

	return S_OK;
}

HRESULT CGameManager::PopFront_GameObject(OBJID eID)
{
	if (m_ObjLst[eID].empty())
		return S_OK;

	SafeDelete(m_ObjLst[eID].back());
	m_ObjLst[eID].pop_back();

	return S_OK;
}

HRESULT CGameManager::PopBack_GameObject(OBJID eID)
{
	if (m_ObjLst[eID].empty())
		return S_OK;

	SafeDelete(m_ObjLst[eID].front());
	m_ObjLst[eID].pop_front();

	return S_OK;
}

HRESULT CGameManager::Delete_OBJLIST(OBJID eID)
{
	for_each(m_ObjLst[eID].begin(), m_ObjLst[eID].end(), SafeDelete<CGameObj*>);
	m_ObjLst[eID].clear();

	return S_OK;
}

HRESULT CGameManager::Reset_OBJLIST()
{
	for (int i = 0; i < OBJID::OBJ_END; ++i)
	{
		for_each(m_ObjLst[i].begin(), m_ObjLst[i].end(), SafeDelete<CGameObj*>);
		m_ObjLst[i].clear();
	}

	return NOERROR;
}

HRESULT CGameManager::Set_CurrMap(CMap* pMap)
{
	if (pMap == nullptr)
		return E_FAIL;

	m_pCurrMap = pMap;

	return NOERROR;
}

list<COLL_RECT*>& CGameManager::Get_MapCollider()
{
	// TODO: 여기에 return 문을 삽입합니다.
	return m_pCurrMap->Get_MapCollider();
}

CGameObj* CGameManager::Get_Object(OBJID eID, int iIndex)
{
	if (iIndex > m_ObjLst[eID].size())
		return nullptr;

	if (iIndex == 0)
		return m_ObjLst[eID].front();

	auto iter = m_ObjLst[eID].begin();
	for (int i = 0; i < iIndex; ++i)
		++iter;

	return (*iter);
}
