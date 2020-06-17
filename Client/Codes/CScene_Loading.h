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

public:
	static CScene_Loading* Create();

private:
	static unsigned int __stdcall Load_Resource(void* pParam);

private:
	CRITICAL_SECTION		m_CriticalSection;
	HANDLE							m_hLoadingThread;

private:
	virtual void Free();
};

