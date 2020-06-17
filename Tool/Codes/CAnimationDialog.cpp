// CAnimationDialog.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "CAnimationDialog.h"
#include "afxdialogex.h"

#include "CAnimation.h"

// CAnimationDialog 대화 상자

IMPLEMENT_DYNAMIC(CAnimationDialog, CDialogEx)

CAnimationDialog::CAnimationDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AnimationDialog, pParent)
	, m_strAnimationTag(_T(""))
	, m_fFrameSpeed(0)
{

}

CAnimationDialog::~CAnimationDialog()
{
	SafeDelete(m_pCurrAnimation);
}

void CAnimationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC, m_PicCtrl);
	DDX_Control(pDX, IDC_LIST1, m_FrameList);
	DDX_Text(pDX, IDC_EDIT2, m_strAnimationTag);
	DDX_Text(pDX, IDC_EDIT4, m_fFrameSpeed);
}


BEGIN_MESSAGE_MAP(CAnimationDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CAnimationDialog::OnBnClicked_AddFrame)
	ON_BN_CLICKED(IDC_BUTTON4, &CAnimationDialog::OnBnClicked_DeleteFrame)
	ON_BN_CLICKED(IDC_BUTTON6, &CAnimationDialog::OnBnClicked_FrameUp)
	ON_BN_CLICKED(IDC_BUTTON5, &CAnimationDialog::OnBnClicked_FrameDown)
	ON_BN_CLICKED(IDC_BUTTON1, &CAnimationDialog::OnBnClicked_PlayAnimation)
	ON_BN_CLICKED(IDC_BUTTON2, &CAnimationDialog::OnBnClicked_StopAnimation)
	ON_LBN_SELCHANGE(IDC_LIST1, &CAnimationDialog::OnLbnSelchange_FrameList)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON18, &CAnimationDialog::OnBnClicked_ResetAnimation)
	ON_BN_CLICKED(IDC_BUTTON19, &CAnimationDialog::OnBnClicked_ChangeFrame)
	ON_BN_CLICKED(IDC_BUTTON17, &CAnimationDialog::OnBnClicked_Adjust)
	ON_BN_CLICKED(IDC_BUTTON20, &CAnimationDialog::OnBnClicked_AdjustAll)
	ON_BN_CLICKED(IDC_BUTTON21, &CAnimationDialog::OnBnClicked_Magnify)
	ON_BN_CLICKED(IDC_BUTTON22, &CAnimationDialog::OnBnClicked_Minimize)
	ON_BN_CLICKED(IDC_BUTTON7, &CAnimationDialog::OnBnClicked_Save)
	ON_BN_CLICKED(IDC_BUTTON8, &CAnimationDialog::OnBnClicked_Load)
END_MESSAGE_MAP()


// CAnimationDialog 메시지 처리기


BOOL CAnimationDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CAnimationDialog::OnBnClicked_AddFrame()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CFileDialog Dlg(
		TRUE,
		L"png",
		L"Image.png",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"PNG(*.png)|*.png|BMP(*.bmp)|*.bmp||",
		this);

	TCHAR szCurPath[MAX_STR] = L"";
	GetCurrentDirectory(MAX_STR, szCurPath);
	PathRemoveFileSpec(szCurPath);
	PathRemoveFileSpec(szCurPath);
	lstrcat(szCurPath, L"\\Binary\\Resources\\Sprite\\");
	Dlg.m_ofn.lpstrInitialDir = szCurPath;

	if (IDOK == Dlg.DoModal())
	{
		TCHAR szTmp[4096];
		CString strFileName = PathFindFileName(Dlg.GetFileName());
		CString strExtension = PathFindExtension(Dlg.GetFileName());
		ZeroMemory(szTmp, 4096);
		StrCpy(szTmp, strFileName);
		PathRemoveExtension(szTmp);

		if (FAILED(m_pCurrAnimation->Add_Frame(wstring(szTmp), Dlg.GetPathName().GetString())))
			return;

		m_FrameList.AddString(szTmp);
	}
}


void CAnimationDialog::OnBnClicked_DeleteFrame()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iSel = m_FrameList.GetCurSel();
	if (iSel == -1)
		return;
	m_pCurrAnimation->Delete_Frame(iSel);
}


void CAnimationDialog::OnBnClicked_FrameUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iSel = m_FrameList.GetCurSel();
	if (iSel == -1)
		return;

	m_pCurrAnimation->Frame_Up(iSel);
}


void CAnimationDialog::OnBnClicked_FrameDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iSel = m_FrameList.GetCurSel();
	if (iSel == -1)
		return;

	m_pCurrAnimation->Frame_Down(iSel);
}


void CAnimationDialog::OnBnClicked_PlayAnimation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pCurrAnimation->m_bPlay = true;
}


void CAnimationDialog::OnBnClicked_StopAnimation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pCurrAnimation->m_bPlay = false;
}


void CAnimationDialog::OnLbnSelchange_FrameList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int iSel = m_FrameList.GetCurSel();
	if (iSel == -1)
		return;
	m_pCurrAnimation->m_fCurrFrame = (float)iSel;

	UpdateData(TRUE);
	m_strAnimationTag = m_pCurrAnimation->m_vecFrame[iSel]->strTag.c_str();
	m_fFrameSpeed = m_pCurrAnimation->m_vecFrame[iSel]->fSpeed;
	UpdateData(FALSE);
}


void CAnimationDialog::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnDropFiles(hDropInfo);

	int iCount = DragQueryFile(hDropInfo, -1, nullptr, 0);

	TCHAR szFullPath[256] = L"";

	m_FrameList.ResetContent();
	m_pCurrAnimation->Clear_Frame();

	for (int i = 0; i < iCount; ++i)
	{
		DragQueryFile(hDropInfo, i, szFullPath, 256);

		DirInfoExtraction(szFullPath);
	}

	for (auto pFrame : m_pCurrAnimation->m_vecFrame)
		m_FrameList.AddString(pFrame->strTag.c_str());

	SetHorizontalScroll();
}


void CAnimationDialog::SetHorizontalScroll()
{
	int iCX = 0;
	CSize size;
	CString strName = L"";

	CDC* pDC = m_FrameList.GetDC();

	for (int i = 0; i < m_FrameList.GetCount(); ++i)
	{
		m_FrameList.GetText(i, strName);
		size = pDC->GetTextExtent(strName);

		if (iCX < size.cx)
			iCX = size.cx;
	}

	m_FrameList.ReleaseDC(pDC);

	if (iCX > m_FrameList.GetHorizontalExtent())
	{
		m_FrameList.SetHorizontalExtent(iCX);
	}
}

void CAnimationDialog::DirInfoExtraction(wstring strFullPath)
{
	// 파일 및 경로 탐색에 관한 MFC 클래스.
	CFileFind	find;

	wstring wstrFindPath = strFullPath + L"\\*.*";

	BOOL bContinue = find.FindFile(wstrFindPath.c_str());

	while (bContinue)
	{
		bContinue = find.FindNextFile();

		if (find.IsDots())
			continue;
		else if (find.IsDirectory())
			DirInfoExtraction(wstring(find.GetFilePath()));
		else
		{
			if (find.IsSystem())
				continue;

			TCHAR		szPath[MAX_STR] = L"";

			lstrcpy(szPath, find.GetFilePath().GetString());
			PathRemoveFileSpec(szPath);

			wstring strTag = find.GetFileTitle();
			
			m_pCurrAnimation->Add_Frame(strTag, find.GetFilePath().GetString());
		}
	}
}


void CAnimationDialog::OnBnClicked_ResetAnimation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (IDYES == AfxMessageBox(L"애니메이션을 모두 초기화하고 다시 시작합니다.", MB_YESNO))
	{
		m_pCurrAnimation->Clear_Frame();
		m_FrameList.ResetContent();
		UpdateData(TRUE);
		m_strAnimationTag = L"";
		m_fFrameSpeed = 0.f;
		UpdateData(FALSE);
	}
	else
		if (IDNO)
			return;
}


void CAnimationDialog::OnBnClicked_ChangeFrame()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int iSel = m_FrameList.GetCurSel();
	if (iSel == -1)
	{
		MessageBox(L"프레임 선택해라", L"ERROR", MB_OK);
		return;
	}

	CFileDialog Dlg(
		TRUE,
		L"png",
		L"Image.png",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"PNG(*.png)|*.png|BMP(*.bmp)|*.bmp||",
		this);

	TCHAR szCurPath[MAX_STR] = L"";
	GetCurrentDirectory(MAX_STR, szCurPath);
	PathRemoveFileSpec(szCurPath);
	PathRemoveFileSpec(szCurPath);
	lstrcat(szCurPath, L"\\Binary\\Resources\\Sprite\\");
	Dlg.m_ofn.lpstrInitialDir = szCurPath;

	if (IDOK == Dlg.DoModal())
	{
		TCHAR szTmp[4096];
		CString strFileName = PathFindFileName(Dlg.GetFileName());
		CString strExtension = PathFindExtension(Dlg.GetFileName());
		ZeroMemory(szTmp, 4096);
		StrCpy(szTmp, strFileName);
		PathRemoveExtension(szTmp);

		if (FAILED(m_pCurrAnimation->Change_Frame(iSel, wstring(szTmp), Dlg.GetPathName().GetString())))
			return;
	}
}


void CAnimationDialog::OnBnClicked_Adjust()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int iSel = m_FrameList.GetCurSel();
	if (iSel == -1)
	{
		MessageBox(L"프레임 선택해라", L"ERROR", MB_OK);
		return;
	}

	UpdateData(TRUE);
	m_pCurrAnimation->m_vecFrame[iSel]->fSpeed = m_fFrameSpeed;
	UpdateData(FALSE);
}


void CAnimationDialog::OnBnClicked_AdjustAll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	for(auto pFrame : m_pCurrAnimation->m_vecFrame)
		pFrame->fSpeed = m_fFrameSpeed;
	UpdateData(FALSE);
}


void CAnimationDialog::OnBnClicked_Magnify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	for (auto pFrame : m_pCurrAnimation->m_vecFrame)
	{
		pFrame->cx *= 2.f;
		pFrame->cy *= 2.f;

		pFrame->tCollRect.left *= 2;
		pFrame->tCollRect.right *= 2;
		pFrame->tCollRect.top *= 2;
		pFrame->tCollRect.bottom *= 2;
	}
}


void CAnimationDialog::OnBnClicked_Minimize()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	for (auto pFrame : m_pCurrAnimation->m_vecFrame)
	{
		pFrame->cx *= 0.5f;
		pFrame->cy *= 0.5f;

		pFrame->tCollRect.left /= 2;
		pFrame->tCollRect.right /= 2;
		pFrame->tCollRect.top /= 2;
		pFrame->tCollRect.bottom /= 2;
	}
}


void CAnimationDialog::OnBnClicked_Save()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CFileDialog Dlg(
		FALSE,
		L"dat",
		L"",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat|Text Files(*.txt)|*.txt||",
		this);

	TCHAR szCurPath[256] = L"";
	GetCurrentDirectory(256, szCurPath);
	PathRemoveFileSpec(szCurPath);
	PathRemoveFileSpec(szCurPath);
	lstrcat(szCurPath, L"\\Binary\\Data\\Animation");

	Dlg.m_ofn.lpstrInitialDir = szCurPath;

	if (Dlg.DoModal() == IDOK)
	{
		wstring path = Dlg.GetPathName();

		m_pCurrAnimation->Save_Animation(path);
	}
}


void CAnimationDialog::OnBnClicked_Load()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CFileDialog Dlg(
		TRUE,
		L"dat",
		L"",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat|Text Files(*.txt)|*.txt||",
		this);

	TCHAR szCurPath[256] = L"";
	GetCurrentDirectory(256, szCurPath);
	PathRemoveFileSpec(szCurPath);
	PathRemoveFileSpec(szCurPath);
	lstrcat(szCurPath, L"\\Binary\\Data\\Animation");

	Dlg.m_ofn.lpstrInitialDir = szCurPath;

	if (Dlg.DoModal() == IDOK)
	{
		wstring path = Dlg.GetPathName();

		m_pCurrAnimation->Load_Animation(path);
	}
}
