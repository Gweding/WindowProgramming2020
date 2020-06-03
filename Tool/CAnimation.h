#pragma once
#include "CGameObj.h"

class CAnimation : public CGameObj
{
public:
	explicit CAnimation();
	~CAnimation();

public:
	virtual HRESULT	Ready_GameObj();
	virtual INT				Update_GameObj(const float& fTimeDelta);
	virtual void			Render_GameObj(HDC hdc);

protected:
	virtual void			Free();
};

