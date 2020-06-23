#include "stdafx.h"
#include "CScene_Stage2.h"

#include "CPlayer.h"
#include "CPortal.h"

CScene_Stage2::CScene_Stage2()
{
}

CScene_Stage2::~CScene_Stage2()
{
	Free();
}

HRESULT CScene_Stage2::Ready_Scene()
{
	CScene::Ready_Scene();
	CGameObj* pObj = nullptr;
	CGameObj* pObj1 = nullptr;

	pObj = CPlayer::Create(100.f, 2000.f, 4000.f);
	m_pGameMgr->Add_GameObject(PLAYER, pObj);

	pObj = CPortal::Create(10994.4f, 1761.72f);
	m_pGameMgr->Add_GameObject(MAP, pObj);

	m_pSoundMgr->Stop_Sound(CSoundManager::BGM);
	m_pSoundMgr->Play_BGM(L"MapleStoryOST ARCANA.mp3"); // 브금 시작

	m_pSoundMgr->Play_BGM(L"");
	m_pMap = m_pMapMgr->Find_Map(L"Map_Stage2");
	if (m_pMap == nullptr)
	return E_FAIL;

	if (FAILED(m_pGameMgr->Set_CurrMap(m_pMap)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CScene_Stage2::Update_Scene(const float& fTimeDelta)
{
	m_pMap->Update_GameObj(fTimeDelta);

	return CScene::Update_Scene(fTimeDelta);
}

HRESULT CScene_Stage2::Render_Scene(HDC hDC)
{
	m_pMap->Render_GameObj(hDC);

	return CScene::Render_Scene(hDC);
}

CScene_Stage2* CScene_Stage2::Create()
{
	CScene_Stage2* pInstance = new CScene_Stage2();

	if (FAILED(pInstance->Ready_Scene()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CScene_Stage2::Free()
{
	m_pImage.Destroy();
	m_pGameMgr->Reset_OBJLIST();
}
