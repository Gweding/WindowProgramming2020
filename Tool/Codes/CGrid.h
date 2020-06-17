#pragma once
#include "CGameObj.h"

class CGrid :	public CGameObj
{
public:
	explicit CGrid();
	~CGrid();

public:
	virtual HRESULT	Ready_GameObj();
	virtual INT				Update_GameObj(const float& fTimeDelta);
	virtual void			Render_GameObj(HDC hdc);

public:
	static CGrid* Create();

public:
	bool m_bRender = true;

private:
	virtual void			Free();
};

