#pragma once
#include "CScene.h"

class CScene_Event : public CScene
{
public:
	explicit CScene_Event();
	~CScene_Event();

public:
	virtual HRESULT		Ready_Scene(int iType);
	virtual HRESULT		Update_Scene(const float& fTimeDelta);
	virtual HRESULT		Render_Scene(HDC hDC);

public:
	static CScene_Event* Create(int iType);

private:
	int m_iType = 0;
	float m_fTime = 0.f;

private:
	CImage m_pImage;
	bool m_bRender = false;

private:
	HFONT m_hFont;
	HFONT m_oldFont;

private:
	virtual void Free();
};

