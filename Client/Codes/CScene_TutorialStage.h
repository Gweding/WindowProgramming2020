#pragma once
#include "CScene.h"

class CScene_TutorialStage : public CScene
{
public:
	explicit CScene_TutorialStage();
	~CScene_TutorialStage();

public:
	virtual HRESULT		Ready_Scene();
	virtual HRESULT		Update_Scene(const float& fTimeDelta);
	virtual HRESULT		Render_Scene(HDC hDC);

public:
	static CScene_TutorialStage* Create();

private:
	float m_fTime = 0.f;
	CImage m_pImage;

private:
	virtual void Free();
};

