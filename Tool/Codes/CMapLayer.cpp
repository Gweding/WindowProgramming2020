#include "pch.h"
#include "CMapLayer.h"
#include "ToolView.h"
#include "MainFrm.h"
#include "CToolMenu.h"

CMapLayer::CMapLayer()
{
}

CMapLayer::~CMapLayer()
{
	Free();
}

HRESULT CMapLayer::Ready_GameObj()
{
	CGameObj::Ready_GameObj();

	m_eType = LAYER_BACK;
	m_strLayerTag = L"Layer";
	m_strSpriteKey = L"Default";
	m_strSpritePath = L"../../Binary/Resources/Default.png";
	m_tInfo.cx = 1280;
	m_tInfo.cy = 720;
	m_tInfo.x = m_tInfo.cx * 0.5f;
	m_tInfo.y = m_tInfo.cy * 0.5f;

	m_fSize[0] = 1.f;
	m_fSize[1] = 1.f;

	m_tViewRect.left = 0;
	m_tViewRect.top = 0;
	m_tViewRect.right = TOOLCX;
	m_tViewRect.bottom = TOOLCY;

	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CToolMenu* pMenu = dynamic_cast<CToolMenu*>(pFrameWnd->m_WndSplit.GetPane(0, 0));
	m_pDialog = pMenu->m_pScene;

	Update_DialogData();
	CGameObj::Update_Rect();

	return NOERROR;
}

INT CMapLayer::Update_GameObj(const float& fTimeDelta)
{
	switch (m_eType)
	{
	case LAYER_BACK:
		return Update_BackLayer(fTimeDelta);
	case LAYER_OBJECT:
		return Update_ObjectLayer(fTimeDelta);
	case LAYER_TILE:
		return Update_TileLayer(fTimeDelta);
	case LAYER_COLL:
		return Update_CollisionLayer(fTimeDelta);
	default:
		return 0;
	}
}

void CMapLayer::Render_GameObj(HDC hdc)
{
	if (!m_bRender)
		return;

	switch (m_eType)
	{
	case LAYER_BACK:
		return Render_BackLayer(hdc);
	case LAYER_OBJECT:
		return Render_ObjectLayer(hdc);
	case LAYER_TILE:
		return Render_TileLayer(hdc);
	case LAYER_COLL:
		return Render_CollisionLayer(hdc);
	default:
		return;
	}
}

INT CMapLayer::Update_BackLayer(const float& fTimeDelta)
{
	if (m_pKeyMgr->KeyDown(KEY_R))
	{
		m_tInfo.x = m_tInfo.cx * m_fSize[0] * 0.5f;
		m_tInfo.y = m_tInfo.cy * m_fSize[1] * 0.5f;
	}
	if (m_pKeyMgr->KeyPressing(KEY_W))
		m_tInfo.y -= fTimeDelta * 100.f;
	if (m_pKeyMgr->KeyPressing(KEY_S))
		m_tInfo.y += fTimeDelta * 100.f;
	if (m_pKeyMgr->KeyPressing(KEY_A))
		m_tInfo.x -= fTimeDelta * 100.f;
	if (m_pKeyMgr->KeyPressing(KEY_D))
		m_tInfo.x += fTimeDelta * 100.f;

	return 0;
}

INT CMapLayer::Update_ObjectLayer(const float& fTimeDelta)
{
	POINT pt = {};
	Update_Rect();
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tViewRect, pt))
	{
		if (m_pKeyMgr->KeyPressing(KEY_LBUTTON))
		{
			m_tInfo.x = (float)pt.x + CScrollManager::GetScrollPos(0);
			m_tInfo.y = (float)pt.y + CScrollManager::GetScrollPos(1);
		}
	}

	if (m_pKeyMgr->KeyDown(KEY_R))
	{
		m_tInfo.x = m_tInfo.cx * m_fSize[0] * 0.5f;
		m_tInfo.y = m_tInfo.cy * m_fSize[1] * 0.5f;
	}
	if (m_pKeyMgr->KeyPressing(KEY_W))
		m_tInfo.y -= fTimeDelta * 100.f;
	if (m_pKeyMgr->KeyPressing(KEY_S))
		m_tInfo.y += fTimeDelta * 100.f;
	if (m_pKeyMgr->KeyPressing(KEY_A))
		m_tInfo.x -= fTimeDelta * 100.f;
	if (m_pKeyMgr->KeyPressing(KEY_D))
		m_tInfo.x += fTimeDelta * 100.f;

	return 0;
}

INT CMapLayer::Update_TileLayer(const float& fTimeDelta)
{
	POINT pt = {};
	Update_Rect();
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tViewRect, pt))
	{
		if (m_pKeyMgr->KeyDown(KEY_LBUTTON))
		{
			if (m_strTileKey != L"")
			{
				if (!m_pResourceMgr->Check_Sprite(m_strTilePath))
					m_pResourceMgr->Load_Sprite(m_strTilePath, m_strTileKey);

				int iIndexX = int((pt.x + CScrollManager::GetScrollPos(0)) / TILE_SIZE);
				int iIndexY = int((pt.y + CScrollManager::GetScrollPos(1)) / TILE_SIZE);
				CTile* pTile = CTile::Create(m_strTileKey, m_strTilePath, iIndexX * TILE_SIZE + (TILE_SIZE * 0.5f), iIndexY * TILE_SIZE + (TILE_SIZE * 0.5f));
				m_TileList.emplace_back(pTile);
			}
		}
	}

	list<CTile*>::iterator iter_begin;
	list<CTile*>::iterator iter_end;

	iter_begin = m_TileList.begin();
	iter_end = m_TileList.end();

	for (; iter_begin != iter_end; )
	{
		int iEvent = (*iter_begin)->Update_GameObj(fTimeDelta);

		if (OBJ_DEAD == iEvent)
		{
			SafeDelete(*iter_begin);
			iter_begin = m_TileList.erase(iter_begin);
		}
		else
			++iter_begin;
	}

	return 0;
}

INT CMapLayer::Update_CollisionLayer(const float& fTimeDelta)
{
	POINT pt = {};
	Update_Rect();
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tViewRect, pt))
	{
		if (m_pKeyMgr->KeyDown(KEY_LBUTTON))
		{
			m_bAddRect = true;
			m_tAddPoint[0] = { pt.x + (LONG)CScrollManager::GetScrollPos(0), pt.y + (LONG)CScrollManager::GetScrollPos(1) };
		}

		if (m_pKeyMgr->KeyPressing(KEY_LBUTTON))
		{
			m_tAddPoint[1] = { pt.x + (LONG)CScrollManager::GetScrollPos(0), pt.y + (LONG)CScrollManager::GetScrollPos(1) };
		}

		if (m_pKeyMgr->KeyUp(KEY_LBUTTON))
		{
			m_bAddRect = false;
			m_tAddPoint[1] = { pt.x + (LONG)CScrollManager::GetScrollPos(0), pt.y + (LONG)CScrollManager::GetScrollPos(1) };

			RECT temp;
			if (m_tAddPoint[0].x < m_tAddPoint[1].x)
			{
				temp.left = m_tAddPoint[0].x;
				temp.right = m_tAddPoint[1].x;
			}
			else
			{
				temp.left = m_tAddPoint[1].x;
				temp.right = m_tAddPoint[0].x;
			}

			if (m_tAddPoint[0].y < m_tAddPoint[1].y)
			{
				temp.top = m_tAddPoint[0].y;
				temp.bottom = m_tAddPoint[1].y;
			}
			else
			{
				temp.top = m_tAddPoint[1].y;
				temp.bottom = m_tAddPoint[0].y;
			}

			COLL_RECT* pRect = new COLL_RECT;
			pRect->tRect.left = temp.left;
			pRect->tRect.right = temp.right;
			pRect->tRect.top = temp.top;
			pRect->tRect.bottom = temp.bottom;
			pRect->iType = (COLL_TYPE)m_pDialog->m_CollTypeCombo.GetCurSel();

			m_vecColl.push_back(pRect);

			Update_CollListData();
		}

		if (m_pKeyMgr->KeyDown(KEY_RBUTTON))
		{
			m_iFixIndex = m_pDialog->m_CollListbox.GetCurSel();
			if (m_iFixIndex != -1)
				m_tAddPoint[0] = { pt.x + (LONG)CScrollManager::GetScrollPos(0), pt.y + (LONG)CScrollManager::GetScrollPos(1) };
		}

		if (m_pKeyMgr->KeyPressing(KEY_RBUTTON))
		{
			if (m_iFixIndex != -1)
			{
				m_pDialog->m_CollListbox.SetCurSel(m_iFixIndex);
				m_tAddPoint[1] = { pt.x + (LONG)CScrollManager::GetScrollPos(0), pt.y + (LONG)CScrollManager::GetScrollPos(1) };
				RECT temp;
				if (m_tAddPoint[0].x < m_tAddPoint[1].x)
				{
					temp.left = m_tAddPoint[0].x;
					temp.right = m_tAddPoint[1].x;
				}
				else
				{
					temp.left = m_tAddPoint[1].x;
					temp.right = m_tAddPoint[0].x;
				}

				if (m_tAddPoint[0].y < m_tAddPoint[1].y)
				{
					temp.top = m_tAddPoint[0].y;
					temp.bottom = m_tAddPoint[1].y;
				}
				else
				{
					temp.top = m_tAddPoint[1].y;
					temp.bottom = m_tAddPoint[0].y;
				}

				m_vecColl[m_iFixIndex]->tRect = temp;
				Update_CollListData();
			}
		}

		if (m_pKeyMgr->KeyUp(KEY_RBUTTON))
		{
			if (m_iFixIndex != -1)
			{
				m_pDialog->m_CollListbox.SetCurSel(m_iFixIndex);
				m_tAddPoint[1] = { pt.x + (LONG)CScrollManager::GetScrollPos(0), pt.y + (LONG)CScrollManager::GetScrollPos(1) };

				RECT temp;
				if (m_tAddPoint[0].x < m_tAddPoint[1].x)
				{
					temp.left = m_tAddPoint[0].x;
					temp.right = m_tAddPoint[1].x;
				}
				else
				{
					temp.left = m_tAddPoint[1].x;
					temp.right = m_tAddPoint[0].x;
				}

				if (m_tAddPoint[0].y < m_tAddPoint[1].y)
				{
					temp.top = m_tAddPoint[0].y;
					temp.bottom = m_tAddPoint[1].y;
				}
				else
				{
					temp.top = m_tAddPoint[1].y;
					temp.bottom = m_tAddPoint[0].y;
				}

				m_vecColl[m_iFixIndex]->tRect = temp;
				Update_CollListData();
				m_pDialog->m_CollListbox.SetCurSel(m_iFixIndex);
				m_iFixIndex = -1;
			}
		}
	}

	return 0;
}

void CMapLayer::Render_BackLayer(HDC hdc)
{
	CGameObj::Update_Rect();
	CImage* pImage = m_pResourceMgr->Find_Sprite(m_strSpriteKey);
	pImage->Draw(hdc, m_tRect.left - int(CScrollManager::GetScrollPos(0) * m_fSpeed)
										, m_tRect.top - int(CScrollManager::GetScrollPos(1) * m_fSpeed)
										, int(m_tInfo.cx * m_fSize[0]), int(m_tInfo.cy * m_fSize[1]));

	cout << m_tInfo.x << " // " << m_tInfo.y << " // " << m_tRect.left << " // " << m_tRect.top << endl;
}

void CMapLayer::Render_ObjectLayer(HDC hdc)
{
	CGameObj::Update_Rect();
	CImage* pImage = m_pResourceMgr->Find_Sprite(m_strSpriteKey);
	pImage->Draw(hdc, m_tRect.left - int(CScrollManager::GetScrollPos(0) * m_fSpeed)
		, m_tRect.top - int(CScrollManager::GetScrollPos(1) * m_fSpeed)
		, int(m_tInfo.cx * m_fSize[0]), int(m_tInfo.cy * m_fSize[1]));
}

void CMapLayer::Render_TileLayer(HDC hdc)
{
	for (auto pTile : m_TileList)
		pTile->Render_GameObj(hdc);
}

void CMapLayer::Render_CollisionLayer(HDC hdc)
{
	if (m_bAddRect)
	{
		RECT temp;
		if (m_tAddPoint[0].x < m_tAddPoint[1].x)
		{
			temp.left = m_tAddPoint[0].x;
			temp.right = m_tAddPoint[1].x;
		}
		else
		{
			temp.left = m_tAddPoint[1].x;
			temp.right = m_tAddPoint[0].x;
		}

		if (m_tAddPoint[0].y < m_tAddPoint[1].y)
		{
			temp.top = m_tAddPoint[0].y;
			temp.bottom = m_tAddPoint[1].y;
		}
		else
		{
			temp.top = m_tAddPoint[1].y;
			temp.bottom = m_tAddPoint[0].y;
		}

		m_hPen = CreatePen(PS_SOLID, 3, RGB(30, 30, 30));
		m_hOldPen = SelectObject(hdc, m_hPen);
		m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		m_hOldBrush = SelectObject(hdc, m_hBrush);
		Rectangle(hdc, temp.left - int(CScrollManager::GetScrollPos(0)),
									temp.top - int(CScrollManager::GetScrollPos(1)),
									temp.right - int(CScrollManager::GetScrollPos(0)), 
									temp.bottom - int(CScrollManager::GetScrollPos(1)));
		SelectObject(hdc, m_hOldPen);
		SelectObject(hdc, m_hOldBrush);
		DeleteObject(m_hBrush);
		DeleteObject(m_hPen);
	}

	for (size_t i = 0; i < m_vecColl.size(); ++i)
	{
		int iPen = 2;
		int iSel = m_pDialog->m_CollListbox.GetCurSel();
		if (i == iSel)
			iPen = 3;

		if (m_vecColl[i]->iType == COLL_ALL)
			m_hPen = CreatePen(PS_SOLID, iPen, RGB(255, 0, 0));
		else if (m_vecColl[i]->iType == COLL_JUMP)
			m_hPen = CreatePen(PS_SOLID, iPen, RGB(0, 255, 0));
		else if (m_vecColl[i]->iType == COLL_INTERACT)
			m_hPen = CreatePen(PS_SOLID, iPen, RGB(0, 0, 255));
		else
			m_hPen = CreatePen(PS_SOLID, iPen, RGB(255, 255, 255));
		m_hOldPen = SelectObject(hdc, m_hPen);
		m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		m_hOldBrush = SelectObject(hdc, m_hBrush);
		Rectangle(hdc, m_vecColl[i]->tRect.left - int(CScrollManager::GetScrollPos(0)),
									m_vecColl[i]->tRect.top - int(CScrollManager::GetScrollPos(1)),
									m_vecColl[i]->tRect.right - int(CScrollManager::GetScrollPos(0)),
									m_vecColl[i]->tRect.bottom - int(CScrollManager::GetScrollPos(1)));
		SelectObject(hdc, m_hOldPen);
		SelectObject(hdc, m_hOldBrush);
		DeleteObject(m_hBrush);
		DeleteObject(m_hPen);
	}
}

HRESULT CMapLayer::Adjust_DialogData()
{
	m_pDialog->UpdateData(TRUE);
	m_strLayerTag = m_pDialog->m_strLayerTag.GetString();
	m_strSpriteKey = m_pDialog->m_strBackImage.GetString();
	m_eType = (LAYER_TYPE)m_pDialog->m_LayerTypeCombo.GetCurSel();
	m_fSpeed = m_pDialog->m_fBackSpeed;
	m_fSize[0] = m_pDialog->m_fSizeX;
	m_fSize[1] = m_pDialog->m_fSizeY;
	m_pDialog->UpdateData(FALSE);

	if (m_eType == LAYER_TILE)
		m_pDialog->Set_TileLayer_Option(true);
	else
		m_pDialog->Set_TileLayer_Option(false);

	return NOERROR;
}

HRESULT CMapLayer::Change_Image(wstring strTag, wstring strPath)
{
	if (!m_pResourceMgr->Check_Sprite(strTag))
	{
		if (FAILED(m_pResourceMgr->Load_Sprite(strPath, strTag)))
			return E_FAIL;
	}

	m_strSpriteKey = strTag;
	m_strSpritePath = strPath;

	CImage* pImage = m_pResourceMgr->Find_Sprite(strTag);
	m_tInfo.cx = (float)pImage->GetWidth();
	m_tInfo.cy = (float)pImage->GetHeight();
	m_tInfo.x = m_tInfo.cx * 0.5f;
	m_tInfo.y = m_tInfo.cy * 0.5f;

	Update_DialogData();

	return NOERROR;
}

HRESULT CMapLayer::Change_CollType(int iIndex)
{
	if (iIndex > m_vecColl.size())
		return E_FAIL;

	m_vecColl[iIndex]->iType = (COLL_TYPE)m_pDialog->m_CollTypeCombo.GetCurSel();
	Update_CollListData();

	return NOERROR;
}

HRESULT CMapLayer::Delete_Coll(int iIndex)
{
	if (iIndex > m_vecColl.size())
		return E_FAIL;

	auto iter = m_vecColl.begin();
	iter += iIndex;
	SafeDelete(*iter);
	m_vecColl.erase(iter);

	m_pDialog->m_CollListbox.DeleteString(iIndex);
	Update_CollListData();

	return NOERROR;
}

void CMapLayer::Update_DialogData()
{
	m_pDialog->UpdateData(TRUE);
	m_pDialog->m_strLayerTag = m_strLayerTag.c_str();
	m_pDialog->m_strBackImage = m_strSpriteKey.c_str();;
	m_pDialog->m_LayerTypeCombo.SetCurSel((int)m_eType);
	m_pDialog->m_fBackSpeed = m_fSpeed;
	m_pDialog->m_fSizeX = m_fSize[0];
	m_pDialog->m_fSizeY = m_fSize[1];

	if (m_eType == LAYER_TILE)
		m_pDialog->Set_TileLayer_Option(true);
	else
		m_pDialog->Set_TileLayer_Option(false);

	m_pDialog->UpdateData(FALSE);
}

void CMapLayer::Update_CollListData()
{
	m_pDialog->m_CollListbox.ResetContent();
	if (m_eType == LAYER_COLL)
	{
		for (size_t i = 0; i < m_vecColl.size(); ++i)
		{
			CString strOutput = L"";
			switch (m_vecColl[i]->iType)
			{
			case COLL_ALL:
				strOutput.Format(L" %d-모두충돌", i);
				break;
			case COLL_JUMP:
				strOutput.Format(L" %d-점프충돌", i);
				break;
			case COLL_INTERACT:
				strOutput.Format(L" %d-상호작용", i);
				break;
			default:
				break;
			}
			m_pDialog->m_CollListbox.AddString(strOutput);
		}
	}
}

HRESULT CMapLayer::Save_Layer(wofstream& fout)
{
	switch (m_eType)
	{
	case LAYER_BACK:
		return Save_ImageLayer(fout);
	case LAYER_OBJECT:
		return Save_ObjectLayer(fout);
	case LAYER_TILE:
		return Save_TileLayer(fout);
	case LAYER_COLL:
		return Save_CollLayer(fout);
	default:
		return 0;
	}

	return NOERROR;
}

HRESULT CMapLayer::Save_ImageLayer(wofstream& fout)
{
	fout << m_eType << endl;
	fout << m_strLayerTag << " " << m_strSpriteKey << " "
		<< m_fSpeed << " " << m_fSize[0] << " " << m_fSize[1] << " " << m_strSpritePath << " " << m_tInfo.x << " " << m_tInfo.y << endl;

	return NOERROR;
}

HRESULT CMapLayer::Save_ObjectLayer(wofstream& fout)
{
	fout << m_eType << endl;
	fout << m_strLayerTag << " " << m_strSpriteKey << " " << m_fSpeed << " " 
			<< m_fSize[0] << " " << m_fSize[1] << " " << m_strSpritePath << " " << m_tInfo.x << " " << m_tInfo.y << endl;

	return NOERROR;
}

HRESULT CMapLayer::Save_TileLayer(wofstream& fout)
{
	fout << m_eType << endl;
	fout << m_TileList.size() << endl;
	fout << m_strLayerTag << endl;

	for (auto pTile : m_TileList)
	{
		fout << pTile->m_strTag << " " << pTile->m_tInfo.x << " " << pTile->m_tInfo.y << " "
			<< pTile->m_tInfo.cx << " " << pTile->m_tInfo.cy << " " << pTile->m_strPath << endl;
	}

	return NOERROR;
}

HRESULT CMapLayer::Save_CollLayer(wofstream& fout)
{
	fout << m_eType << endl;
	fout << m_vecColl.size() << endl;
	fout << m_strLayerTag << endl;

	for (auto pColl : m_vecColl)
	{
		fout << pColl->iType << " " << pColl->tRect.left << " " << pColl->tRect.right << " "
			<< pColl->tRect.top << " " << pColl->tRect.bottom << endl;
}

	return NOERROR;
}

HRESULT CMapLayer::Load_ImageLayer(wifstream& fin)
{
	fin >> m_strLayerTag >> m_strSpriteKey >> m_fSpeed >> m_fSize[0] >> m_fSize[1] >> m_strSpritePath >> m_tInfo.x >> m_tInfo.y;

	if (!m_pResourceMgr->Check_Sprite(m_strSpriteKey))
		m_pResourceMgr->Load_Sprite(m_strSpritePath, m_strSpriteKey);

	CImage* pImage = m_pResourceMgr->Find_Sprite(m_strSpriteKey);
	if (pImage != nullptr)
	{
		m_tInfo.cx = (float)pImage->GetWidth();
		m_tInfo.cy = (float)pImage->GetHeight();
	}

	return NOERROR;
}

HRESULT CMapLayer::Load_ObjectLayer(wifstream& fin)
{
	fin >> m_strLayerTag >> m_strSpriteKey >> m_fSpeed >> m_fSize[0] >> m_fSize[1] >> m_strSpritePath >> m_tInfo.x >> m_tInfo.y;

	if (!m_pResourceMgr->Check_Sprite(m_strSpriteKey))
		m_pResourceMgr->Load_Sprite(m_strSpritePath, m_strSpriteKey);

	CImage* pImage = m_pResourceMgr->Find_Sprite(m_strSpriteKey);
	if (pImage != nullptr)
	{
		m_tInfo.cx = (float)pImage->GetWidth();
		m_tInfo.cy = (float)pImage->GetHeight();
	}

	return NOERROR;
}

HRESULT CMapLayer::Load_TileLayer(wifstream& fin)
{
	int iCnt = 0;
	fin >> iCnt;
	fin >> m_strLayerTag;

	for (auto pTile : m_TileList)
		SafeDelete(pTile);
	m_TileList.clear();

	INFO tInfo = {};
	wstring strTag = L"";
	wstring strPath = L"";
	for (int i = 0; i < iCnt; ++i)
	{
		fin >> strTag >> tInfo.x >> tInfo.y >> tInfo.cx >> tInfo.cy >> strPath;
		CTile* pTile = CTile::Create(strTag, strPath, tInfo.x, tInfo.y);
		m_TileList.emplace_back(pTile);
	}

	return NOERROR;
}

HRESULT CMapLayer::Load_CollLayer(wifstream& fin)
{
	int iCnt = 0;
	fin >> iCnt;
	fin >> m_strLayerTag;

	for (auto pRect : m_vecColl)
		SafeDelete(pRect);
	m_vecColl.clear();

	int iType;
	RECT tRect;
	for (int i = 0; i < iCnt; ++i)
	{
		fin >> iType >> tRect.left >> tRect.right >> tRect.top >> tRect.bottom;

		COLL_RECT* pRect = new COLL_RECT;
		pRect->iType = (COLL_TYPE)iType;
		pRect->tRect = tRect;
		m_vecColl.push_back(pRect);
	}

	return NOERROR;
}

CMapLayer* CMapLayer::Create()
{
	CMapLayer* pInstance = new CMapLayer;
	if (FAILED(pInstance->Ready_GameObj()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CMapLayer::Free()
{
	for (auto pTile : m_TileList)
		SafeDelete(pTile);
	m_TileList.clear();

	for (auto pRect : m_vecColl)
		SafeDelete(pRect);
	m_vecColl.clear();
}
