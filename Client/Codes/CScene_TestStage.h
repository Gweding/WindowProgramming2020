#pragma once
#include "CScene.h"

class CScene_TestStage : public CScene
{
public:
	explicit CScene_TestStage();
	~CScene_TestStage();

public:
	virtual HRESULT		Ready_Scene();
	virtual HRESULT		Update_Scene(const float& fTimeDelta);
	virtual HRESULT		Render_Scene(HDC hDC);

public:
	static CScene_TestStage* Create();

private:
	CImage m_pImage;

private:
	virtual void Free();
};

