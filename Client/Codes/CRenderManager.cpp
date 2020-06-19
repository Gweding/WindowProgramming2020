#include "stdafx.h"
#include "CRenderManager.h"

IMPLEMENT_SINGLETON(CRenderManager)

CRenderManager::CRenderManager()
{
}

CRenderManager::~CRenderManager()
{
	if (!m_RenderLst.empty())
		m_RenderLst.clear();
}

HRESULT CRenderManager::RenderObject(HDC hdc)
{
	OBJITER iter_begin = m_RenderLst.begin();
	OBJITER iter_end = m_RenderLst.end();

	for (; iter_begin != iter_end; ++iter_begin)
		(*iter_begin)->Render_GameObj(hdc);

	m_RenderLst.clear();
	if (!m_RenderLst.empty())
		return E_FAIL;

	return NOERROR;
}

HRESULT CRenderManager::AddBack_RenderList(CGameObj* pGameObj)
{
	if (pGameObj == nullptr)
		return E_FAIL;

	m_RenderLst.emplace_back(pGameObj);

	return NOERROR;
}

HRESULT CRenderManager::AddFront_RenderList(CGameObj* pGameObj)
{
	if (pGameObj == nullptr)
		return E_FAIL;

	m_RenderLst.emplace_front(pGameObj);

	return NOERROR;
}
