#pragma once

const DWORD KEY_UP = 0x00000001;
const DWORD KEY_DOWN = 0x00000002;
const DWORD KEY_LEFT = 0x00000004;
const DWORD KEY_RIGHT = 0x00000008;

const DWORD KEY_LBUTTON = 0x00000010;
const DWORD KEY_RBUTTON = 0x00000020;	

const DWORD KEY_Q = 0x00000040;
const DWORD KEY_W = 0x00000080;
const DWORD KEY_E = 0x00000200;
const DWORD KEY_R = 0x00000400;

class CKeyManager
{
	DECLARE_SINGLETON(CKeyManager)

private:
	CKeyManager();
	~CKeyManager();

public:
	void UpdateKey();

public:
	bool KeyDown(DWORD dwCurKey);
	bool KeyUp(DWORD dwCurKey);
	bool KeyPressing(DWORD dwCurKey);
	bool KeyCombined(DWORD dwFistKey, DWORD dwSecondKey);

private:
	DWORD m_dwCurKey;
	DWORD m_dwKeyUp;
	DWORD m_dwKeyDown;
};

