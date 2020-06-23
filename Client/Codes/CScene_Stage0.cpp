#include "stdafx.h"
#include "CScene_Stage0.h"

#include "CPlayer.h"
#include "CPortal.h"

CScene_Stage0::CScene_Stage0()
{
}

CScene_Stage0::~CScene_Stage0()
{
	Free();
}

HRESULT CScene_Stage0::Ready_Scene()
{
	CScene::Ready_Scene();
	CGameObj* pObj = nullptr;
	CGameObj* pObj1 = nullptr;

	pObj = CPlayer::Create(100.f, 100.f, 2000.f);
	m_pGameMgr->Add_GameObject(PLAYER, pObj);

	pObj = CPortal::Create(7326.99f, 995.142f);
	m_pGameMgr->Add_GameObject(MAP, pObj);

	m_pMap = m_pMapMgr->Find_Map(L"Map_Stage0");
	//m_pMap = m_pMapMgr->Find_Map(L"Map_Stage0");
	if (m_pMap == nullptr)
	return E_FAIL;

	if (FAILED(m_pGameMgr->Set_CurrMap(m_pMap)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CScene_Stage0::Update_Scene(const float& fTimeDelta)
{
	m_pMap->Update_GameObj(fTimeDelta);

	return CScene::Update_Scene(fTimeDelta);
}

HRESULT CScene_Stage0::Render_Scene(HDC hDC)
{
	if (m_pKeyMgr->KeyDown(KEY_NEXTSTAGE))
	{
		m_pSceneMgr->Change_Scene(CSceneManager::SCENE_STAGE1);
		return NOERROR;
	}

	m_pMap->Render_GameObj(hDC);

	return CScene::Render_Scene(hDC);
}

CScene_Stage0* CScene_Stage0::Create()
{
	CScene_Stage0* pInstance = new CScene_Stage0();

	if (FAILED(pInstance->Ready_Scene()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CScene_Stage0::Free()
{
	m_pImage.Destroy();
	m_pGameMgr->Reset_OBJLIST();
}
