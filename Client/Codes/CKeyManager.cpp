#include "stdafx.h"
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

	for (int i = 0; i < MAX_VKEY; ++i)
	{
		if (m_dwCurKey && !(GetAsyncKeyState(i) & 0x8000))
			m_dwCurKey = !m_dwCurKey;
		if (!m_dwCurKey && (GetAsyncKeyState(i) & 0x8000))
			m_dwCurKey = !m_dwCurKey;
	}

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
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_dwCurKey |= KEY_ENTER;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_dwCurKey |= KEY_SPACE;
	if (GetAsyncKeyState(VK_TAB) & 0x8000)
		m_dwCurKey |= KEY_TAB;

	if(GetAsyncKeyState(VK_F1) & 0x8000)
		m_dwCurKey |= KEY_COLLIDER;
	if (GetAsyncKeyState(VK_F2) & 0x8000)
		m_dwCurKey |= KEY_PLAYERCOLLIDER;

	if (GetAsyncKeyState('Z') & 0x8000)
		m_dwCurKey |= KEY_PLAYERDASH;

	if (GetAsyncKeyState('D') & 0x8000)
		m_dwCurKey |= KEY_PLAYERSKILL1;
	if (GetAsyncKeyState('S') & 0x8000)
		m_dwCurKey |= KEY_PLAYERSKILL2;

	if (GetAsyncKeyState('X') & 0x8000)
		m_dwCurKey |= KEY_PLAYERATTACK;
	if (GetAsyncKeyState('C') & 0x8000)
		m_dwCurKey |= KEY_PLAYERJUMP;

	if (GetAsyncKeyState('F') & 0x8000)
		m_dwCurKey |= KEY_INTERACT;
	if (GetAsyncKeyState('R') & 0x8000)
		m_dwCurKey |= KEY_RESTART;
	if (GetAsyncKeyState(VK_F3) & 0x8000)
		m_dwCurKey |= KEY_NEXTSTAGE;
}


bool CKeyManager::KeyDown(DWORD dwCurKey)
{
	// ���� ������ ���� ���� ������ �� true
	if (!(m_dwKeyDown & dwCurKey) && (m_dwCurKey & dwCurKey))
	{
		m_dwKeyDown |= dwCurKey;
		return true;
	}

	// m_dwKeyDown�� ����
	// ���� ������ �ְ� ���� ������ �ʾ��� ��
	else if ((m_dwKeyDown & dwCurKey) && !(m_dwCurKey & dwCurKey))
	{
		m_dwKeyDown ^= dwCurKey;
		return false;
	}

	return false;
}

bool CKeyManager::KeyUp(DWORD dwCurKey)
{
	// ���� ������ �ְ� ���� ������ �ʾ��� �� true
	if ((m_dwKeyUp & dwCurKey) && !(m_dwCurKey & dwCurKey))
	{
		// m_dwKeyUp�� ����
		m_dwKeyUp ^= dwCurKey;
		return true;
	}

	// ���� ������ ���� ���� ������ �� 
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
