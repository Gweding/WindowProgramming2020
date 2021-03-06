#pragma once
#include "CMap.h"

class CKeyManager;
class CMapManager;
class CGameManager;
class CSceneManager;
class CRenderManager;
class CResourseManager;
class CAnimationManager;
class CSoundManager;

class CScene
{
public:
	explicit CScene();
	virtual ~CScene();

public:
	virtual HRESULT		Ready_Scene();
	virtual HRESULT		Update_Scene(const float& fTimeDelta);
	virtual HRESULT		Render_Scene(HDC hDC);

protected:
	HFONT m_hFont;
	HFONT m_oldFont;

protected:
	CMap* m_pMap = nullptr;

protected:
	CKeyManager* m_pKeyMgr = nullptr;
	CMapManager* m_pMapMgr = nullptr;
	CGameManager* m_pGameMgr = nullptr;
	CSceneManager* m_pSceneMgr = nullptr;
	CRenderManager* m_pRenderMgr = nullptr;
	CResourceManager* m_pResourceMgr = nullptr;
	CAnimationManager* m_pAnimationMgr = nullptr;
	CSoundManager* m_pSoundMgr = nullptr;

protected:
	virtual void	Free();
};

