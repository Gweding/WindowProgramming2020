#pragma once
#include "CScene.h"

class CScene_Stage : public CScene
{
public:
	explicit CScene_Stage();
	~CScene_Stage();

public:
	virtual HRESULT		Ready_Scene();
	virtual HRESULT		Update_Scene(const float& fTimeDelta);
	virtual HRESULT		Render_Scene(HDC hDC);

public:
	static CScene_Stage* Create();

private:
	virtual void Free();
};

