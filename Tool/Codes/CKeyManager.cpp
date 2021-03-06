#include "pch.h"
#include "CKeyManager.h"

IMPLEMENT_SINGLETON(CKeyManager)

CKeyManager::CKeyManager()
	: m_dwCurKey(0), m_dwKeyUp(0), m_dwKeyDown(0)
{

}

CKeyManager::~CKeyManager()
{

}


void CKeyManager::UpdateKey()
{
	m_dwCurKey = 0;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_dwCurKey |= KEY_LBUTTON;
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		m_dwCurKey |= KEY_RBUTTON;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_dwCurKey |= KEY_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_dwCurKey |= KEY_DOWN;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_dwCurKey |= KEY_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_dwCurKey |= KEY_RIGHT;

	if (GetAsyncKeyState('Q') & 0x8000)
		m_dwCurKey |= KEY_Q;
	if (GetAsyncKeyState('W') & 0x8000)
		m_dwCurKey |= KEY_W;
	if (GetAsyncKeyState('E') & 0x8000)
		m_dwCurKey |= KEY_E;
	if (GetAsyncKeyState('R') & 0x8000)
		m_dwCurKey |= KEY_R;

	if (GetAsyncKeyState('A') & 0x8000)
		m_dwCurKey |= KEY_A;
	if (GetAsyncKeyState('S') & 0x8000)
		m_dwCurKey |= KEY_S;
	if (GetAsyncKeyState('D') & 0x8000)
		m_dwCurKey |= KEY_D;

}


bool CKeyManager::KeyDown(DWORD dwCurKey)
{
	// 전에 누른적 없고 현재 눌렸을 때 true
	if (!(m_dwKeyDown & dwCurKey) && (m_dwCurKey & dwCurKey))
	{
		m_dwKeyDown |= dwCurKey;
		return true;
	}

	// m_dwKeyDown을 원복
	// 전에 누른적 있고 현재 누르지 않았을 때
	else if ((m_dwKeyDown & dwCurKey) && !(m_dwCurKey & dwCurKey))
	{
		m_dwKeyDown ^= dwCurKey;
		return false;
	}

	return false;
}

bool CKeyManager::KeyUp(DWORD dwCurKey)
{
	// 전에 누른적 있고 현재 누르지 않았을 때 true
	if ((m_dwKeyUp & dwCurKey) && !(m_dwCurKey & dwCurKey))
	{
		// m_dwKeyUp을 원복
		m_dwKeyUp ^= dwCurKey;
		return true;
	}

	// 전에 누른적 없고 현재 눌렸을 때 
	else if (!(m_dwKeyUp & dwCurKey) && (m_dwCurKey & dwCurKey))
	{
		m_dwKeyUp |= dwCurKey;
		return false;
	}

	return false;
}

bool CKeyManager::KeyPressing(DWORD dwCurKey)
{
	if (m_dwCurKey & dwCurKey)
		return true;

	return false;
}

// ex) Ctrl + V
bool CKeyManager::KeyCombined(DWORD dwFistKey, DWORD dwSecondKey)
{
	if (KeyDown(dwSecondKey) && KeyPressing(dwFistKey))
		return true;

	return false;
}
