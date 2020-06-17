#pragma once


// CSoundList 대화 상자

class CSoundList : public CDialogEx
{
	DECLARE_DYNAMIC(CSoundList)

public:
	CSoundList(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSoundList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SoundList };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClicked_RefreshSoundLIst();
	afx_msg void OnBnClicked_SelectMusic();

public:
	CListBox m_SoundList;
	bool m_bMainSound = true;
};
