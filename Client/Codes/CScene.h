#pragma once

class CGameManager;
class CSceneManager;
class CRenderManager;
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
	CKeyManager* m_pKeyMgr = nullptr;
	CGameManager* m_pGameMgr = nullptr;
	CSceneManager* m_pSceneMgr = nullptr;
	CRenderManager* m_pRenderMgr = nullptr;
	CResourceManager* m_pResourceMgr = nullptr;

protected:
	virtual void	Free();
};

