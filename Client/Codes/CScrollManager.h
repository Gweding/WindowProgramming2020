#pragma once

class CScrollManager
{
public:
	CScrollManager();
	~CScrollManager();

public:
	static float GetScrollPos(int iAxis);
	static void SetScrollPos(float iX, float iY);

private:
	static float m_fScroll[2];
};

