#pragma once
#include "CGameObj.h"

class CGrid;
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
	HRESULT			Add_Layer(wstring strTag, CMapLayer* pLayer);
	HRESULT			Delete_Layer(wstring strTag);
	CMapLayer*		Get_Layer(wstring strTag);

public:
	HRESULT			Update_LayerList(CListBox* pListBox, CMapLayer** ppCurrLayer);

public:
	CGrid* m_pGrid;
	list<CMapLayer*>		m_LayerList;

public:
	static CScene* Create();

private:
	virtual void			Free();
};

