#pragma once

#include "CGameObj.h"

class CMathManager
{
public:
	CMathManager() = default;
	~CMathManager() = default;

public:
	static float Calc_Distance(CGameObj* pDst, CGameObj* pSrc);
	static float Calc_Radian(CGameObj* pDst, CGameObj* pSrc);
	static float Calc_Degree(CGameObj* pDst, CGameObj* pSrc);
};

