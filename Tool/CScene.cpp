#include "pch.h"
#include "CScene.h"

#include "CGrid.h"
#include "CMapLayer.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	Free();
}

HRESULT CScene::Ready_GameObj()
{
	CMapLayer* pLayer = CMapLayer::Create(LAYER_BACK);
	if (FAILED(Add_Layer(L"Default_Layer", pLayer)))
		return E_FAIL;

	m_pGrid = CGrid::Create();

	return NOERROR;
}

INT CScene::Update_GameObj(const float& fTimeDelta)
{
	m_pGrid->Update_GameObj(fTimeDelta);

	list<CMapLayer*>::iterator iter_begin;
	list<CMapLayer*>::iterator iter_end;

	iter_begin = m_LayerList.begin();
	iter_end = m_LayerList.end();

	for (; iter_begin != iter_end; )
	{
		int iEvent = (*iter_begin)->Update_GameObj(fTimeDelta);

		if (OBJ_DEAD == iEvent)
		{
			SafeDelete(*iter_begin);
			iter_begin = m_LayerList.erase(iter_begin);
		}
		else
			++iter_begin;
	}

	return 0;
}

void CScene::Render_GameObj(HDC hdc)
{
	for (auto& iter : m_LayerList)
		iter->Render_GameObj(hdc);

	m_pGrid->Render_GameObj(hdc);
}

HRESULT CScene::Add_Layer(wstring strTag, CMapLayer* pLayer)
{
	if (pLayer == nullptr)
		return E_FAIL;

	auto iter = m_LayerList.begin();

	for (; iter != m_LayerList.end(); )
	{
		if ((*iter)->m_strTag == strTag)
		{
			MessageBox(g_hWnd, L"이미 존재하는 태그", L"ERROR", MB_OK);
			SafeDelete(pLayer);
			return E_FAIL;
		}

		++iter;
	}

	pLayer->m_strTag = strTag;
	m_LayerList.emplace_back(pLayer);

	return NOERROR;
}

HRESULT CScene::Delete_Layer(wstring strTag)
{
	auto iter = m_LayerList.begin();

	for (; iter != m_LayerList.end(); )
	{
		if ((*iter)->m_strTag == strTag)
		{
			SafeDelete(*iter);
			iter = m_LayerList.erase(iter);
			return NOERROR;
		}

		++iter;
	}

	return NOERROR;
}

CMapLayer* CScene::Get_Layer(wstring strTag)
{
	auto iter = m_LayerList.begin();

	for (; iter != m_LayerList.end(); )
	{
		if ((*iter)->m_strTag == strTag)
			break;

		++iter;
	}

	if (iter == m_LayerList.end())
		return nullptr;

	return (*iter);
}

HRESULT CScene::Update_LayerList(CListBox* pListBox, CMapLayer** ppCurrLayer)
{
	if (pListBox == nullptr)
		return E_FAIL;

	pListBox->ResetContent();
	pListBox->SetCurSel(0);
	*ppCurrLayer = m_LayerList.front();

	for (auto& Mapiter : m_LayerList)
		pListBox->AddString(Mapiter->m_strTag.c_str());

	return NOERROR;
}

CScene* CScene::Create()
{
	CScene* pInstance = new CScene;
	if (FAILED(pInstance->Ready_GameObj()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CScene::Free()
{
	for (auto& Mapiter : m_LayerList)
		SafeDelete(Mapiter);
	m_LayerList.clear();

	SafeDelete(m_pGrid);
}
