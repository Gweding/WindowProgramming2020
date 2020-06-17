#pragma once
#include "CScene.h"

class CScene_Logo : public CScene
{
public:
	explicit CScene_Logo();
	~CScene_Logo();

public:
	virtual HRESULT		Ready_Scene();
	virtual HRESULT		Update_Scene(const float& fTimeDelta);
	virtual HRESULT		Render_Scene(HDC hDC);

public:
	static CScene_Logo* Create();

private:
	wstring m_strTag = L"";
	float m_fAlpha = 0.f;
	float m_fSpeed = 100.f;
	float m_fTime = 0.f;
	bool m_bLogoEnd = false;
	bool m_bSceneChange = false;

private:
	virtual void Free();
};

