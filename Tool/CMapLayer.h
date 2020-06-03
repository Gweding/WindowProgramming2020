#pragma once
#include "CGameObj.h"

class CMapLayer : public CGameObj
{
public:
	explicit CMapLayer();
	~CMapLayer();

public:
	virtual HRESULT	Ready_GameObj(LAYER_TYPE eType);
	virtual INT				Update_GameObj(const float& fTimeDelta);
	virtual void			Render_GameObj(HDC hdc);

public:
	wstring m_strTag = L"";
	wstring m_strSpriteKey = L"Default";

public:
	bool m_bRender = true;
	float m_fSpeed = 1.f;
	LAYER_TYPE m_eType;
	POINT m_tPosition = {};

public:
	static CMapLayer* Create(LAYER_TYPE eType);

private:
	virtual void			Free();
};

