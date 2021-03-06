#pragma once
#include "CGameObj.h"

class CAnimation : public CGameObj
{
public:
	explicit CAnimation();
	virtual ~CAnimation();

public:
	RECT Get_CollRect();
	int Get_CollSize(int iAxis);
	RECT Get_OriginCollRect() { return m_tCollRect; }
	BOOL& Get_RenderCollider() { return m_bRenderCollider; }

public:
	virtual HRESULT		Ready_GameObj();
	virtual int					Update_GameObj(const float& fTimeDelta);
	virtual void				Render_GameObj(HDC hDC);

public:
	HRESULT					Add_Frame(FRAME* pFrame);
	HRESULT					Add_CollRect(RECT tRect);

public:
	BOOL							Check_FrameEnd() { return m_bAnimationEnd; }

public:
	void								Update_Position(float fX, float fY);

private:
	int m_iSize = 1;
	float m_fCurrFrame = 0.f;

private:
	RECT m_tCollRect = {};
	vector<FRAME*>	m_vecFrame;

private:
	BOOL m_bAnimationEnd = FALSE;
	BOOL m_bRenderCollider = FALSE;

private:
	HPEN			m_hPen;
	HGDIOBJ	m_hOldPen;
	HBRUSH		m_hBrush;
	HGDIOBJ	m_hOldBrush;

public:
	static CAnimation* Create();

private:
	virtual void	Free();
};

