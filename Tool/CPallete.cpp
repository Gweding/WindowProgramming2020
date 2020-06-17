#include "pch.h"
#include "CPallete.h"
#include "MainFrm.h"
#include "CMapLayer.h"
#include "CToolMenu.h"
#include "CSceneDialog.h"
#include "CScene.h"

CPallete::CPallete()
{
}

CPallete::~CPallete()
{
}

HRESULT CPallete::Ready_GameObj()
{
	CGameObj::Ready_GameObj();

	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CToolMenu* pMenu = dynamic_cast<CToolMenu*>(pFrameWnd->m_WndSplit.GetPane(0, 0));
	CDC* pCDC = pMenu->m_pScene->m_TilePicCtrl.GetDC();
	m_PicCtrl = pCDC->GetSafeHdc();
	m_PicHwnd = pMenu->m_pScene->m_TilePicCtrl.GetSafeHwnd();

	m_tSelected.x = 0;
	m_tSelected.y = 0;
	m_tSelected.cx = TILE_SIZE;
	m_tSelected.cy = TILE_SIZE;

	m_pResourceMgr->Load_Bmp(L"../Binary/Resources/Back.bmp", L"Pallete_Back");
	m_pResourceMgr->Load_Bmp(L"../Binary/Resources/Back.bmp", L"Pallete_MemDC");

	return NOERROR;
}

INT CPallete::Update_GameObj(const float& fTimeDelta)
{
	POINT pt = {};
	Update_Rect();
	GetCursorPos(&pt);
	ScreenToClient(m_PicHwnd, &pt);

	for (auto pTile : m_TileList)
	{
		pTile->tRect.left = LONG(pTile->x);
		pTile->tRect.top = LONG(pTile->y);
		pTile->tRect.right = LONG(pTile->x + pTile->cx);
		pTile->tRect.bottom = LONG(pTile->y + pTile->cy);

		if (PtInRect(&pTile->tRect, pt))
		{
			if (m_pKeyMgr->KeyDown(KEY_LBUTTON))
			{
				m_tSelected = *pTile;
				CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
				CToolMenu* pMenu = dynamic_cast<CToolMenu*>(pFrameWnd->m_WndSplit.GetPane(0, 0));
				int iSel = pMenu->m_pScene->m_LayerListbox.GetCurSel();
				if (iSel == -1)
					MessageBox(g_hWnd, L"레이어를 선택 해주세용~!", L"ERROR", MB_OK);
				else
				{
					pMenu->m_pScene->m_pCurrScene->m_vecLayer[iSel]->m_strTileKey = pTile->strTag.c_str();
					pMenu->m_pScene->m_pCurrScene->m_vecLayer[iSel]->m_strTilePath = pTile->strPath.c_str();
				}
			}
		}
	}

	return 0;
}

void CPallete::Render_GameObj(HDC hdc)
{
	HDC hBack = m_pResourceMgr->Find_Bmp(L"Pallete_Back");
	HDC hMemDC = m_pResourceMgr->Find_Bmp(L"Pallete_MemDC");

	BitBlt(hBack, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	//

	for (auto pTile : m_TileList)
	{
		CImage* pImage = m_pResourceMgr->Find_Sprite(pTile->strTag);
		if (pImage == nullptr)
			continue;
		pImage->Draw(hBack, (int)pTile->x, (int)pTile->y, (int)pTile->cx, (int)pTile->cy);
	}

	CImage* pImage = m_pResourceMgr->Find_Sprite(L"SelectedTile");
	if (pImage == nullptr)
		return;
	pImage->Draw(hBack, (int)m_tSelected.x, (int)m_tSelected.y, (int)m_tSelected.cx, (int)m_tSelected.cy);

	//

	BitBlt(m_PicCtrl, 0, 0, WINCX, WINCY, hBack, 0, 0, SRCCOPY);
}

HRESULT CPallete::Add_Tile(wstring strPath, wstring strTag)
{
	TILE* pTile = new TILE;
	pTile->strTag = strTag;
	pTile->strPath = strPath;

	int iIndex = (int)m_TileList.size();
	pTile->cx = TILE_SIZE;
	pTile->cy = TILE_SIZE;
	pTile->x = (float)(iIndex % 8) * TILE_SIZE;
	pTile->y = (float)(iIndex / 8) * TILE_SIZE;

	m_TileList.emplace_back(pTile);

	return NOERROR;
}

HRESULT CPallete::Clear_Pallete()
{
	for (auto pTile : m_TileList)
		SafeDelete(pTile);
	m_TileList.clear();

	return NOERROR;
}

HRESULT CPallete::Save_Pallete(wstring strPath)
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

	for (auto pTile : m_TileList)
		fout << pTile->strTag << " " << pTile->strPath << " " << pTile->x << " " << pTile->y << " " << pTile->cx << " " << pTile->cy << endl;

	fout.close();

	return NOERROR;
}

HRESULT CPallete::Load_Pallete(wstring strPath)
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

	Clear_Pallete();

	while (true)
	{
		TILE* pTile = new TILE;

		fin >> pTile->strTag >> pTile->strPath >> pTile->x >> pTile->y >> pTile->cx >> pTile->cy;

		if (!m_pResourceMgr->Check_Sprite(pTile->strTag))
			m_pResourceMgr->Load_Sprite(pTile->strPath, pTile->strTag);

		if (fin.eof())
		{
			SafeDelete(pTile);
			break;
		}

		m_TileList.emplace_back(pTile);
	}

	fin.close();

	return NOERROR;
}

CPallete* CPallete::Create()
{
	CPallete* pInstance = new CPallete;
	if (FAILED(pInstance->Ready_GameObj()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CPallete::Free()
{
	for (auto pTile : m_TileList)
		SafeDelete(pTile);
	m_TileList.clear();
}
