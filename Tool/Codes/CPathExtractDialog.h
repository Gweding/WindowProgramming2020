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

public:
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnDropFiles(HDROP hDropInfo);

public:
	void SetHorizontalScroll();
	void DirInfoExtraction(wstring strFullPath);

public:
	CListBox m_PathList;

public:
	list<IMAGE> m_ImageInfoList;
	afx_msg void OnBnClicked_ExtractPath();
};
