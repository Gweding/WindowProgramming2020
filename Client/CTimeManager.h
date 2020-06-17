#pragma once

class CTimeManager
{
	DECLARE_SINGLETON(CTimeManager)

public:
	explicit CTimeManager();
	~CTimeManager();

public:
	const float& GetDelta() const;

public:
	void UpdateTime();
	bool FrameLimit(float fLimit);

public:
	void Free();

private:
	// Delta Time
	LARGE_INTEGER	m_CurTime;
	LARGE_INTEGER	m_OldTime;
	LARGE_INTEGER	m_CpuTick;
	float			m_fDeltaTime;

private:
	// Frame Limit
	LARGE_INTEGER	m_FrameCurTime;
	LARGE_INTEGER	m_FrameOldTime;
	LARGE_INTEGER	m_FrameCpuTick;
	float			m_fTimeCount;
};

