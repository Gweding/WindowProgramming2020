#include "pch.h"
#include "CScrollManager.h"

float CScrollManager::m_fScroll[2] = {};

CScrollManager::CScrollManager()
{
}


CScrollManager::~CScrollManager()
{
}

float CScrollManager::GetScrollPos(int iAxis)
{
	switch (iAxis)
	{
	case 0:
		return m_fScroll[0];
	case 1:
		return m_fScroll[1];
	}

	return 0;
}

void CScrollManager::SetScrollPos(float iX, float iY)
{
	m_fScroll[0] += iX;
	m_fScroll[1] += iY;
}
