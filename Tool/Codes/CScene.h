#pragma once
#include "CGameObj.h"

class CGrid;
class CPallete;
class CMapLayer;
class CScene : public CGameObj
{
public:
	explicit CScene();
	~CScene();

public:
	virtual HRESULT	Ready_GameObj();
	virtual INT				Update_GameObj(const float& fTimeDelta);
	virtual void			Render_GameObj(HDC hdc);

public:
	HRESULT				Add_Layer();
	HRESULT				Delete_Layer(int iIndex);
	HRESULT				Adjust_Layer(int iIndex);
	HRESULT				Layer_Up(int iIndex);
	HRESULT				Layer_Down(int iIndex);
	HRESULT				Change_Image(int iIndex, wstring strTag, wstring strPath);
	HRESULT				Change_CollType(int iLayerIndex, int iCollIndex);

public:
	HRESULT				Save_Scene(wstring strPath);
	HRESULT				Load_Scene(wstring strPath);

public:
	void							Reset_ListBox();
	void							Set_HorizontalScroll();

public:
	CGrid* m_pGrid;
	CPallete* m_pPallete;

public:
	CListBox* m_pLayerList;
	CComboBox* m_pLayerTypeCombo;

public:
	vector<CMapLayer*> m_vecLayer;

public:
	static CScene* Create();

private:
	virtual void			Free();
};

