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
	afx_msg void OnBnClicked_AddSceneBGM();
	afx_msg void OnBnClicked_ViewSceneInfo();
	afx_msg void OnBnClicked_AddLayer();
	afx_msg void OnBnClicked_DeleteLayer();
	afx_msg void OnBnClicked_HideLayer();

public:
	afx_msg void OnBnClicked_LoadBackImage();
	afx_msg void OnBnClicked_AdjustBackSpeed();
	afx_msg void OnBnClicked_LayerBack();
	afx_msg void OnBnClicked_LayerTile();
	afx_msg void OnBnClicked_AdjustGrid();
	afx_msg void OnBnClicked_AddTile();

public:
	afx_msg void OnBnClicked_DeleteCollision();
	afx_msg void OnBnClicked_ChangeCollision();

public:
	afx_msg void OnLbnSelchange_LayerList();
	afx_msg void OnLbnSelchange_CollList();

public:
	CScene* m_pCurrScene;
	CMapLayer* m_pCurrLayer;

public:
	CSoundList m_SoundList;
	CSceneInfoDialog m_SceneInfo;

public:
	CListBox m_LayerListbox;
	CString m_strLayerTag;

public:
	CStatic m_TilePicCtrl;
	CButton m_LayerType[LAYER_END];
	CString m_strBackImage;
	UINT m_iGridX;
	UINT m_iGridY;
	float m_fBackSpeed;

public:
	CListBox m_CollListbox;
	CButton m_CollType[COLL_END];
	CComboBox m_InteractCombo;
};
