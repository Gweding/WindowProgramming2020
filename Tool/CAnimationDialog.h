#pragma once


// CAnimationDialog 대화 상자

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
};
