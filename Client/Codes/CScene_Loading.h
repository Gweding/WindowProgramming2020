#pragma once
#include "CScene.h"

class CScene_Loading : public CScene
{
public:
	explicit CScene_Loading();
	~CScene_Loading();

public:
	virtual HRESULT		Ready_Scene();
	virtual HRESULT		Update_Scene(const float& fTimeDelta);
	virtual HRESULT		Render_Scene(HDC hDC);

private:
	HRESULT					Update_LogoAnimation(const float& fTimeDelta);
	HRESULT					Update_LoadingAnimation(const float& fTimeDelta);

private:
	static unsigned int __stdcall Load_Resource(void* pParam);

private:
	CRITICAL_SECTION		m_CriticalSection;
	HANDLE							m_hLoadingThread;

private:
	HFONT m_hFont;
	HFONT m_oldFont;

private:
	float							m_fCurrFrame = 0.f;
	wstring						m_strLoadingMessage = L"";
	bool							m_bLoadingEnd = false;
	bool							m_bTransition = false;

private:
	float							m_fTime = 0.f;
	float							m_fBackAlpha = 0.f;
	float							m_fLogoAlpha = 0.f;
	bool							m_bLogoAniEnd = false;

public:
	static CScene_Loading* Create();

private:
	virtual void Free();
};

