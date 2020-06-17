#include "stdafx.h"
#include "CScene_TestStage.h"

#include "CTest.h"

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

	pObj = CTest::Create(500 , 670 , L"../Binary/Resources/Player_Idle_Head00.png");
	m_pGameMgr->Add_GameObject(GAMEOBJ, pObj);

	pObj1 = CTest::Create(1000, 670, L"../Binary/Resources/Idle_0 #20945.png");
	m_pGameMgr->Add_GameObject(GAMEOBJ, pObj1);	


	m_pResourceMgr->Load_Sprite(L"../Binary/Resources/Grid.png", L"TestStage_Back");


	if (FAILED(m_pImage.Load(L"../Binary/Resources/Sprite/1 #16897.png")))
		return E_FAIL;

	return NOERROR;
}

HRESULT CScene_TestStage::Update_Scene(const float& fTimeDelta)
{
	return CScene::Update_Scene(fTimeDelta);
}

HRESULT CScene_TestStage::Render_Scene(HDC hDC)
{
	//Graphics pGraphics(hDC);
	//Image* pImage = m_pResourceMgr->Find_Sprite(L"TestStage_Back");
	//pGraphics.DrawImage(pImage, 0, 0, 1280, 720);

	m_pImage.Draw(hDC, 0, 0, WINCX, WINCY);

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
	m_pImage.ReleaseDC();
	m_pGameMgr->Reset_OBJLIST();
}
