#include "pch.h"
#include "CAnimation.h"
#include "MainFrm.h"
#include "CMapLayer.h"
#include "CToolMenu.h"
#include "CAnimationDialog.h"

CAnimation::CAnimation()
{
}

CAnimation::~CAnimation()
{
}

HRESULT CAnimation::Ready_GameObj()
{
	CGameObj::Ready_GameObj();

	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CToolMenu* pMenu = dynamic_cast<CToolMenu*>(pFrameWnd->m_WndSplit.GetPane(0, 0));
	CDC* pCDC = pMenu->m_pMain->m_Animation.m_PicCtrl.GetDC();
	pMenu->m_pMain->m_Animation.m_PicCtrl.GetClientRect(&m_tPicRect);
	m_PicHdc = pCDC->GetSafeHdc();
	m_PicHwnd = pMenu->m_pMain->m_Animation.m_PicCtrl.GetSafeHwnd();
	m_FrameList = &pMenu->m_pMain->m_Animation.m_FrameList;

	m_pDialog = &pMenu->m_pMain->m_Animation;

	m_pResourceMgr->Load_Bmp(L"../../Binary/Resources/Back.bmp", L"Animation_Back");
	m_pResourceMgr->Load_Bmp(L"../../Binary/Resources/Back.bmp", L"Animation_MemDC");

	return NOERROR;
}

INT CAnimation::Update_GameObj(const float& fTimeDelta)
{
	for (auto pFrame : m_vecFrame)
	{
		pFrame->tRect.left = LONG(pFrame->x - pFrame->cx * 0.5f);
		pFrame->tRect.top = LONG(pFrame->y - pFrame->cy * 0.5f);
		pFrame->tRect.right = LONG(pFrame->x + pFrame->cx * 0.5f);
		pFrame->tRect.bottom = LONG(pFrame->y + pFrame->cy * 0.5f);
	}

	if (!m_vecFrame.empty())
	{
		if (m_bPlay)
		{
			FRAME* pCurrFrame = nullptr;
			m_fCurrFrame += m_vecFrame[(int)m_fCurrFrame]->fSpeed * fTimeDelta;
			if (m_fCurrFrame > m_vecFrame.size())
				m_fCurrFrame = 0.f;
			m_FrameList->SetCurSel((int)m_fCurrFrame);

			pCurrFrame = m_vecFrame[(int)m_fCurrFrame];
			m_pDialog->UpdateData(TRUE);
			m_pDialog->m_strAnimationTag = pCurrFrame->strTag.c_str();
			m_pDialog->m_fFrameSpeed = pCurrFrame->fSpeed;
			m_pDialog->UpdateData(FALSE);
		}

		POINT pt = {};
		Update_Rect();
		GetCursorPos(&pt);
		ScreenToClient(m_PicHwnd, &pt);

		if (PtInRect(&m_tPicRect, pt))
		{
			if (m_pKeyMgr->KeyDown(KEY_LBUTTON))
			{
				m_bAddRect = true;
				m_tAddPoint[0] = pt;
			}

			if (m_pKeyMgr->KeyPressing(KEY_LBUTTON))
			{
				m_tAddPoint[1] = pt;
			}

			if (m_pKeyMgr->KeyUp(KEY_LBUTTON))
			{
				m_bAddRect = false;
				m_tAddPoint[1] = pt;

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

				if (!m_vecFrame.empty())
				{
					FRAME* pFrame = m_vecFrame[(int)m_fCurrFrame];
					pFrame->tCollRect.left = LONG(temp.left - pFrame->x);
					pFrame->tCollRect.right = LONG(temp.right - pFrame->x);
					pFrame->tCollRect.top = LONG(temp.top - pFrame->y);
					pFrame->tCollRect.bottom = LONG(temp.bottom - pFrame->y);
				}
			}

		}
	}

	return 0;
}

void CAnimation::Render_GameObj(HDC hdc)
{
	HDC hBack = m_pResourceMgr->Find_Bmp(L"Animation_Back");
	HDC hMemDC = m_pResourceMgr->Find_Bmp(L"Animation_MemDC");

	BitBlt(hBack, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	//
	if (!m_vecFrame.empty())
	{
		CImage* pImage = m_pResourceMgr->Find_Sprite(m_vecFrame[(int)m_fCurrFrame]->strTag);
		if (pImage == nullptr)
			return;
		pImage->Draw(hBack, m_vecFrame[(int)m_fCurrFrame]->tRect.left, m_vecFrame[(int)m_fCurrFrame]->tRect.top,
												(int)m_vecFrame[(int)m_fCurrFrame]->cx, (int)m_vecFrame[(int)m_fCurrFrame]->cy);

		m_hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		m_hOldPen = SelectObject(hBack, m_hPen);
		m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		m_hOldBrush = SelectObject(hBack, m_hBrush);
		Rectangle(hBack, m_vecFrame[(int)m_fCurrFrame]->tCollRect.left + (int)m_vecFrame[(int)m_fCurrFrame]->x,
										m_vecFrame[(int)m_fCurrFrame]->tCollRect.top + (int)m_vecFrame[(int)m_fCurrFrame]->x,
										m_vecFrame[(int)m_fCurrFrame]->tCollRect.right + (int)m_vecFrame[(int)m_fCurrFrame]->y,
										m_vecFrame[(int)m_fCurrFrame]->tCollRect.bottom + (int)m_vecFrame[(int)m_fCurrFrame]->y);
		SelectObject(hBack, m_hOldPen);
		SelectObject(hBack, m_hOldBrush);
		DeleteObject(m_hBrush);
		DeleteObject(m_hPen);
	}

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
		m_hOldPen = SelectObject(hBack, m_hPen);
		m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		m_hOldBrush = SelectObject(hBack, m_hBrush);
		Rectangle(hBack, temp.left, temp.top, temp.right, temp.bottom);
		SelectObject(hBack, m_hOldPen);
		SelectObject(hBack, m_hOldBrush);
		DeleteObject(m_hBrush);
		DeleteObject(m_hPen);
	}
	//

	BitBlt(m_PicHdc, 0, 0, WINCX, WINCY, hBack, 0, 0, SRCCOPY);
}

HRESULT CAnimation::Add_Frame(wstring strTag, wstring strFilePath)
{
	if (!m_pResourceMgr->Check_Sprite(strTag))
	{
		if (FAILED(m_pResourceMgr->Load_Sprite(strFilePath, strTag)))
			return E_FAIL;
	}

	CImage* pImage = m_pResourceMgr->Find_Sprite(strTag);

	FRAME* pFrame = new FRAME;
	pFrame->x = m_iWindowSize * 0.5f;
	pFrame->y = m_iWindowSize * 0.5f;
	pFrame->cx = (float)pImage->GetWidth();
	pFrame->cy = (float)pImage->GetHeight();
	pFrame->fSpeed = 1.f;
	pFrame->strTag = strTag;


	TCHAR szRelativePath[MAX_STR] = L"";
	TCHAR szCurrentPath[MAX_STR] = L"";
	GetCurrentDirectory(MAX_STR, szCurrentPath);
	PathRelativePathTo(szRelativePath, szCurrentPath, FILE_ATTRIBUTE_DIRECTORY, strFilePath.c_str(), FILE_ATTRIBUTE_DIRECTORY);
	pFrame->strPath = szRelativePath;


	ZeroMemory(&pFrame->tCollRect, sizeof(RECT));

	m_fCurrFrame = (float)m_vecFrame.size();
	m_vecFrame.emplace_back(pFrame);

	return NOERROR;
}

HRESULT CAnimation::Delete_Frame(int iIndex)
{
	if (iIndex >= m_vecFrame.size())
		return E_FAIL;

	auto iter = m_vecFrame.begin();
	iter += iIndex;
	SafeDelete(*iter);
	m_vecFrame.erase(iter);

	m_FrameList->DeleteString(iIndex);

	return NOERROR;
}

HRESULT CAnimation::Frame_Up(int iIndex)
{
	if (iIndex >= m_vecFrame.size())
		return E_FAIL;

	int iSelIndex = iIndex;
	int iNewIndex = iIndex - 1;
	if (iNewIndex < 0)
		iNewIndex = (int)m_vecFrame.size() - 1;

	FRAME* pSelFrame = m_vecFrame[iIndex];
	FRAME* pSwapFrame = m_vecFrame[iNewIndex];

	m_vecFrame[iNewIndex] = pSelFrame;
	m_vecFrame[iSelIndex] = pSwapFrame;

	m_FrameList->ResetContent();
	for (auto pFrame : m_vecFrame)
		m_FrameList->AddString(pFrame->strTag.c_str());

	m_FrameList->SetCurSel(iNewIndex);

	return NOERROR;
}

HRESULT CAnimation::Frame_Down(int iIndex)
{
	if (iIndex >= m_vecFrame.size())
		return E_FAIL;

	int iSelIndex = iIndex;
	int iNewIndex = iIndex + 1;
	if (iNewIndex > m_vecFrame.size() - 1)
		iNewIndex = 0;

	FRAME* pSelFrame = m_vecFrame[iIndex];
	FRAME* pSwapFrame = m_vecFrame[iNewIndex];

	m_vecFrame[iNewIndex] = pSelFrame;
	m_vecFrame[iSelIndex] = pSwapFrame;

	m_FrameList->ResetContent();
	for (auto pFrame : m_vecFrame)
		m_FrameList->AddString(pFrame->strTag.c_str());

	m_FrameList->SetCurSel(iNewIndex);

	return NOERROR;
}

HRESULT CAnimation::Clear_Frame()
{
	for (auto pFrame : m_vecFrame)
		SafeDelete(pFrame);
	m_vecFrame.clear();

	m_FrameList->ResetContent();

	return NOERROR;
}

HRESULT CAnimation::Change_Frame(int iIndex, wstring strTag, wstring strFilePath)
{
	if (iIndex >= m_vecFrame.size())
		return E_FAIL;

	if(!m_pResourceMgr->Check_Sprite(strTag))
	{
		if (FAILED(m_pResourceMgr->Load_Sprite(strFilePath, strTag)))
			return E_FAIL;
	}

	m_vecFrame[iIndex]->strTag = strTag;
	m_fCurrFrame = (float)iIndex;
	m_FrameList->SetCurSel(iIndex);

	CImage* pImage = m_pResourceMgr->Find_Sprite(strTag);
	m_vecFrame[iIndex]->cx = (float)pImage->GetWidth();
	m_vecFrame[iIndex]->cy = (float)pImage->GetHeight();

	return NOERROR;
}

HRESULT CAnimation::Save_Animation(wstring strPath)
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

	for (auto pFrame : m_vecFrame)
		fout << pFrame->strTag << " " << pFrame->fSpeed << " " << pFrame->x << " " << pFrame->y << " " << pFrame->cx << " " << pFrame->cy << " "
		<< pFrame->tCollRect.left << " " << pFrame->tCollRect.top << " " << pFrame->tCollRect.right << " " << pFrame->tCollRect.bottom << " "
		<< pFrame->strPath << endl;

	fout.close();

	return NOERROR;
}

HRESULT CAnimation::Load_Animation(wstring strPath)
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

	Clear_Frame();

	while (true)
	{
		FRAME* pFrame = new FRAME;

		fin >> pFrame->strTag >> pFrame->fSpeed >> pFrame->x >> pFrame->y >> pFrame->cx >> pFrame->cy >>
			pFrame->tCollRect.left >> pFrame->tCollRect.top >> pFrame->tCollRect.right >> pFrame->tCollRect.bottom >> pFrame->strPath;

		if (fin.eof())
		{
			SafeDelete(pFrame);
			break;
		}

		if (!m_pResourceMgr->Check_Sprite(pFrame->strTag))
		{
			if (FAILED(m_pResourceMgr->Load_Sprite(pFrame->strTag, pFrame->strPath)))
				return E_FAIL;
		}

		m_vecFrame.emplace_back(pFrame);
	}

	fin.close();

	for (auto pFrame : m_vecFrame)
		m_FrameList->AddString(pFrame->strTag.c_str());

	return NOERROR;
}

CAnimation* CAnimation::Create()
{
	CAnimation* pInstance = new CAnimation;

	if (FAILED(pInstance->Ready_GameObj()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CAnimation::Free()
{
	for (auto pFrame : m_vecFrame)
		SafeDelete(pFrame);
	m_vecFrame.clear();
}
