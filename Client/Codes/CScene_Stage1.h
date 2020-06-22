#pragma once
#include "CScene.h"

class CScene_Stage1 : public CScene
{
public:
	explicit CScene_Stage1();
	~CScene_Stage1();

public:
	virtual HRESULT		Ready_Scene();
	virtual HRESULT		Update_Scene(const float& fTimeDelta);
	virtual HRESULT		Render_Scene(HDC hDC);

public:
	static CScene_Stage1* Create();

private:
	CImage m_pImage;

private:
	virtual void Free();
};

