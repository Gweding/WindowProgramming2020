#include "stdafx.h"
#include "CAnimation.h"

CAnimation::CAnimation()
{
}

CAnimation::~CAnimation()
{
	Free();
}

RECT CAnimation::Get_CollRect()
{
	// TODO: 여기에 return 문을 삽입합니다.
	RECT tRect = {};
	tRect.left = m_tCollRect.left * 2 + (int)m_tInfo.x;
	tRect.top = m_tCollRect.top * 2 + (int)m_tInfo.y;
	tRect.right = m_tCollRect.right * 2 + (int)m_tInfo.x;
	tRect.bottom = m_tCollRect.bottom * 2 + (int)m_tInfo.y;

	return tRect;
}

int CAnimation::Get_CollSize(int iAxis)
{
	if (iAxis == 0)
		return (m_tCollRect.right - m_tCollRect.left);

	if (iAxis == 1)
		return (m_tCollRect.bottom - m_tCollRect.top);

	return 0;
}

HRESULT CAnimation::Ready_GameObj()	        
{
	CGameObj::Ready_GameObj();

	m_tColor = {};

	return NOERROR;
}

int CAnimation::Update_GameObj(const float& fTimeDelta)
{
	m_tColor = {};

	m_fCurrFrame += m_vecFrame[(int)m_fCurrFrame]->fSpeed * fTimeDelta;
	if (m_fCurrFrame >= m_vecFrame.size())
	{
		m_fCurrFrame = 0.f;
		m_bAnimationEnd = TRUE;
	}
	else
		m_bAnimationEnd = FALSE;

	CGameObj::Update_Rect();

	if (m_pKeyMgr->KeyDown(KEY_PLAYERCOLLIDER))
		m_bRenderCollider = !m_bRenderCollider;

	return 0;
}

void CAnimation::Render_GameObj(HDC hDC)
{
	CImage* pImage = m_pResourceMgr->Find_Sprite(m_vecFrame[(int)m_fCurrFrame]->strTag);
	if (pImage != nullptr)
		pImage->Draw(hDC, m_tRect.left - (int)CScrollManager::GetScrollPos(0), m_tRect.top - (int)CScrollManager::GetScrollPos(1), (int)m_tInfo.cx, (int)m_tInfo.cy);

	if (m_bRenderCollider)
	{
		m_hPen = CreatePen(PS_SOLID, 1, RGB(m_tColor.r, m_tColor.g, m_tColor.b));
		m_hOldPen = SelectObject(hDC, m_hPen);
		m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		m_hOldBrush = SelectObject(hDC, m_hBrush);
		Rectangle(hDC, m_tCollRect.left * 2 + (int)m_tInfo.x - (int)CScrollManager::GetScrollPos(0)
			, m_tCollRect.top * 2 + (int)m_tInfo.y - (int)CScrollManager::GetScrollPos(1)
			, m_tCollRect.right * 2 + (int)m_tInfo.x - (int)CScrollManager::GetScrollPos(0)
			, m_tCollRect.bottom * 2 + (int)m_tInfo.y - (int)CScrollManager::GetScrollPos(1));
		SelectObject(hDC, m_hOldPen);
		SelectObject(hDC, m_hOldBrush);
		DeleteObject(m_hBrush);
		DeleteObject(m_hPen);
	}
}

HRESULT CAnimation::Add_Frame(FRAME* pFrame)
{
	if (pFrame == nullptr)
		return E_FAIL;

	if (m_pResourceMgr->Check_Sprite(pFrame->strTag))
	{
		if (FAILED(m_pResourceMgr->Load_Sprite(pFrame->strTag, pFrame->strPath)))
			return E_FAIL;
	}

	CImage* pImage = m_pResourceMgr->Find_Sprite(pFrame->strTag);
	m_tInfo.cx = pImage->GetWidth() * 2.f;
	m_tInfo.cy = pImage->GetHeight() * 2.f;

	m_vecFrame.push_back(pFrame);

	return NOERROR;
}

HRESULT CAnimation::Add_CollRect(RECT tRect)
{
	CImage* pImage = m_pResourceMgr->Find_Sprite(m_vecFrame[0]->strTag);
	m_iSize = (int)m_vecFrame[0]->tInfo.cx / pImage->GetWidth();

	m_tCollRect.left = tRect.left / m_iSize;
	m_tCollRect.right = tRect.right / m_iSize;
	m_tCollRect.top = tRect.top / m_iSize;
	m_tCollRect.bottom = tRect.bottom / m_iSize;

	return NOERROR;
}

void CAnimation::Update_Position(float fX, float fY)
{
	m_tInfo.x = fX;
	m_tInfo.y = fY;
	CGameObj::Update_Rect();
}

CAnimation* CAnimation::Create()
{
	CAnimation* pInstance = new CAnimation;

	if (FAILED(pInstance->Ready_GameObj()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CAnimation::Free()
{
	for (auto& pFrame : m_vecFrame)
		SafeDelete(pFrame);
	m_vecFrame.clear();
}
