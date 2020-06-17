#pragma once
#include "CGameObj.h"
#include "CTile.h"
#include "CSceneDialog.h"

class CMapLayer : public CGameObj
{
public:
	explicit CMapLayer();
	~CMapLayer();

public:
	virtual HRESULT	Ready_GameObj();
	virtual INT				Update_GameObj(const float& fTimeDelta);
	virtual void			Render_GameObj(HDC hdc);

private:
	INT		Update_BackLayer(const float& fTimeDelta);
	INT		Update_ObjectLayer(const float& fTimeDelta);
	INT		Update_TileLayer(const float& fTimeDelta);
	INT		Update_CollisionLayer(const float& fTimeDelta);

private:
	void		Render_BackLayer(HDC hdc);
	void		Render_ObjectLayer(HDC hdc);
	void		Render_TileLayer(HDC hdc);
	void		Render_CollisionLayer(HDC hdc);

public:
	HRESULT Adjust_DialogData();
	HRESULT Change_Image(wstring strTag, wstring strPath);
	HRESULT Change_CollType(int iIndex);
	HRESULT Delete_Coll(int iIndex);

public:
	void		Update_DialogData();
	void		Update_CollListData();

public:
	HRESULT Save_Layer(wofstream& fout);

private:
	HRESULT Save_ImageLayer(wofstream& fout);
	HRESULT Save_ObjectLayer(wofstream& fout);
	HRESULT Save_TileLayer(wofstream& fout);
	HRESULT Save_CollLayer(wofstream& fout);

public:
	HRESULT Load_ImageLayer(wifstream& fin);
	HRESULT Load_ObjectLayer(wifstream& fin);
	HRESULT Load_TileLayer(wifstream& fin);
	HRESULT Load_CollLayer(wifstream& fin);

public:
	LAYER_TYPE m_eType;
	float m_fSpeed = 1.f;
	wstring m_strLayerTag = L"";
	float m_fSize[2] = {};

public:
	wstring m_strSpriteKey = L"";
	wstring m_strSpritePath = L"";

public:
	list<CTile*> m_TileList;
	wstring m_strTileKey = L"";
	wstring m_strTilePath = L"";

public:
	bool m_bRender = true;
	RECT m_tViewRect;
	CSceneDialog* m_pDialog = nullptr;

public:
	vector<COLL_RECT*> m_vecColl;
	POINT m_tAddPoint[2];
	bool m_bAddRect = false;
	int m_iFixIndex = -1;

public:
	HPEN			m_hPen;
	HGDIOBJ	m_hOldPen;
	HBRUSH		m_hBrush;
	HGDIOBJ	m_hOldBrush;

public:
	static CMapLayer* Create();

protected:
	virtual void			Free();
};

