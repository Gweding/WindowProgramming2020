#pragma once
#include "CScene.h"

class CScene_Stage0 : public CScene
{
public:
	explicit CScene_Stage0();
	~CScene_Stage0();

public:
	virtual HRESULT		Ready_Scene();
	virtual HRESULT		Update_Scene(const float& fTimeDelta);
	virtual HRESULT		Render_Scene(HDC hDC);

public:
	static CScene_Stage0* Create();

private:
	CImage m_pImage;

private:
	virtual void Free();
};

