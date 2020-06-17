#pragma once
#include "CGameObj.h"

class CGameManager
{
	DECLARE_SINGLETON(CGameManager)

private:
	explicit CGameManager();
	~CGameManager();

public:
	HRESULT	Update_Object(const float& fTimeDelta);

public:
	HRESULT	Add_GameObject(OBJID eID, CGameObj* pGameObj);
	HRESULT	PopFront_GameObject(OBJID eID);
	HRESULT	PopBack_GameObject(OBJID eID);
	HRESULT	Delete_OBJLIST(OBJID eID);
	HRESULT	Reset_OBJLIST();

private:
	OBJLIST		m_ObjLst[OBJID::OBJ_END];
};

