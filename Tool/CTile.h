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
	virtual void			Render_GameObj(HDC hdc);

public:
	wstring			m_strTag = L"";
	wstring			m_strPath = L"";
	bool				m_bSelected = false;

public:
	static CTile* Create(wstring strTag, wstring strPath, float fX, float fY);

private:
	virtual void			Free();
};

