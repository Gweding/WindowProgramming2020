// CPathExtractDialog.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "CPathExtractDialog.h"
#include "afxdialogex.h"


// CPathExtractDialog 대화 상자

IMPLEMENT_DYNAMIC(CPathExtractDialog, CDialogEx)

CPathExtractDialog::CPathExtractDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PathExtractDialog, pParent)
{

}

CPathExtractDialog::~CPathExtractDialog()
{
}

void CPathExtractDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_PathList);
}


BEGIN_MESSAGE_MAP(CPathExtractDialog, CDialogEx)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CPathExtractDialog::OnBnClicked_ExtractPath)
END_MESSAGE_MAP()


// CPathExtractDialog 메시지 처리기


BOOL CPathExtractDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CPathExtractDialog::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CDialog::OnDropFiles(hDropInfo);

	int iCount = DragQueryFile(hDropInfo, -1, nullptr, 0);

	TCHAR szFullPath[256] = L"";

	m_PathList.ResetContent();

	for (int i = 0; i < iCount; ++i)
	{
		DragQueryFile(hDropInfo, i, szFullPath, 256);

		DirInfoExtraction(szFullPath);
	}

	m_PathList.ResetContent();

	wstring strCombined = L"";

	for (auto tTile : m_ImageInfoList)
	{
		wstring strCombined = tTile.strImageTag + L" || " + tTile.strRelativePath;
		m_PathList.AddString(strCombined.c_str());
	}

	SetHorizontalScroll();
}

void CPathExtractDialog::SetHorizontalScroll()
{
	int iCX = 0;
	CSize size;
	CString strName = L"";

	CDC* pDC = m_PathList.GetDC();

	for (int i = 0; i < m_PathList.GetCount(); ++i)
	{
		m_PathList.GetText(i, strName);
		size = pDC->GetTextExtent(strName);

		if (iCX < size.cx)
			iCX = size.cx;
	}

	m_PathList.ReleaseDC(pDC);

	if (iCX > m_PathList.GetHorizontalExtent())
	{
		m_PathList.SetHorizontalExtent(iCX);
	}
}

void CPathExtractDialog::DirInfoExtraction(wstring strFullPath)
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

			TCHAR szRelativePath[MAX_STR] = L"";
			TCHAR szCurrentPath[MAX_STR] = L"";
			GetCurrentDirectory(MAX_STR, szCurrentPath);
			PathRelativePathTo(szRelativePath, szCurrentPath, FILE_ATTRIBUTE_DIRECTORY,
				strFullPath.c_str(), FILE_ATTRIBUTE_DIRECTORY);

			IMAGE tTemp;
			tTemp.strImageTag = strTag;
			tTemp.strRelativePath = wstring(szRelativePath) + find.GetFileName().GetString();
			m_ImageInfoList.emplace_back(tTemp);
		}
	}
}



void CPathExtractDialog::OnBnClicked_ExtractPath()
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
	lstrcat(szCurPath, L"\\Binary\\Data\\Path");

	Dlg.m_ofn.lpstrInitialDir = szCurPath;

	if (Dlg.DoModal() == IDOK)
	{
		wstring path = Dlg.GetPathName();

		std::locale::global(std::locale("Korean"));
#ifdef _UNICODE
		wofstream fout;
#else
		ofstream fout;
#endif // _UNICODE

		fout.open(path);

		if (fout.fail())
			return;

		for (auto tInfo : m_ImageInfoList)
			fout << tInfo.strImageTag << "|" << tInfo.strRelativePath << endl;

		fout.close();
	}
}
