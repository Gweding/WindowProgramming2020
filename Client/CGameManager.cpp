#include "stdafx.h"
#include "CGameManager.h"

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
