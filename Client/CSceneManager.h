#pragma once

class CScene;
class CSceneManager
{
	DECLARE_SINGLETON(CSceneManager)

public:
	enum SCENE_ID { SCENE_TESTSTAGE, SCENE_END };

private:
	explicit CSceneManager();
	~CSceneManager();

public:
	HRESULT	Update_Scene(const float& fTimeDelta);
	HRESULT	Render_Scene(HDC hdc);

public:
	HRESULT	Change_Scene(SCENE_ID eID);

private:
	CScene* m_pScene = nullptr;
	SCENE_ID m_eCurScene;
	SCENE_ID m_eNextScene;

private:
	void Free();
};

