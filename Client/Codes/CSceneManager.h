#pragma once

class CScene;
class CSceneManager
{
	DECLARE_SINGLETON(CSceneManager)

public:
	enum SCENE_ID { SCENE_LOGO, SCENE_LOADING
									, SCENE_TUTORIAL, SCENE_STAGE0, SCENE_STAGE1
									, SCENE_CLEAR, SCENE_GAMEOVER0, SCENE_GAMEOVER1
									, SCENE_TESTSTAGE, SCENE_END };

public:
	BOOL& Get_ChangeScene() { return m_bChangeScene; }
	SCENE_ID& Get_NextScene() { return m_eNextScene; }

private:
	explicit CSceneManager();
	~CSceneManager();

public:
	HRESULT	Update_Scene(const float& fTimeDelta);
	HRESULT	Render_Scene(HDC hdc);

public:
	HRESULT	Change_Scene(SCENE_ID eID);
	HRESULT	Change_NextScene();

private:
	CScene* m_pScene = nullptr;
	SCENE_ID m_eCurScene;
	SCENE_ID m_eNextScene;

private:
	BOOL m_bChangeScene = FALSE;

private:
	void Free();
};

