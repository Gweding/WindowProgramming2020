#pragma once
#include "CGameObj.h"

class CScene;
class CPallete : public CGameObj
{
public:
	explicit CPallete();
	~CPallete();

public:
	virtual HRESULT	Ready_GameObj();
	virtual INT				Update_GameObj(const float& fTimeDelta);
	virtual void			Render_GameObj(HDC hdc);

public:
	HRESULT				Add_Tile(wstring strPath, wstring strTag);
	HRESULT				Clear_Pallete();
	HRESULT				Save_Pallete(wstring strPath);
	HRESULT				Load_Pallete(wstring strPath);

public:
	HDC m_PicCtrl;
	HWND m_PicHwnd;
	TILE m_tSelected;
	list<TILE*> m_TileList;

public:
	static CPallete* Create();

private:
	virtual void			Free();
};

