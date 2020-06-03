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

IMPLEMENT_DYNAMIC(CSceneDialog, CDialogEx)

CSceneDialog::CSceneDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SceneDialog, pParent)
	, m_strBackImage(_T(""))
	, m_iGridX(100)
	, m_iGridY(100)
	, m_fBackSpeed(1.f)
	, m_strLayerTag(_T("Default"))
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
	DDX_Control(pDX, IDC_RADIO1, m_LayerType[LAYER_BACK]);
	DDX_Control(pDX, IDC_RADIO2, m_LayerType[LAYER_TILE]);
	DDX_Text(pDX, IDC_EDIT1, m_strBackImage);
	DDX_Control(pDX, IDC_LIST3, m_CollListbox);
	DDX_Control(pDX, IDC_RADIO3, m_CollType[COLL_ALL]);
	DDX_Control(pDX, IDC_RADIO4, m_CollType[COLL_JUMP]);
	DDX_Control(pDX, IDC_RADIO5, m_CollType[COLL_INTERACT]);
	DDX_Control(pDX, IDC_COMBO1, m_InteractCombo);
	DDX_Text(pDX, IDC_EDIT5, m_iGridX);
	DDX_Text(pDX, IDC_EDIT6, m_iGridY);
	DDX_Text(pDX, IDC_EDIT7, m_fBackSpeed);
	DDX_Text(pDX, IDC_EDIT3, m_strLayerTag);
}


BEGIN_MESSAGE_MAP(CSceneDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON7, &CSceneDialog::OnBnClicked_AddSceneBGM)
	ON_BN_CLICKED(IDC_BUTTON8, &CSceneDialog::OnBnClicked_ViewSceneInfo)
	ON_BN_CLICKED(IDC_BUTTON4, &CSceneDialog::OnBnClicked_AddLayer)
	ON_BN_CLICKED(IDC_BUTTON3, &CSceneDialog::OnBnClicked_DeleteLayer)
	ON_BN_CLICKED(IDC_BUTTON9, &CSceneDialog::OnBnClicked_LoadBackImage)
	ON_BN_CLICKED(IDC_BUTTON10, &CSceneDialog::OnBnClicked_AddTile)
	ON_BN_CLICKED(IDC_BUTTON11, &CSceneDialog::OnBnClicked_DeleteCollision)
	ON_BN_CLICKED(IDC_BUTTON17, &CSceneDialog::OnBnClicked_ChangeCollision)
	ON_BN_CLICKED(IDC_BUTTON18, &CSceneDialog::OnBnClicked_AdjustGrid)
	ON_BN_CLICKED(IDC_RADIO1, &CSceneDialog::OnBnClicked_LayerBack)
	ON_BN_CLICKED(IDC_RADIO2, &CSceneDialog::OnBnClicked_LayerTile)
	ON_LBN_SELCHANGE(IDC_LIST2, &CSceneDialog::OnLbnSelchange_LayerList)
	ON_LBN_SELCHANGE(IDC_LIST3, &CSceneDialog::OnLbnSelchange_CollList)
	ON_BN_CLICKED(IDC_BUTTON19, &CSceneDialog::OnBnClicked_HideLayer)
	ON_BN_CLICKED(IDC_BUTTON20, &CSceneDialog::OnBnClicked_AdjustBackSpeed)
END_MESSAGE_MAP()


// CSceneDialog 메시지 처리기


BOOL CSceneDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	if (nullptr == m_SceneInfo.GetSafeHwnd())
		m_SceneInfo.Create(IDD_SceneInfoDialog);
	if (nullptr == m_SoundList.GetSafeHwnd())
	{
		m_SoundList.Create(IDD_SoundList);
		m_SoundList.m_bMainSound = false;
	}

	m_LayerType[LAYER_BACK].SetCheck(TRUE);
	m_CollType[COLL_ALL].SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSceneDialog::OnBnClicked_AddSceneBGM()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//if (m_SceneListbox.GetCount() == 0)
	//{
	//	MessageBox(L"브금 설정할 Scene이 없는데용?", L"ERROR", MB_OK);
	//	return;
	//}

	m_SoundList.ShowWindow(SW_SHOW);
}


void CSceneDialog::OnBnClicked_ViewSceneInfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//if (m_SceneListbox.GetCount() == 0)
	//{
	//	MessageBox(L"정보를 볼 Scene이 없는데용?", L"ERROR", MB_OK);
	//	return;
	//}

	m_SceneInfo.ShowWindow(SW_SHOW);
}


void CSceneDialog::OnBnClicked_HideLayer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pCurrLayer == nullptr)
	{
		MessageBox(L"Layer 선택 해주세용", L"ERROR", MB_OK);
		return;
	}

	m_pCurrLayer->m_bRender = !m_pCurrLayer->m_bRender;
}


void CSceneDialog::OnBnClicked_AddLayer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pCurrScene == nullptr)
	{
		MessageBox(L"Scene 선택 해주세용", L"ERROR", MB_OK);
		return;
	}

	CMapLayer* pLayer = CMapLayer::Create(LAYER_BACK);
	if (pLayer == nullptr)
		return;

	m_LayerType[LAYER_BACK].SetCheck(TRUE);

	UpdateData(TRUE);
	m_pCurrScene->Add_Layer(m_strLayerTag.GetString(), pLayer);
	m_pCurrScene->Update_LayerList(&m_LayerListbox, &m_pCurrLayer);
	UpdateData(FALSE);
}


void CSceneDialog::OnBnClicked_DeleteLayer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pCurrScene == nullptr)
	{
		MessageBox(L"Scene 선택 해주세용", L"ERROR", MB_OK);
		return;
	}

	int iLayerSel = m_LayerListbox.GetCurSel();
	CString strLayerTag;
	m_LayerListbox.GetText(iLayerSel, strLayerTag);

	m_pCurrScene->Delete_Layer(strLayerTag.GetString());
	m_LayerListbox.DeleteString(iLayerSel);

	m_pCurrLayer = nullptr;
}


void CSceneDialog::OnBnClicked_LoadBackImage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pCurrLayer == nullptr)
	{
		MessageBox(L"Layer 선택 해주세용", L"ERROR", MB_OK);
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
	lstrcat(szCurPath, L"\\Bin\\Resources\\Sprite\\");
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
				if (FAILED(CResourceManager::GetInstance()->Load_Bmp(Dlg.GetPathName().GetString(), strFileName.GetString())))
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
				if(FAILED(CResourceManager::GetInstance()->Load_Sprite(Dlg.GetPathName().GetString(), strFileName.GetString())))
				{
					MessageBox(L"이미지 로드 실패", L"ERROR", MB_OK);
					return;
				}
			}
		}

		m_pCurrLayer->m_strSpriteKey = strFileName.GetString();
		UpdateData(TRUE);
		m_strBackImage = strFileName;
		UpdateData(FALSE);
	}
}



void CSceneDialog::OnBnClicked_AdjustBackSpeed()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pCurrLayer == nullptr)
	{
		MessageBox(L"Layer 선택 해주세용", L"ERROR", MB_OK);
		return;
	}

	UpdateData(TRUE);
	m_pCurrLayer->m_fSpeed = m_fBackSpeed;
	UpdateData(FALSE);
}


void CSceneDialog::OnBnClicked_LayerBack()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pCurrLayer == nullptr)
	{
		MessageBox(L"Layer 선택 해주세용", L"ERROR", MB_OK);
		return;
	}

	m_pCurrLayer->m_eType = LAYER_BACK;

	GetDlgItem(IDC_TILEPALLETE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON10)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON9)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON20)->EnableWindow(TRUE);
}


void CSceneDialog::OnBnClicked_LayerTile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pCurrLayer == nullptr)
	{
		MessageBox(L"Layer 선택 해주세용", L"ERROR", MB_OK);
		return;
	}

	m_pCurrLayer->m_eType = LAYER_TILE;

	GetDlgItem(IDC_TILEPALLETE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON10)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON9)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON20)->EnableWindow(FALSE);
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
}


void CSceneDialog::OnBnClicked_DeleteCollision()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CSceneDialog::OnBnClicked_ChangeCollision()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CSceneDialog::OnLbnSelchange_LayerList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pCurrScene == nullptr)
		return;

	int iSel = m_LayerListbox.GetCurSel();
	CString strName;
	m_LayerListbox.GetText(iSel, strName);

	m_pCurrLayer = m_pCurrScene->Get_Layer(strName.GetString());

	LAYER_TYPE eType = m_pCurrLayer->m_eType;
	if (eType == LAYER_BACK)
	{
		UpdateData(TRUE);
		m_strBackImage = m_pCurrLayer->m_strSpriteKey.c_str();
		UpdateData(FALSE);
	}
	else if(eType == LAYER_TILE)
	{

	}

	for (int i = 0; i < LAYER_END; ++i)
		m_LayerType[i].SetCheck(FALSE);
	m_LayerType[eType].SetCheck(TRUE);
}


void CSceneDialog::OnLbnSelchange_CollList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
