#pragma once
#include "CSceneInfoDialog.h"
#include "CSoundList.h"

// CSceneDialog 대화 상자

class CScene;
class CMapLayer;
class CSceneDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSceneDialog)

public:
	CSceneDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSceneDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SceneDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

public:
	// Scene
	afx_msg void OnBnClicked_HideLayer();
	afx_msg void OnBnClicked_AddLayer();
	afx_msg void OnBnClicked_DeleteLayer();
	afx_msg void OnBnClicked_AdjustLayer();
	afx_msg void OnLbnSelchange_LayerList();
	afx_msg void OnCbnSelchange_LayerType();

public:
	afx_msg void OnBnClicked_LayerUp();
	afx_msg void OnBnClicked_LayerDown();
	afx_msg void OnBnClicked_LoadBackImage();

public:
	afx_msg void OnBnClicked_AddTile();
	afx_msg void OnBnClicked_AdjustGrid();

public:
	afx_msg void OnBnClicked_DeleteCollision();

public:
	afx_msg void OnLbnSelchange_CollList();
	afx_msg void OnCbnSelchange_CollType();

	// Pallete
public:
	afx_msg void OnBnClicked_ClearPallete();
	afx_msg void OnBnClicked_SavePallete();
	afx_msg void OnBnClicked_LoadPallete();

public:
	afx_msg void OnBnClicked_SaveScene();
	afx_msg void OnBnClicked_LoadScene();

public:
	void Set_TileLayer_Option(bool bIsTile);

public:
	CScene* m_pCurrScene;

public:
	CListBox m_LayerListbox;

public:
	CStatic m_TilePicCtrl;

public:
	CString m_strLayerTag;
	CString m_strBackImage;
	UINT m_iGridX;
	UINT m_iGridY;
	CComboBox m_LayerTypeCombo;
	float m_fBackSpeed;
	float m_fSizeX;
	float m_fSizeY;

public:
	CListBox m_CollListbox;
	CComboBox m_CollTypeCombo;
};
