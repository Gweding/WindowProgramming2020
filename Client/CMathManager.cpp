
#include "stdafx.h"
#include "CMathManager.h"

float CMathManager::Calc_Distance(CGameObj* pDst, CGameObj* pSrc)
{
	float w = pDst->Get_Info().x - pSrc->Get_Info().x;
	float h = pDst->Get_Info().y - pSrc->Get_Info().y;

	return sqrtf(w * w + h * h);
}

float CMathManager::Calc_Radian(CGameObj* pDst, CGameObj* pSrc)
{
	float w = pDst->Get_Info().x - pSrc->Get_Info().x;
	float h = pDst->Get_Info().y - pSrc->Get_Info().y;
	float d = sqrtf(w * w + h * h);

	float fAngle = acosf(w / d);

	if (pSrc->Get_Info().y < pDst->Get_Info().y)
		fAngle *= -1.f;

	return fAngle;
}

float CMathManager::Calc_Degree(CGameObj* pDst, CGameObj* pSrc)
{
	float w = pDst->Get_Info().x - pSrc->Get_Info().x;
	float h = pDst->Get_Info().y - pSrc->Get_Info().y;
	float d = sqrtf(w * w + h * h);

	float fAngle = acosf(w / d);

	if (pSrc->Get_Info().y < pDst->Get_Info().y)
		fAngle *= -1.f;

	return fAngle * 180.f / PI;
}
