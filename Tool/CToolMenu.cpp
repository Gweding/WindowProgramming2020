// CToolMenu.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "CToolMenu.h"

// CToolMenu

IMPLEMENT_DYNCREATE(CToolMenu, CFormView)

CToolMenu::CToolMenu()
	: CFormView(IDD_ToolMenu)
{

}

CToolMenu::~CToolMenu()
{
}

void CToolMenu::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
}

BEGIN_MESSAGE_MAP(CToolMenu, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CToolMenu::OnTcnSelchangeTabCtrl)
END_MESSAGE_MAP()


// CToolMenu 진단

#ifdef _DEBUG
void CToolMenu::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CToolMenu::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CToolMenu 메시지 처리기


void CToolMenu::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CSize scrollSize(0, 0);
	SetScrollSizes(MM_TEXT, scrollSize);

	m_TabCtrl.InsertItem(0, L"MAIN");
	m_TabCtrl.InsertItem(1, L"SCENE");
	m_TabCtrl.InsertItem(2, L"OBJECT");

	m_TabCtrl.SetCurSel(0);

	CRect rect;
	m_TabCtrl.GetWindowRect(&rect);

	m_pMain = new CMainDialog;
	m_pMain->Create(IDD_MainDialog, &m_TabCtrl);
	m_pMain->MoveWindow(0, 25, rect.Width(), rect.Height());

	m_pScene = new CSceneDialog;
	m_pScene->Create(IDD_SceneDialog, &m_TabCtrl);
	m_pScene->MoveWindow(0, 25, rect.Width(), rect.Height());

	m_pObject = new CObjectDialog;
	m_pObject->Create(IDD_ObjectDialog, &m_TabCtrl);
	m_pObject->MoveWindow(0, 25, rect.Width(), rect.Height());

	m_pMain->ShowWindow(SW_SHOW);
	m_pWnd = m_pMain;
}


void CToolMenu::OnTcnSelchangeTabCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_pWnd != nullptr)
	{
		m_pWnd->ShowWindow(SW_HIDE);
		m_pWnd = nullptr;
	}

	int iSel = m_TabCtrl.GetCurSel();

	switch (iSel)
	{
	case 0:
		m_pMain->ShowWindow(SW_SHOW);
		m_pWnd = m_pMain;
		break;
	case 1:
		m_pScene->ShowWindow(SW_SHOW);
		m_pWnd = m_pScene;
		break;
	case 2:
		m_pObject->ShowWindow(SW_SHOW);
		m_pWnd = m_pObject;
		break;
	}

	*pResult = 0;
}
