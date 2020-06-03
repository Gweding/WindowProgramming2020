#include "stdafx.h"
#include "CTest.h"

CTest::CTest()
{
}

CTest::~CTest()
{
}

HRESULT CTest::Ready_GameObj(float fX, float fY, wstring strTag)
{
	CGameObj::Ready_GameObj();
	m_pImage.Load(strTag.c_str());

	m_tInfo.x = fX;
	m_tInfo.y = fY;
	m_tInfo.cx = 100;
	m_tInfo.cy = 100;

	return NOERROR;
}

int CTest::Update_GameObj(const float& fTimeDelta)
{
	if (m_pKeyMgr->KeyPressing(KEY_UP))
		m_tInfo.y -= fTimeDelta * 100.f;

	if (m_pKeyMgr->KeyPressing(KEY_DOWN))
		m_tInfo.y += fTimeDelta * 100.f;

	if (m_pKeyMgr->KeyPressing(KEY_RIGHT))
		m_tInfo.x += fTimeDelta * 100.f;

	if (m_pKeyMgr->KeyPressing(KEY_LEFT))
		m_tInfo.x -= fTimeDelta * 100.f;

	CGameObj::Update_Rect();
	m_pRenderMgr->AddBack_RenderList(this);

	return 0;
}

void CTest::Render_GameObj(HDC hDC)
{
	m_pImage.Draw(hDC, m_tRect);
}

CTest* CTest::Create(float fX, float fY, wstring strTag)
{
	CTest* pInstance = new CTest;

	if (FAILED(pInstance->Ready_GameObj(fX, fY, strTag)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CTest::Free()
{
	m_pImage.ReleaseDC();
}
