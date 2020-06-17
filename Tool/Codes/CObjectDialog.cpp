// CObjectDialog.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "CObjectDialog.h"
#include "afxdialogex.h"


// CObjectDialog 대화 상자

IMPLEMENT_DYNAMIC(CObjectDialog, CDialogEx)

CObjectDialog::CObjectDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ObjectDialog, pParent)
{

}

CObjectDialog::~CObjectDialog()
{
}

void CObjectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CObjectDialog, CDialogEx)
END_MESSAGE_MAP()


// CObjectDialog 메시지 처리기
