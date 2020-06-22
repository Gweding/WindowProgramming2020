#include "stdafx.h"
#include "CScene_TutorialStage.h"

#include "CPlayer.h"
#include "CPortal.h"

CScene_TutorialStage::CScene_TutorialStage()
{
}

CScene_TutorialStage::~CScene_TutorialStage()
{
	Free();
}

HRESULT CScene_TutorialStage::Ready_Scene()
{
	CScene::Ready_Scene();
	CGameObj* pObj = nullptr;
	CGameObj* pObj1 = nullptr;

	pObj = CPlayer::Create(100.f, 100.f);
	m_pGameMgr->Add_GameObject(PLAYER, pObj);
	
	pObj = CPortal::Create(2231.25f, 357.354f);
	m_pGameMgr->Add_GameObject(MAP, pObj);

	m_pMap = m_pMapMgr->Find_Map(L"Map_Tutorial");
	if (m_pMap == nullptr)
	return E_FAIL;

	if (FAILED(m_pGameMgr->Set_CurrMap(m_pMap)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CScene_TutorialStage::Update_Scene(const float& fTimeDelta)
{
	m_pMap->Update_GameObj(fTimeDelta);

	return CScene::Update_Scene(fTimeDelta);
}

HRESULT CScene_TutorialStage::Render_Scene(HDC hDC)
{
	m_pMap->Render_GameObj(hDC);

	return CScene::Render_Scene(hDC);
}

CScene_TutorialStage* CScene_TutorialStage::Create()
{
	CScene_TutorialStage* pInstance = new CScene_TutorialStage();

	if (FAILED(pInstance->Ready_Scene()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CScene_TutorialStage::Free()
{
	m_pImage.Destroy();
	m_pGameMgr->Reset_OBJLIST();
}
