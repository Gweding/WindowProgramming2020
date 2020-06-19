#pragma once
#include "CGameObj.h"

class CPlayer : public CGameObj
{
public:
	explicit CPlayer();
	virtual ~CPlayer();

public:
	virtual HRESULT		Ready_GameObj(float fStartX, float fStartY);
	virtual int					Update_GameObj(const float& fTimeDelta);
	virtual void				Render_GameObj(HDC hDC);

private:
	int								Update_Key(const float& fTimeDelta);
	int								Update_Collision();

private:
	float m_fSpeed = 500.f;
	CAnimation* m_pAnimation = nullptr;

private:
	bool							m_bJump = false;
	float							m_fJumpPower = 0.f;
	float							m_fJumpAccel = 0.f;

public:
	static CPlayer* Create(float fStartX, float fStartY);

protected:
	virtual void	Free();
};

