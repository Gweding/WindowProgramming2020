#include "stdafx.h"
#include "CScene_TestStage.h"

#include "CPlayer.h"

CScene_TestStage::CScene_TestStage()
{
}

CScene_TestStage::~CScene_TestStage()
{
	Free();
}

HRESULT CScene_TestStage::Ready_Scene()
{
	CScene::Ready_Scene();
	CGameObj* pObj = nullptr;
	CGameObj* pObj1 = nullptr;

	pObj = CPlayer::Create(100.f, 300.f, 1000.f);
	m_pGameMgr->Add_GameObject(PLAYER, pObj);
	
	m_pMap = m_pMapMgr->Find_Map(L"Map_Tutorial");
	//m_pMap = m_pMapMgr->Find_Map(L"Map_Stage0");
	if (m_pMap == nullptr)
	return E_FAIL;

	if (FAILED(m_pGameMgr->Set_CurrMap(m_pMap)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CScene_TestStage::Update_Scene(const float& fTimeDelta)
{
	m_pMap->Update_GameObj(fTimeDelta);

	return CScene::Update_Scene(fTimeDelta);
}

HRESULT CScene_TestStage::Render_Scene(HDC hDC)
{
	m_pMap->Render_GameObj(hDC);

	return CScene::Render_Scene(hDC);
}

CScene_TestStage* CScene_TestStage::Create()
{
	CScene_TestStage* pInstance = new CScene_TestStage();

	if (FAILED(pInstance->Ready_Scene()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CScene_TestStage::Free()
{
	m_pImage.Destroy();
	m_pGameMgr->Reset_OBJLIST();
}
