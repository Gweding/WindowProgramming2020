#include "stdafx.h"
#include "CTimeManager.h"

IMPLEMENT_SINGLETON(CTimeManager)

CTimeManager::CTimeManager()
	: m_fDeltaTime(0.f), m_fTimeCount(0.f)
{
	// �ϵ��� �ִ� ���ػ� Ÿ�̸� ���� ������ �Լ�.
	// Ÿ�̸� ���� Cpu�� Clock�� ������� �Ѵ�.
	// �ᱹ Ÿ�̸� ���� ���� ��������.
	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceCounter(&m_OldTime);

	// Cpu�� Clock�� �ʴ� ������(Hz)�� ������ �Լ�.
	QueryPerformanceFrequency(&m_CpuTick);

	QueryPerformanceCounter(&m_FrameCurTime);
	QueryPerformanceCounter(&m_FrameOldTime);
	QueryPerformanceFrequency(&m_FrameCpuTick);
}

CTimeManager::~CTimeManager()
{
	Free();
}

const float& CTimeManager::GetDelta() const
{
	// TODO: ���⿡ return ���� �����մϴ�.
	return m_fDeltaTime;
}

void CTimeManager::UpdateTime()
{
	QueryPerformanceCounter(&m_CurTime);

	if (m_CurTime.QuadPart - m_OldTime.QuadPart > m_CpuTick.QuadPart)
	{
		QueryPerformanceCounter(&m_CurTime);
		QueryPerformanceCounter(&m_OldTime);
		QueryPerformanceFrequency(&m_CpuTick);
	}

	m_fDeltaTime = float(m_CurTime.QuadPart - m_OldTime.QuadPart) / m_CpuTick.QuadPart;

	m_OldTime.QuadPart = m_CurTime.QuadPart;
}

bool CTimeManager::FrameLimit(float fLimit)
{
	QueryPerformanceCounter(&m_FrameCurTime);

	if (m_FrameCurTime.QuadPart - m_FrameOldTime.QuadPart > m_FrameCpuTick.QuadPart)
	{
		QueryPerformanceCounter(&m_FrameCurTime);
		QueryPerformanceCounter(&m_FrameOldTime);
		QueryPerformanceFrequency(&m_FrameCpuTick);
	}

	m_fTimeCount += float(m_FrameCurTime.QuadPart - m_FrameOldTime.QuadPart) / m_FrameCpuTick.QuadPart;
	m_FrameOldTime.QuadPart = m_FrameCurTime.QuadPart;

	if ((1.f / fLimit) <= m_fTimeCount)
	{
		m_fTimeCount = 0.f;
		return true;
	}

	return false;
}

void CTimeManager::Free()
{
}