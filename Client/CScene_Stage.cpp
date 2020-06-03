#include "stdafx.h"
#include "CScene_Stage.h"

CScene_Stage::CScene_Stage()
{
}

CScene_Stage::~CScene_Stage()
{
	Free();
}

HRESULT CScene_Stage::Ready_Scene()
{
	CScene::Ready_Scene();
	CGameObj* pObj = nullptr;

	return NOERROR;
}

HRESULT CScene_Stage::Update_Scene(const float& fTimeDelta)
{
	return CScene::Update_Scene(fTimeDelta);
}

HRESULT CScene_Stage::Render_Scene(HDC hDC)
{
	return CScene::Render_Scene(hDC);
}

CScene_Stage* CScene_Stage::Create()
{
	CScene_Stage* pInstance = new CScene_Stage();

	if (FAILED(pInstance->Ready_Scene()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CScene_Stage::Free()
{
	m_pGameMgr->Reset_OBJLIST();
}
