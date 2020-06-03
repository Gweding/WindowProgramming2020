#pragma once


// CSceneInfoDialog 대화 상자

class CSceneInfoDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSceneInfoDialog)

public:
	CSceneInfoDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSceneInfoDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SceneInfoDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
