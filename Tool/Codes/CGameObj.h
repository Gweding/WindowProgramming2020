#pragma once

class CGameObj
{
public:
	explicit CGameObj();
	~CGameObj();

public:
	virtual HRESULT	Ready_GameObj();
	virtual INT				Update_GameObj(const float& fTimeDelta);
	virtual void			Render_GameObj(HDC hdc);

protected:
	void							Update_Rect();

public:
	INFO						m_tInfo;
	RECT						m_tRect;

protected:
	CKeyManager* m_pKeyMgr;
	CTimeManager* m_pTimeMgr;
	CSoundManager* m_pSoundMgr;
	CResourceManager* m_pResourceMgr;

protected:
	virtual void			Free();
};
