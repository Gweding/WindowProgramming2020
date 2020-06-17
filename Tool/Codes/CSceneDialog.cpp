// CSceneDialog.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "CSceneDialog.h"
#include "afxdialogex.h"


// CSceneDialog 대화 상자

#include "CScene.h"
#include "CProject.h"
#include "CMapLayer.h"
#include "CPallete.h"

IMPLEMENT_DYNAMIC(CSceneDialog, CDialogEx)

CSceneDialog::CSceneDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SceneDialog, pParent)
	, m_strBackImage(_T(""))
	, m_iGridX(100)
	, m_iGridY(100)
	, m_fBackSpeed(1.f)
	, m_strLayerTag(_T("Layer"))
	, m_fSizeX(1.f)
	, m_fSizeY(1.f)
{
	g_iGridX = m_iGridX;
	g_iGridY = m_iGridY;
}

CSceneDialog::~CSceneDialog()
{
}

void CSceneDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_LayerListbox);
	DDX_Control(pDX, IDC_TILEPALLETE, m_TilePicCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_strBackImage);
	DDX_Control(pDX, IDC_LIST3, m_CollListbox);
	DDX_Text(pDX, IDC_EDIT5, m_iGridX);
	DDX_Text(pDX, IDC_EDIT6, m_iGridY);
	DDX_Text(pDX, IDC_EDIT7, m_fBackSpeed);
	DDX_Text(pDX, IDC_EDIT3, m_strLayerTag);
	DDX_Text(pDX, IDC_EDIT8, m_fSizeX);
	DDX_Text(pDX, IDC_EDIT9, m_fSizeY);
	DDX_Control(pDX, IDC_COMBO2, m_LayerTypeCombo);
	DDX_Control(pDX, IDC_COMBO1, m_CollTypeCombo);
}


BEGIN_MESSAGE_MAP(CSceneDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON4, &CSceneDialog::OnBnClicked_AddLayer)
	ON_BN_CLICKED(IDC_BUTTON3, &CSceneDialog::OnBnClicked_DeleteLayer)
	ON_BN_CLICKED(IDC_BUTTON9, &CSceneDialog::OnBnClicked_LoadBackImage)
	ON_BN_CLICKED(IDC_BUTTON10, &CSceneDialog::OnBnClicked_AddTile)
	ON_BN_CLICKED(IDC_BUTTON11, &CSceneDialog::OnBnClicked_DeleteCollision)
	ON_BN_CLICKED(IDC_BUTTON18, &CSceneDialog::OnBnClicked_AdjustGrid)
	ON_LBN_SELCHANGE(IDC_LIST2, &CSceneDialog::OnLbnSelchange_LayerList)
	ON_LBN_SELCHANGE(IDC_LIST3, &CSceneDialog::OnLbnSelchange_CollList)
	ON_BN_CLICKED(IDC_BUTTON19, &CSceneDialog::OnBnClicked_HideLayer)
	ON_BN_CLICKED(IDC_BUTTON1, &CSceneDialog::OnBnClicked_ClearPallete)
	ON_BN_CLICKED(IDC_BUTTON2, &CSceneDialog::OnBnClicked_SavePallete)
	ON_BN_CLICKED(IDC_BUTTON5, &CSceneDialog::OnBnClicked_LoadPallete)
	ON_BN_CLICKED(IDC_BUTTON22, &CSceneDialog::OnBnClicked_SaveScene)
	ON_BN_CLICKED(IDC_BUTTON23, &CSceneDialog::OnBnClicked_LoadScene)
	ON_BN_CLICKED(IDC_BUTTON7, &CSceneDialog::OnBnClicked_LayerUp)
	ON_BN_CLICKED(IDC_BUTTON6, &CSceneDialog::OnBnClicked_LayerDown)
	ON_BN_CLICKED(IDC_BUTTON24, &CSceneDialog::OnBnClicked_AdjustLayer)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSceneDialog::OnCbnSelchange_CollType)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CSceneDialog::OnCbnSelchange_LayerType)
END_MESSAGE_MAP()


// CSceneDialog 메시지 처리기


BOOL CSceneDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_LayerTypeCombo.AddString(L"Back Layer");
	m_LayerTypeCombo.AddString(L"Object Layer");
	m_LayerTypeCombo.AddString(L"Tile Layer");
	m_LayerTypeCombo.AddString(L"Collision Layer");
	m_LayerTypeCombo.SetCurSel(0);

	m_CollTypeCombo.AddString(L"모두 충돌");
	m_CollTypeCombo.AddString(L"단층");
	m_CollTypeCombo.AddString(L"상호작용");
	m_CollTypeCombo.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSceneDialog::OnBnClicked_HideLayer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pCurrScene == nullptr)
	{
		MessageBox(L"Scene이 비어있는데용", L"ERROR", MB_OK);
		return;
	}

	int iSel = m_LayerListbox.GetCurSel();
	if (iSel == -1)
	{
		MessageBox(L"레이어를 선택해주세용", L"ERROR", MB_OK);
		return;
	}

	m_pCurrScene->m_vecLayer[iSel]->m_bRender = !m_pCurrScene->m_vecLayer[iSel]->m_bRender;
}


void CSceneDialog::OnBnClicked_AddLayer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pCurrScene == nullptr)
	{
		MessageBox(L"Scene이 비어있는데용", L"ERROR", MB_OK);
		return;
	}

	m_pCurrScene->Add_Layer();
}


void CSceneDialog::OnBnClicked_DeleteLayer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pCurrScene == nullptr)
	{
		MessageBox(L"Scene이 비어있는데용", L"ERROR", MB_OK);
		return;
	}

	int iSel = m_LayerListbox.GetCurSel();
	if (iSel == -1)
	{
		MessageBox(L"레이어를 선택해주세용", L"ERROR", MB_OK);
		return;
	}

	m_pCurrScene->Delete_Layer(iSel);
}


void CSceneDialog::OnBnClicked_AdjustLayer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pCurrScene == nullptr)
	{
		MessageBox(L"Scene이 비어있는데용", L"ERROR", MB_OK);
		return;
	}

	int iSel = m_LayerListbox.GetCurSel();
	if (iSel == -1)
	{
		MessageBox(L"레이어를 선택해주세용", L"ERROR", MB_OK);
		return;
	}

	m_pCurrScene->Adjust_Layer(iSel);
}


void CSceneDialog::OnLbnSelchange_LayerList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pCurrScene == nullptr)
	{
		MessageBox(L"Scene이 비어있는데용", L"ERROR", MB_OK);
		return;
	}

	int iSel = m_LayerListbox.GetCurSel();
	if (iSel == -1)
	{
		MessageBox(L"레이어를 선택해주세용", L"ERROR", MB_OK);
		return;
	}

	m_pCurrScene->m_vecLayer[iSel]->Update_DialogData();
}


void CSceneDialog::OnCbnSelchange_LayerType()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pCurrScene == nullptr)
		return;

	int iSel = m_LayerListbox.GetCurSel();
	if (iSel == -1)
		return;

	m_pCurrScene->m_vecLayer[iSel]->m_eType = (LAYER_TYPE)m_LayerTypeCombo.GetCurSel();
	m_pCurrScene->m_vecLayer[iSel]->Update_DialogData();
}


void CSceneDialog::OnBnClicked_LayerUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pCurrScene == nullptr)
	{
		MessageBox(L"Scene이 비어있는데용", L"ERROR", MB_OK);
		return;
	}

	int iSel = m_LayerListbox.GetCurSel();
	if (iSel == -1)
	{
		MessageBox(L"레이어를 선택해주세용", L"ERROR", MB_OK);
		return;
	}

	m_pCurrScene->Layer_Up(iSel);
}


void CSceneDialog::OnBnClicked_LayerDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pCurrScene == nullptr)
	{
		MessageBox(L"Scene이 비어있는데용", L"ERROR", MB_OK);
		return;
	}

	int iSel = m_LayerListbox.GetCurSel();
	if (iSel == -1)
	{
		MessageBox(L"레이어를 선택해주세용", L"ERROR", MB_OK);
		return;
	}

	m_pCurrScene->Layer_Down(iSel);
}


void CSceneDialog::OnBnClicked_LoadBackImage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pCurrScene == nullptr)
	{
		MessageBox(L"Scene이 비어있는데용", L"ERROR", MB_OK);
		return;
	}

	int iSel = m_LayerListbox.GetCurSel();
	if (iSel == -1)
	{
		MessageBox(L"레이어를 선택해주세용", L"ERROR", MB_OK);
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
		TCHAR szRelativePath[MAX_STR] = L"";
		TCHAR szCurrentPath[MAX_STR] = L"";

		GetCurrentDirectory(MAX_STR, szCurrentPath);
		PathRelativePathTo(szRelativePath, szCurrentPath, FILE_ATTRIBUTE_DIRECTORY,
			Dlg.GetPathName().GetString(), FILE_ATTRIBUTE_DIRECTORY);

		wstring strRelativePath = wstring(szRelativePath);
		wstring strImageTag = Dlg.GetFileTitle().GetString();

		m_pCurrScene->Change_Image(iSel, strImageTag, strRelativePath);
	}
}


void CSceneDialog::OnBnClicked_AdjustGrid()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	g_iGridX = m_iGridX;
	g_iGridY = m_iGridY;
	UpdateData(FALSE);
}


void CSceneDialog::OnBnClicked_AddTile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	// 팔레트에 타일 추가

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
	lstrcat(szCurPath, L"\\Binary\\Resources\\Sprite\\Tile\\"); 
	Dlg.m_ofn.lpstrInitialDir = szCurPath;

	if (IDOK == Dlg.DoModal())
	{
		TCHAR szTmp[4096];
		CString strFileName = PathFindFileName(Dlg.GetFileName());
		CString strExtension = PathFindExtension(Dlg.GetFileName());
		ZeroMemory(szTmp, 4096);
		StrCpy(szTmp, strFileName);
		PathRemoveExtension(szTmp);

		if (strExtension == L".bmp")
		{
			if (!CResourceManager::GetInstance()->Check_Bmp(szTmp))
			{
				if (FAILED(CResourceManager::GetInstance()->Load_Bmp(Dlg.GetPathName().GetString(), szTmp)))
				{
					MessageBox(L"이미지 로드 실패", L"ERROR", MB_OK);
					return;
				}
			}
		}
		else
		{
			if (!CResourceManager::GetInstance()->Check_Sprite(szTmp))
			{
				if (FAILED(CResourceManager::GetInstance()->Load_Sprite(Dlg.GetPathName().GetString(), szTmp)))
				{
					MessageBox(L"이미지 로드 실패", L"ERROR", MB_OK);
					return;
				}
			}
		}

		TCHAR szRelativePath[MAX_STR] = L"";
		TCHAR szCurrentPath[MAX_STR] = L"";

		GetCurrentDirectory(MAX_STR, szCurrentPath);

		PathRelativePathTo(szRelativePath, szCurrentPath, FILE_ATTRIBUTE_DIRECTORY,
			Dlg.GetPathName().GetString(), FILE_ATTRIBUTE_DIRECTORY);

		m_pCurrScene->m_pPallete->Add_Tile(szRelativePath, szTmp);
	}
}


void CSceneDialog::OnBnClicked_DeleteCollision()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pCurrScene == nullptr)
	{
		MessageBox(L"Scene이 비어있는데용", L"ERROR", MB_OK);
		return;
	}

	int iSel = m_LayerListbox.GetCurSel();
	if (iSel == -1)
	{
		MessageBox(L"레이어를 선택해주세용", L"ERROR", MB_OK);
		return;
	}

	int iSel2 = m_CollListbox.GetCurSel();
	if (iSel2 == -1)
	{
		MessageBox(L"충돌체를 선택해주세용", L"ERROR", MB_OK);
		return;
	}

	m_pCurrScene->m_vecLayer[iSel]->Delete_Coll(iSel2);
}


void CSceneDialog::OnLbnSelchange_CollList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pCurrScene == nullptr)
	{
		MessageBox(L"Scene이 비어있는데용", L"ERROR", MB_OK);
		return;
	}

	int iSel = m_LayerListbox.GetCurSel();
	if (iSel == -1)
		return;

	int iSel2 = m_CollListbox.GetCurSel();
	if (iSel2 == -1)
		return;

	int iType = m_pCurrScene->m_vecLayer[iSel]->m_vecColl[iSel2]->iType;
	m_CollTypeCombo.SetCurSel(iType);
}


void CSceneDialog::OnCbnSelchange_CollType()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pCurrScene == nullptr)
	{
		MessageBox(L"Scene이 비어있는데용", L"ERROR", MB_OK);
		return;
	}

	int iSel = m_LayerListbox.GetCurSel();
	if (iSel == -1)
		return;

	int iSel2 = m_CollListbox.GetCurSel();
	if (iSel2 == -1)
		return;

	m_pCurrScene->Change_CollType(iSel, iSel2);
}


void CSceneDialog::OnBnClicked_ClearPallete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_pCurrScene == nullptr)
		return;

	m_pCurrScene->m_pPallete->Clear_Pallete();
}


void CSceneDialog::OnBnClicked_SavePallete()
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
	lstrcat(szCurPath, L"\\Binary\\Data\\Pallete");

	Dlg.m_ofn.lpstrInitialDir = szCurPath;

	if (Dlg.DoModal() == IDOK)
	{
		wstring path = Dlg.GetPathName();

		// 팔레트 저장
		m_pCurrScene->m_pPallete->Save_Pallete(path);
	}
}


void CSceneDialog::OnBnClicked_LoadPallete()
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
	lstrcat(szCurPath, L"\\Binary\\Data\\Pallete");

	Dlg.m_ofn.lpstrInitialDir = szCurPath;

	if (Dlg.DoModal() == IDOK)
	{
		wstring path = Dlg.GetPathName();

		// 팔레트 로드
		m_pCurrScene->m_pPallete->Load_Pallete(path);
	}
}


void CSceneDialog::OnBnClicked_SaveScene()
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
	lstrcat(szCurPath, L"\\Binary\\Data\\Scene");

	Dlg.m_ofn.lpstrInitialDir = szCurPath;

	if (Dlg.DoModal() == IDOK)
	{
		wstring path = Dlg.GetPathName();
		m_pCurrScene->Save_Scene(path);
	}
}

void CSceneDialog::OnBnClicked_LoadScene()
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
	lstrcat(szCurPath, L"\\Binary\\Data\\Scene");

	Dlg.m_ofn.lpstrInitialDir = szCurPath;

	if (Dlg.DoModal() == IDOK)
	{
		wstring path = Dlg.GetPathName();
		m_pCurrScene->Load_Scene(path);
	}
}

void CSceneDialog::Set_TileLayer_Option(bool bIsTile)
{
	GetDlgItem(IDC_EDIT1)->EnableWindow(!bIsTile);
	GetDlgItem(IDC_BUTTON9)->EnableWindow(!bIsTile);
}
