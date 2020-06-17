#pragma once

class CMainApp
{
public:
	CMainApp() = default;
	~CMainApp();

public:
	HRESULT	Ready_MainApp();
	void	Update_MainApp(const float& fTimeDelta);
	void	Render_MainApp();

private:
	void RenderStart();
	void RenderEnd();

private:
	HDC				m_hDC;

private:
	HDC				m_hMemDC;
	HDC				m_hBackDC;

private:
	CKeyManager* m_pKeyMgr = nullptr;
	CSceneManager* m_pSceneMgr = nullptr;
	CResourceManager* m_pResourceMgr = nullptr;

public:
	static CMainApp*	Create();

private:
	void				Free();
};

