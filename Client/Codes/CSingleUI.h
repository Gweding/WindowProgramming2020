#pragma once
#include "CGameObj.h"

class CAnimation;
class CPortal : public CGameObj
{
public:
	explicit CPortal();
	virtual ~CPortal();

public:
	virtual HRESULT		Ready_GameObj(float fStartX, float fStartY);
	virtual int					Update_GameObj(const float& fTimeDelta);
	virtual void				Render_GameObj(HDC hDC);

private:
	bool							m_bRenderUI = false;
	CAnimation*				m_pAnimation = nullptr;

public:
	static CPortal* Create(float fStartX, float fStartY);

private:
	virtual void	Free();
};

