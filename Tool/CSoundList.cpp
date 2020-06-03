// CSoundList.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "CSoundList.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "CToolMenu.h"

// CSoundList 대화 상자

IMPLEMENT_DYNAMIC(CSoundList, CDialogEx)

CSoundList::CSoundList(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SoundList, pParent)
{

}

CSoundList::~CSoundList()
{
}

void CSoundList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_SoundList);
}


BEGIN_MESSAGE_MAP(CSoundList, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CSoundList::OnBnClicked_RefreshSoundLIst)
	ON_BN_CLICKED(IDC_BUTTON1, &CSoundList::OnBnClicked_SelectMusic)
END_MESSAGE_MAP()


// CSoundList 메시지 처리기


void CSoundList::OnBnClicked_RefreshSoundLIst()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_SoundList.ResetContent();
	CSoundManager::GetInstance()->SetUp_ListBox(&m_SoundList);
	UpdateData(FALSE);
}


void CSoundList::OnBnClicked_SelectMusic()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_SoundList.GetCount() == 0)
	{
		MessageBox(L"로드된 사운드가 없습니다.", L"ERROR", MB_OK);
		return;
	}

	if (m_bMainSound)
	{
		CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		CToolMenu* pToolMenu = dynamic_cast<CToolMenu*>(pFrameWnd->m_WndSplit.GetPane(0, 0));

		CString Temp = L"";
		m_SoundList.GetText(m_SoundList.GetCurSel(), Temp);
		pToolMenu->m_pMain->Set_SoundName(Temp);
	}
	else
	{
		CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		CToolMenu* pToolMenu = dynamic_cast<CToolMenu*>(pFrameWnd->m_WndSplit.GetPane(0, 0));
		MessageBox(L"테스트인데용", L"테수뚜", MB_OK);
		return;
	}

	ShowWindow(SW_HIDE);
	UpdateWindow();
}
