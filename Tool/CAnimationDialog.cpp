// CAnimationDialog.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "CAnimationDialog.h"
#include "afxdialogex.h"


// CAnimationDialog 대화 상자

IMPLEMENT_DYNAMIC(CAnimationDialog, CDialogEx)

CAnimationDialog::CAnimationDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AnimationDialog, pParent)
{

}

CAnimationDialog::~CAnimationDialog()
{
}

void CAnimationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAnimationDialog, CDialogEx)
END_MESSAGE_MAP()


// CAnimationDialog 메시지 처리기
