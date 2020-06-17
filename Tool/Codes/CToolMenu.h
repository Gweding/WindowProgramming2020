#pragma once
#include "CMainDialog.h"
#include "CSceneDialog.h"
#include "CObjectDialog.h"

// CToolMenu 폼 보기

class CToolMenu : public CFormView
{
	DECLARE_DYNCREATE(CToolMenu)

protected:
	CToolMenu();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CToolMenu();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ToolMenu };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();

public:
	afx_msg void OnTcnSelchangeTabCtrl(NMHDR* pNMHDR, LRESULT* pResult);

public:
	CTabCtrl m_TabCtrl;

public:
	CWnd* m_pWnd;
	CMainDialog* m_pMain;
	CSceneDialog* m_pScene;
	CObjectDialog* m_pObject;
};
