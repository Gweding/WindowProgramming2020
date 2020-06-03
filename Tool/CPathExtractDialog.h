#pragma once


// CPathExtractDialog 대화 상자

class CPathExtractDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPathExtractDialog)

public:
	CPathExtractDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CPathExtractDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PathExtractDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
