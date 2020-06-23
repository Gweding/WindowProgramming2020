#include "stdafx.h"
#include "CScene_Stage1.h"

#include "CPlayer.h"
#include "CPortal.h"

CScene_Stage1::CScene_Stage1()
{
}

CScene_Stage1::~CScene_Stage1()
{
	Free();
}

HRESULT CScene_Stage1::Ready_Scene()
{
	CScene::Ready_Scene();
	CGameObj* pObj = nullptr;
	CGameObj* pObj1 = nullptr;

	pObj = CPlayer::Create(50.f, 5500.f, 8000.f);
	m_pGameMgr->Add_GameObject(PLAYER, pObj);

	pObj = CPortal::Create(1574.08f, 805.649f);
	m_pGameMgr->Add_GameObject(MAP, pObj);

	m_pMap = m_pMapMgr->Find_Map(L"Map_Stage1");
	if (m_pMap == nullptr)
	return E_FAIL;

	if (FAILED(m_pGameMgr->Set_CurrMap(m_pMap)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CScene_Stage1::Update_Scene(const float& fTimeDelta)
{
	m_pMap->Update_GameObj(fTimeDelta);

	return CScene::Update_Scene(fTimeDelta);
}

HRESULT CScene_Stage1::Render_Scene(HDC hDC)
{
	if (m_pKeyMgr->KeyDown(KEY_NEXTSTAGE))
	{
		m_pSceneMgr->Change_Scene(CSceneManager::SCENE_STAGE2);
		return NOERROR;
	}

	m_pMap->Render_GameObj(hDC);

	return CScene::Render_Scene(hDC);
}

CScene_Stage1* CScene_Stage1::Create()
{
	CScene_Stage1* pInstance = new CScene_Stage1();

	if (FAILED(pInstance->Ready_Scene()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CScene_Stage1::Free()
{
	m_pImage.Destroy();
	m_pGameMgr->Reset_OBJLIST();
}
