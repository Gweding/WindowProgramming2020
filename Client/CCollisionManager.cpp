#include "stdafx.h"
#include "CCollisionManager.h"

bool CCollisionManager::Check_IntersectRect(CGameObj* pDst, CGameObj* pSrc)
{
	RECT rc = {};
	// IntersectRect: 사각형 충돌을 판별하는 함수. 두 사각형이 충돌 됬을 때 TRUE 반환.
	// IntersectRect(겹친 영역을 기록할 사각형, 충돌 사각형1, 충돌 사각형2);

	const RECT& dstRect = pDst->Get_Rect();
	const RECT& srcRect = pSrc->Get_Rect();

	if (IntersectRect(&rc, &dstRect, &srcRect))
		return true;
	

	return false;
}

bool CCollisionManager::Check_Rect(CGameObj* pDst, CGameObj* pSrc, float* pMoveX, float* pMoveY)
{
	// 두 사각형의 가로, 세로 축 반지름의 합을 구한다.
	float fSumRadX = (pDst->Get_Info().cx + pSrc->Get_Info().cx) * 0.5f;
	float fSumRadY = (pDst->Get_Info().cy + pSrc->Get_Info().cy) * 0.5f;

	// 두 사각형의 가로, 세로 중점의 거리를 구한다.
	// fabs(X): X의 절대 값을 구하는 함수. <cmath>에서 제공. 
	float fDistX = fabs(pDst->Get_Info().x - pSrc->Get_Info().x);
	float fDistY = fabs(pDst->Get_Info().y - pSrc->Get_Info().y);

	// 가로 축 반지름 합이 가로 축 거리보다 클 때와
	// 세로 축 반지름 합이 세로 축 거리보다 클 때
	if (fSumRadX > fDistX && fSumRadY > fDistY)
	{
		// 두 사각형이 겹쳤을 때 파고든 길이도 구한다.
		*pMoveX = fSumRadX - fDistX;
		*pMoveY = fSumRadY - fDistY;

		return true;
	}

	return false;
}

bool CCollisionManager::Check_Sphere(CGameObj* pDst, CGameObj* pSrc)
{
	// 원충돌

	// 두 원의 반지름 합을 구한다.
	float fSumRad = (pDst->Get_Info().cx + pSrc->Get_Info().cx) * 0.5f;

	// 두 원의 거리를 구한다. 피타고라스를 이용.
	float w = pDst->Get_Info().x - pSrc->Get_Info().x;
	float h = pDst->Get_Info().y - pSrc->Get_Info().y;

	// sqrtf(X): X에 대한 제곱근을 구해주는 함수.
	float fDist = sqrtf(w * w + h * h);

	return (fSumRad >= fDist);
}
