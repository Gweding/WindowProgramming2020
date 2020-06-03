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
}


BEGIN_MESSAGE_MAP(CPathExtractDialog, CDialogEx)
END_MESSAGE_MAP()


// CPathExtractDialog 메시지 처리기
