#pragma once
class CTimeManager
{
	DECLARE_SINGLETON(CTimeManager)

private:
	CTimeManager();
	~CTimeManager();

public:
	float GetTime() { return m_fTime; }

public:
	void InitTime();
	void UpdateTime();

private:
	LARGE_INTEGER	m_CurTime;
	LARGE_INTEGER	m_OldTime1;
	LARGE_INTEGER	m_OldTime2;
	LARGE_INTEGER	m_CpuTick;

	float			m_fTime;
};
