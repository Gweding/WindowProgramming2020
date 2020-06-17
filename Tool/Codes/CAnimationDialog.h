#pragma once
// CAnimationDialog 대화 상자

class CAnimation;
class CAnimationDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CAnimationDialog)

public:
	CAnimationDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAnimationDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AnimationDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnBnClicked_AddFrame();
	afx_msg void OnBnClicked_DeleteFrame();

public:
	afx_msg void OnBnClicked_FrameUp();
	afx_msg void OnBnClicked_FrameDown();

public:
	afx_msg void OnBnClicked_PlayAnimation();
	afx_msg void OnBnClicked_StopAnimation();

public:
	afx_msg void OnLbnSelchange_FrameList();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClicked_ResetAnimation();
	afx_msg void OnBnClicked_ChangeFrame();
	afx_msg void OnBnClicked_Adjust();
	afx_msg void OnBnClicked_AdjustAll();
	afx_msg void OnBnClicked_Magnify();
	afx_msg void OnBnClicked_Minimize();
	afx_msg void OnBnClicked_Save();
	afx_msg void OnBnClicked_Load();

public:
	void SetHorizontalScroll();
	void DirInfoExtraction(wstring strFullPath);

public:
	CAnimation* m_pCurrAnimation;

public:
	CStatic m_PicCtrl;
	CListBox m_FrameList;

public:
	float m_fFrameSpeed;
	CString m_strAnimationTag;
};
