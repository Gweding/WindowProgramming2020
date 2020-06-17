// CMapRenderDialog.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "CMapRenderDialog.h"
#include "afxdialogex.h"


// CMapRenderDialog 대화 상자

IMPLEMENT_DYNAMIC(CMapRenderDialog, CDialogEx)

CMapRenderDialog::CMapRenderDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MapRenderDialog, pParent)
{

}

CMapRenderDialog::~CMapRenderDialog()
{
}

void CMapRenderDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMapRenderDialog, CDialogEx)
END_MESSAGE_MAP()


// CMapRenderDialog 메시지 처리기
