#pragma once
#include "CGameObj.h"
#include "CScene.h"
#include "CAnimation.h"

class CProject
{
public:
	explicit CProject();
	~CProject();

public:
	virtual HRESULT	Ready_Project();
	virtual INT				Update_Project(const float& fTimeDelta);
	virtual void			Render_Project(HDC hdc);

public:
	bool m_bRender[RENDER_END];

public:
	CScene* m_pScene;
	CAnimation* m_pAnimation;

public:
	HWND m_AnimationHwnd;

private:
	CKeyManager* m_pKeyMgr;
	CTimeManager* m_pTimeMgr;
	CSoundManager* m_pSoundMgr;
	CResourceManager* m_pResourceMgr;

private:
	// For Gdi+
	ULONG_PTR m_pGdiPlusTokenData;

public:
	static CProject*	Create();

private:
	virtual void			Free();
};

