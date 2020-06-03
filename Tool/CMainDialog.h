#pragma once


// CMainDialog 대화 상자

#include "CSoundList.h"
#include "CAnimationDialog.h"
#include "CMapRenderDialog.h"
#include "CPathExtractDialog.h"

class CMainDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDialog)

public:
	CMainDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMainDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MainDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnBnClicked_OpenPathExtract();
	afx_msg void OnBnClicked_OpenAnimation();
	afx_msg void OnBnClicked_OpenMapRender();

public:
	afx_msg void OnBnClicked_RenderGrid();
	afx_msg void OnBnClicked_RenderAni();
	afx_msg void OnBnClicked_RenderBack();
	afx_msg void OnBnClicked_RenderColl();

public:
	afx_msg void OnBnClicked_LoadSoundDirectory();

public:
	afx_msg void OnBnClicked_AddSound();
	afx_msg void OnBnClicked_PlaySound();
	afx_msg void OnBnClicked_StopSound();

public:
	void Set_SoundName(CString strName);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClicked_NewProject();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

public:
	CAnimationDialog m_Animation;
	CMapRenderDialog m_MapRender;
	CPathExtractDialog m_PathExtract;

public:
	CButton	m_Render[RENDER_END];

public:
	CSoundList m_SoundList;
	CSliderCtrl m_SoundSlider;
	CString m_strSoundName;
	CString m_strCurrSound;
	CString m_strPosition;
	CString m_strMilliSeconds;
	CString m_strSeconds;
	CString m_strMinutes;
};
