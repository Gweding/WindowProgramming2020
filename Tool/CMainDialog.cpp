// CMainDialog.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "CMainDialog.h"
#include "afxdialogex.h"

#include "Tool.h"
#include "CProject.h"
#include "CGrid.h"

// CMainDialog 대화 상자

IMPLEMENT_DYNAMIC(CMainDialog, CDialogEx)

CMainDialog::CMainDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MainDialog, pParent)
	, m_strSoundName(_T("마침 여기가 밋밋했는데 fmod 확인할겸 넣어본 간지 기능"))
	, m_strPosition(_T(""))
{

}

CMainDialog::~CMainDialog()
{
	KillTimer(0);
}

void CMainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_Render[0]);
	DDX_Control(pDX, IDC_CHECK2, m_Render[1]);
	DDX_Control(pDX, IDC_CHECK3, m_Render[2]);
	DDX_Control(pDX, IDC_CHECK4, m_Render[3]);
	DDX_Text(pDX, IDC_SOUNDPLAYER, m_strSoundName);
	DDX_Text(pDX, IDC_EDIT3, m_strPosition);
	DDX_Control(pDX, IDC_SLIDER2, m_SoundSlider);
}


BEGIN_MESSAGE_MAP(CMainDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON4, &CMainDialog::OnBnClicked_OpenPathExtract)
	ON_BN_CLICKED(IDC_BUTTON5, &CMainDialog::OnBnClicked_OpenAnimation)
	ON_BN_CLICKED(IDC_BUTTON7, &CMainDialog::OnBnClicked_OpenMapRender)
	ON_BN_CLICKED(IDC_CHECK1, &CMainDialog::OnBnClicked_RenderGrid)
	ON_BN_CLICKED(IDC_CHECK2, &CMainDialog::OnBnClicked_RenderAni)
	ON_BN_CLICKED(IDC_CHECK3, &CMainDialog::OnBnClicked_RenderBack)
	ON_BN_CLICKED(IDC_CHECK4, &CMainDialog::OnBnClicked_RenderColl)
	ON_BN_CLICKED(IDC_BUTTON14, &CMainDialog::OnBnClicked_AddSound)
	ON_BN_CLICKED(IDC_BUTTON15, &CMainDialog::OnBnClicked_PlaySound)
	ON_BN_CLICKED(IDC_BUTTON13, &CMainDialog::OnBnClicked_LoadSoundDirectory)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON16, &CMainDialog::OnBnClicked_StopSound)
	ON_BN_CLICKED(IDC_BUTTON3, &CMainDialog::OnBnClicked_NewProject)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


BOOL CMainDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	if (nullptr == m_Animation.GetSafeHwnd())
		m_Animation.Create(IDD_AnimationDialog);
	if (nullptr == m_MapRender.GetSafeHwnd())
		m_MapRender.Create(IDD_MapRenderDialog);
	if (nullptr == m_PathExtract.GetSafeHwnd())
		m_PathExtract.Create(IDD_PathExtractDialog);
	if (nullptr == m_SoundList.GetSafeHwnd())
		m_SoundList.Create(IDD_SoundList);

	for (int i = 0; i < RENDER_END; ++i)
	{
		m_Render[i].SetCheck(TRUE);
	}

	SetTimer(0, 10, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


// CMainDialog 메시지 처리기


void CMainDialog::OnBnClicked_OpenPathExtract()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_PathExtract.ShowWindow(SW_SHOW);
}


void CMainDialog::OnBnClicked_OpenAnimation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_PathExtract.ShowWindow(SW_SHOW);
}


void CMainDialog::OnBnClicked_OpenMapRender()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Animation.ShowWindow(SW_SHOW);
}


void CMainDialog::OnBnClicked_RenderGrid()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL bCheck = m_Render[RENDER_GRID].GetCheck();
	CToolApp* pApp = (CToolApp*)AfxGetApp();

	pApp->m_pProject->m_pScene->m_pGrid->m_bRender = bCheck;
}


void CMainDialog::OnBnClicked_RenderAni()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}


void CMainDialog::OnBnClicked_RenderBack()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}


void CMainDialog::OnBnClicked_RenderColl()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}

static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if (uMsg == BFFM_INITIALIZED)
		SendMessage(hwnd, BFFM_SETSELECTION, (WPARAM)TRUE, (LPARAM)lpData);
	return 0;
}

void CMainDialog::OnBnClicked_LoadSoundDirectory()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LPITEMIDLIST  pidlBrowse;
	WCHAR         szFolder[MAX_PATH];

	TCHAR szCurPath[256] = L"";
	GetCurrentDirectory(256, szCurPath);
	PathRemoveFileSpec(szCurPath);
	lstrcat(szCurPath, L"\\Binary\\Resources");
	CString strPath = szCurPath;
	BROWSEINFO brInfo;

	::ZeroMemory(&brInfo, sizeof(BROWSEINFO));
	brInfo.hwndOwner = m_hWnd;
	brInfo.pidlRoot = NULL;
	brInfo.pszDisplayName = szFolder;
	brInfo.lpszTitle = L"폴더 선택";
	brInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT | BIF_VALIDATE;
	brInfo.lpfn = BrowseCallbackProc;
	brInfo.lParam = (LPARAM)strPath.GetBuffer(strPath.GetLength());

	::ZeroMemory(szFolder, MAX_PATH);

	pidlBrowse = ::SHBrowseForFolder(&brInfo);
	strPath.ReleaseBuffer();

	if (pidlBrowse != NULL)
		::SHGetPathFromIDList(pidlBrowse, szFolder);
	else
		return;

	StrCat(szFolder, L"\\");
	int len = 256;
	char ctemp[256];
	WideCharToMultiByte(CP_ACP, 0, szFolder, len, ctemp, len, NULL, NULL);
	printf("%s", ctemp);

	CSoundManager::GetInstance()->Load_SoundFile(ctemp);
	CSoundManager::GetInstance()->SetUp_ListBox(&m_SoundList.m_SoundList);
}


void CMainDialog::OnBnClicked_AddSound()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_SoundList.ShowWindow(SW_SHOW);
}


void CMainDialog::OnBnClicked_PlaySound()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CSoundManager::GetInstance()->Stop_All();
	CSoundManager::GetInstance()->Play_BGM(m_strCurrSound.GetString());
	UINT iLength = CSoundManager::GetInstance()->Get_Length(m_strCurrSound.GetString());
	m_SoundSlider.SetRange(0, iLength / 1000);
}


void CMainDialog::OnBnClicked_StopSound()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CSoundManager::GetInstance()->Stop_All();
	//m_SoundSlider.SetPos(0);
}


void CMainDialog::Set_SoundName(CString strName)
{
	UpdateData(TRUE);
	m_strSoundName = L" ♩♪♬ ) " + strName;
	m_strCurrSound = strName;
	UpdateData(FALSE);
}


void CMainDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_strCurrSound == L"")
	{
		UpdateData(TRUE);
		m_strPosition = L"- : - : -";
		UpdateData(FALSE);
		return;
	}

	UpdateData(TRUE);

	int position = (int)CSoundManager::GetInstance()->Get_Position();
	int mill = position % 1000;
	int sec = position / 1000;
	m_SoundSlider.SetPos(sec);
	int min = sec / 60;
	sec -= min * 60;

	m_strMilliSeconds.Format(L"%d", mill);
	m_strSeconds.Format(L"%d", sec);
	m_strMinutes.Format(L"%d", min);

	m_strPosition = m_strMinutes + L" : " + m_strSeconds + L" : " + m_strMilliSeconds;

	UpdateData(FALSE);

	CDialogEx::OnTimer(nIDEvent);
}


void CMainDialog::OnBnClicked_NewProject()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (IDYES == AfxMessageBox(L"프로젝트를 모두 초기화하고 다시 시작합니다.", MB_YESNO))
	{
		CToolApp* pApp = (CToolApp*)AfxGetApp();
		SafeDelete(pApp->m_pProject);
		pApp->m_pProject = CProject::Create();
		m_SoundList.m_SoundList.ResetContent();
	}
	else
		if (IDNO)
			return;
}


void CMainDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (IDC_SLIDER2 == pScrollBar->GetDlgCtrlID())
	{
		int iPos = m_SoundSlider.GetPos();
		CSoundManager::GetInstance()->Set_Position(iPos * 1000);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
