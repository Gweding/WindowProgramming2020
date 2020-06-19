#pragma once
#include "CGameObj.h"

class CTile;
class CLayer;
class CMap : public CGameObj
{
public:
	explicit CMap();
	virtual ~CMap();

public:
	virtual HRESULT		Ready_GameObj();
	virtual int					Update_GameObj(const float& fTimeDelta);
	virtual void				Render_GameObj(HDC hDC);

public:
	void								Render_Collider(HDC hDC);

public:
	list<COLL_RECT*>& Get_MapCollider() { return m_lstCollision; }

public:
	HRESULT					Add_Tile(CTile* pTile);
	HRESULT					Add_Layer(CLayer* pLayer);
	HRESULT					Add_Collision(COLL_RECT* pRect);

private:
	BOOL							m_bRenderCollider = TRUE;

private:
	list<CTile*>				m_lstTile;
	list<CLayer*>			m_lstLayer;
	list<COLL_RECT*>	m_lstCollision;

private:
	HPEN			m_hPen;
	HGDIOBJ	m_hOldPen;
	HBRUSH		m_hBrush;
	HGDIOBJ	m_hOldBrush;

public:
	static CMap* Create();

private:
	virtual void	Free();
};
