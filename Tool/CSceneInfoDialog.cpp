// CSceneInfoDialog.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "CSceneInfoDialog.h"
#include "afxdialogex.h"


// CSceneInfoDialog 대화 상자

IMPLEMENT_DYNAMIC(CSceneInfoDialog, CDialogEx)

CSceneInfoDialog::CSceneInfoDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SceneInfoDialog, pParent)
{

}

CSceneInfoDialog::~CSceneInfoDialog()
{
}

void CSceneInfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSceneInfoDialog, CDialogEx)
END_MESSAGE_MAP()


// CSceneInfoDialog 메시지 처리기
