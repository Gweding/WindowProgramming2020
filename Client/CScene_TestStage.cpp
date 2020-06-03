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

	for (int i = 0; i < 5; ++i)
	{
		pObj = CTest::Create(10 * i, 10 * i, L"../Binary/Resources/Profile_-_Forky.png");
		m_pGameMgr->Add_GameObject(GAMEOBJ, pObj);
	}

	for (int i = 0; i < 5; ++i)
	{
		pObj = CTest::Create(50 + 10 * i, 50 + 10 * i, L"../Binary/Resources/01 #16038.png");
		m_pGameMgr->Add_GameObject(GAMEOBJ, pObj);
	}

	for (int i = 0; i < 10; ++i)
	{
		pObj = CTest::Create(200 + 10 * i, 200 + 10 * i, L"../Binary/Resources/01 #17449.png");
		m_pGameMgr->Add_GameObject(GAMEOBJ, pObj);
	}

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
