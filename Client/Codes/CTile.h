#pragma once
#include "CGameObj.h"

class CTile : public CGameObj
{
public:
	explicit CTile();
	~CTile();

public:
	virtual HRESULT	Ready_GameObj(wstring strTag, wstring strPath, float fX, float fY);
	virtual INT				Update_GameObj(const float& fTimeDelta);
	virtual void			Render_GameObj(HDC hDC);

public:
	wstring			m_strTag = L"";
	bool				m_bRender = false;

public:
	static CTile* Create(wstring strTag, wstring strPath, float fX, float fY);

private:
	virtual void			Free();
};
