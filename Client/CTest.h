#pragma once
#include "CGameObj.h"

class CTest : public CGameObj
{
public:
	CTest();
	~CTest();

public:
	virtual HRESULT		Ready_GameObj(float fX, float fY, wstring strTag);
	virtual int					Update_GameObj(const float& fTimeDelta);
	virtual void				Render_GameObj(HDC hDC);

private:
	CImage m_pImage;

public:
	static CTest* Create(float fX, float fY, wstring strTag);

protected:
	virtual void	Free();
};

