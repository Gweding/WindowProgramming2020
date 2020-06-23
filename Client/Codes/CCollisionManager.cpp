#include "stdafx.h"
#include "CCollisionManager.h"

bool CCollisionManager::Check_IntersectRect(CGameObj* pDst, CGameObj* pSrc)
{
	RECT rc = {};
	// IntersectRect: �簢�� �浹�� �Ǻ��ϴ� �Լ�. �� �簢���� �浹 ���� �� TRUE ��ȯ.
	// IntersectRect(��ģ ������ ����� �簢��, �浹 �簢��1, �浹 �簢��2);

	const RECT& dstRect = pDst->Get_Rect();
	const RECT& srcRect = pSrc->Get_Rect();

	if (IntersectRect(&rc, &dstRect, &srcRect))
		return true;
	

	return false;
}

bool CCollisionManager::Check_ObjRect(CGameObj* pDst, CGameObj* pSrc, float* pMoveX, float* pMoveY)
{
	// �� �簢���� ����, ���� �� �������� ���� ���Ѵ�.
	float fSumRadX = (pDst->Get_Info().cx + pSrc->Get_Info().cx) * 0.5f;
	float fSumRadY = (pDst->Get_Info().cy + pSrc->Get_Info().cy) * 0.5f;

	// �� �簢���� ����, ���� ������ �Ÿ��� ���Ѵ�.
	// fabs(X): X�� ���� ���� ���ϴ� �Լ�. <cmath>���� ����. 
	float fDistX = fabs(pDst->Get_Info().x - pSrc->Get_Info().x);
	float fDistY = fabs(pDst->Get_Info().y - pSrc->Get_Info().y);

	// ���� �� ������ ���� ���� �� �Ÿ����� Ŭ ����
	// ���� �� ������ ���� ���� �� �Ÿ����� Ŭ ��
	if (fSumRadX > fDistX && fSumRadY > fDistY)
	{
		// �� �簢���� ������ �� �İ�� ���̵� ���Ѵ�.
		*pMoveX = fSumRadX - fDistX;
		*pMoveY = fSumRadY - fDistY;

		return true;
	}

	return false;
}

bool CCollisionManager::Check_Rect(RECT tDst, RECT tSrc, float* pMoveX, float* pMoveY)
{
	INFO tDstInfo = {};
	INFO tSrcInfo = {};

	tDstInfo.cx = float(tDst.right - tDst.left);
	tDstInfo.cy = float(tDst.bottom - tDst.top);
	tDstInfo.x = (float)tDst.left + (tDstInfo.cx * 0.5f);
	tDstInfo.y = (float)tDst.top + (tDstInfo.cy * 0.5f);

	tSrcInfo.cx = float( tSrc.right - tSrc.left);
	tSrcInfo.cy = float(tSrc.bottom - tSrc.top);
	tSrcInfo.x = (float)tSrc.left + (tSrcInfo.cx * 0.5f);
	tSrcInfo.y = (float)tSrc.top + (tSrcInfo.cy * 0.5f);

	// �� �簢���� ����, ���� �� �������� ���� ���Ѵ�.
	float fSumRadX = (tDstInfo.cx + tSrcInfo.cx) * 0.5f;
	float fSumRadY = (tDstInfo.cy + tSrcInfo.cy) * 0.5f;

	// �� �簢���� ����, ���� ������ �Ÿ��� ���Ѵ�.
	// fabs(X): X�� ���� ���� ���ϴ� �Լ�. <cmath>���� ����. 
	float fDistX = fabs(tDstInfo.x - tSrcInfo.x);
	float fDistY = fabs(tDstInfo.y - tSrcInfo.y);

	// ���� �� ������ ���� ���� �� �Ÿ����� Ŭ ����
	// ���� �� ������ ���� ���� �� �Ÿ����� Ŭ ��
	if (fSumRadX > fDistX && fSumRadY > fDistY)
	{
		// �� �簢���� ������ �� �İ�� ���̵� ���Ѵ�.
		*pMoveX = fSumRadX - fDistX;
		*pMoveY = fSumRadY - fDistY;

		return true;
	}

	return false;
}

bool CCollisionManager::Check_Sphere(CGameObj* pDst, CGameObj* pSrc)
{
	// ���浹

	// �� ���� ������ ���� ���Ѵ�.
	float fSumRad = (pDst->Get_Info().cx + pSrc->Get_Info().cx) * 0.5f;

	// �� ���� �Ÿ��� ���Ѵ�. ��Ÿ��󽺸� �̿�.
	float w = pDst->Get_Info().x - pSrc->Get_Info().x;
	float h = pDst->Get_Info().y - pSrc->Get_Info().y;

	// sqrtf(X): X�� ���� �������� �����ִ� �Լ�.
	float fDist = sqrtf(w * w + h * h);

	return (fSumRad >= fDist);
}
