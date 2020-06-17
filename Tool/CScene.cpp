#include "pch.h"
#include "CScene.h"

#include "CTile.h"
#include "CGrid.h"
#include "CPallete.h"
#include "CMapLayer.h"
#include "MainFrm.h"
#include "CToolMenu.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	Free();
}

HRESULT CScene::Ready_GameObj()
{
	CGameObj::Ready_GameObj();

	m_pGrid = CGrid::Create();
	if (m_pGrid == nullptr)
		return E_FAIL;

	m_pPallete = CPallete::Create();
	if (m_pPallete == nullptr)
		return E_FAIL;

	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CToolMenu* pMenu = dynamic_cast<CToolMenu*>(pFrameWnd->m_WndSplit.GetPane(0, 0));
	m_pLayerList = &pMenu->m_pScene->m_LayerListbox;
	m_pLayerTypeCombo = &pMenu->m_pScene->m_LayerTypeCombo;

	return NOERROR;
}

INT CScene::Update_GameObj(const float& fTimeDelta)
{
	int iSel = m_pLayerList->GetCurSel();
	if (iSel != -1)
		m_vecLayer[iSel]->Update_GameObj(fTimeDelta);

	m_pGrid->Update_GameObj(fTimeDelta);
	m_pPallete->Update_GameObj(fTimeDelta);

	return 0;
}

void CScene::Render_GameObj(HDC hdc)
{
	for (auto pLayer : m_vecLayer)
		pLayer->Render_GameObj(hdc);

	m_pGrid->Render_GameObj(hdc);
	m_pPallete->Render_GameObj(hdc);
}

HRESULT CScene::Add_Layer()
{
	CMapLayer* pLayer = CMapLayer::Create();
	if (pLayer == nullptr)
		return E_FAIL;

	m_vecLayer.push_back(pLayer);

	Reset_ListBox();

	return NOERROR;
}

HRESULT CScene::Delete_Layer(int iIndex)
{
	if (iIndex > m_vecLayer.size())
		return E_FAIL;

	auto iter = m_vecLayer.begin();
	iter += iIndex;
	SafeDelete(*iter);
	m_vecLayer.erase(iter);

	m_pLayerList->DeleteString(iIndex);

	return NOERROR;
}

HRESULT CScene::Adjust_Layer(int iIndex)
{
	if (iIndex > m_vecLayer.size())
		return E_FAIL;

	if (FAILED(m_vecLayer[iIndex]->Adjust_DialogData()))
		return E_FAIL;

	Reset_ListBox();
	m_pLayerList->SetCurSel(iIndex);

	return NOERROR;
}

HRESULT CScene::Layer_Up(int iIndex)
{
	if (iIndex > m_vecLayer.size())
		return E_FAIL;

	int iSelIndex = iIndex;
	int iNewIndex = iIndex - 1;
	if (iNewIndex < 0)
		iNewIndex = (int)m_vecLayer.size() - 1;

	CMapLayer* pSelFrame = m_vecLayer[iIndex];
	CMapLayer* pSwapFrame = m_vecLayer[iNewIndex];

	m_vecLayer[iNewIndex] = pSelFrame;
	m_vecLayer[iSelIndex] = pSwapFrame;

	Reset_ListBox();

	m_pLayerList->SetCurSel(iNewIndex);

	return NOERROR;
}

HRESULT CScene::Layer_Down(int iIndex)
{
	if (iIndex > m_vecLayer.size())
		return E_FAIL;

	int iSelIndex = iIndex;
	int iNewIndex = iIndex + 1;
	if (iNewIndex > m_vecLayer.size() - 1)
		iNewIndex = 0;

	CMapLayer* pSelFrame = m_vecLayer[iIndex];
	CMapLayer* pSwapFrame = m_vecLayer[iNewIndex];

	m_vecLayer[iNewIndex] = pSelFrame;
	m_vecLayer[iSelIndex] = pSwapFrame;

	Reset_ListBox();

	m_pLayerList->SetCurSel(iNewIndex);

	return NOERROR;
}

HRESULT CScene::Change_Image(int iIndex, wstring strTag, wstring strPath)
{
	if (iIndex > m_vecLayer.size())
		return E_FAIL;

	return m_vecLayer[iIndex]->Change_Image(strTag, strPath);
}

HRESULT CScene::Change_CollType(int iLayerIndex, int iCollIndex)
{
	if (iLayerIndex > m_vecLayer.size())
		return E_FAIL;

	return m_vecLayer[iLayerIndex]->Change_CollType(iCollIndex);
}

HRESULT CScene::Save_Scene(wstring strPath)
{
	std::locale::global(std::locale("Korean"));
#ifdef _UNICODE
	wofstream fout;
#else
	ofstream fout;
#endif // _UNICODE

	fout.open(strPath);

	if (fout.fail())
		return E_FAIL;

	for (auto pLayer : m_vecLayer)
		pLayer->Save_Layer(fout);

	fout.close();

	return NOERROR;
}

HRESULT CScene::Load_Scene(wstring strPath)
{
	std::locale::global(std::locale("Korean"));
#ifdef _UNICODE
	wifstream fin;
#else
	wifstream fin;
#endif // _UNICODE

	fin.open(strPath);

	if (fin.fail())
		return E_FAIL;;

	CMapLayer* pLayer = nullptr;
	
	while (true)
	{
		int iType;
		fin >> iType;

		if (fin.eof())
			break;

		pLayer = CMapLayer::Create();
		pLayer->m_eType = (LAYER_TYPE)iType;
		switch ((LAYER_TYPE)iType)
		{
		case LAYER_BACK:
			pLayer->Load_ImageLayer(fin);
			break;
		case LAYER_OBJECT:
			pLayer->Load_ObjectLayer(fin);
			break;
		case LAYER_TILE:
			pLayer->Load_TileLayer(fin);
			break;
		case LAYER_COLL:
			pLayer->Load_CollLayer(fin);
			break;
		}
		m_vecLayer.push_back(pLayer);
	}

	fin.close();

	Reset_ListBox();

	return NOERROR;
}

void CScene::Reset_ListBox()
{
	m_pLayerList->ResetContent();

	for (auto pLayer : m_vecLayer)
		m_pLayerList->AddString(pLayer->m_strLayerTag.c_str());

	Set_HorizontalScroll();
}

void CScene::Set_HorizontalScroll()
{
	int iCX = 0;
	CSize size;
	CString strName = L"";

	CDC* pDC = m_pLayerList->GetDC();

	for (int i = 0; i < m_pLayerList->GetCount(); ++i)
	{
		m_pLayerList->GetText(i, strName);
		size = pDC->GetTextExtent(strName);

		if (iCX < size.cx)
			iCX = size.cx;
	}

	m_pLayerList->ReleaseDC(pDC);

	if (iCX > m_pLayerList->GetHorizontalExtent())
		m_pLayerList->SetHorizontalExtent(iCX);
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
	for (auto pLayer : m_vecLayer)
		SafeDelete(pLayer);
	m_vecLayer.clear();

	SafeDelete(m_pGrid);
	SafeDelete(m_pPallete);
}
