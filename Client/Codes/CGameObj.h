#pragma once

class CKeyManager;
class CTimeManager;
class CGameManager;
class CRenderManager;
class CResourceManager;
class CGameObj
{
public:
	explicit CGameObj();
	virtual ~CGameObj();

public:
	INFO& Get_Info()		{ return m_tInfo; }
	RECT& Get_Rect()	{ return m_tRect; }
	void								Dead_GameObj() { m_bIsDead = true; }

public:
	virtual HRESULT		Ready_GameObj();
	virtual void				LateInit_GameObj();
	virtual int					Update_GameObj(const float& fTimeDelta);
	virtual void				Render_GameObj(HDC hDC);

protected:
	void								Update_Rect();

protected:
	CRenderManager*	m_pRenderMgr = nullptr;
	CKeyManager*			m_pKeyMgr = nullptr;
	CTimeManager*		m_pTimeMgr = nullptr;
	CGameManager*		m_pGameMgr = nullptr;
	CResourceManager* m_pResourceMgr = nullptr;

protected:
	INFO			m_tInfo;
	RECT			m_tRect;
	COLOR		m_tColor;

protected:
	bool m_bIsDead = false;
	bool m_bIsLateInit = false;

protected:
	virtual void	Free();
};

