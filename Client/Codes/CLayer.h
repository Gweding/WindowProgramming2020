#pragma once
#include "CGameObj.h"

class CTile;
class CLayer : public CGameObj
{
public:
	explicit CLayer();
	virtual ~CLayer();

public:
	bool& Get_Cull() { return m_bCull; }

public:
	virtual HRESULT		Ready_GameObj(wstring strTag, wstring strPath, float fSpeed, float fSizeX, float fSizeY, float fX, float fY);
	virtual int					Update_GameObj(const float& fTimeDelta);
	virtual void				Render_GameObj(HDC hDC);

private:
	bool							m_bCull = false;
	bool							m_bRender = false;
	float							m_fSize[2] = {};
	wstring						m_strTag = L"";
	float							m_fSpeed = 0.f;

public:
	static CLayer* Create(wstring strTag, wstring strPath, float fSpeed, float fSizeX, float fSizeY, float fX, float fY);

private:
	virtual void	Free();
};
