#pragma once
#include "CScene.h"

class CScene_Stage2 : public CScene
{
public:
	explicit CScene_Stage2();
	~CScene_Stage2();

public:
	virtual HRESULT		Ready_Scene();
	virtual HRESULT		Update_Scene(const float& fTimeDelta);
	virtual HRESULT		Render_Scene(HDC hDC);

public:
	static CScene_Stage2* Create();

private:
	CImage m_pImage;

private:
	virtual void Free();
};

