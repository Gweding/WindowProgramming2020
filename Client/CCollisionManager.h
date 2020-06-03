#pragma once

#include "CGameObj.h"

class CCollisionManager
{
public:
	CCollisionManager() = default;
	~CCollisionManager() = default;

public:
	static bool Check_IntersectRect(CGameObj* pDst, CGameObj* pSrc);
	static bool Check_Rect(CGameObj* pDst, CGameObj* pSrc, float* pMoveX, float* pMoveY);
	static bool Check_Sphere(CGameObj* pDst, CGameObj* pSrc);
};

