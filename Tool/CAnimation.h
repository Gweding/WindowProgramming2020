#pragma once
#include "CGameObj.h"

class CAnimationDialog;
class CAnimation : public CGameObj
{
public:
	explicit CAnimation();
	~CAnimation();

public:
	virtual HRESULT	Ready_GameObj();
	virtual INT				Update_GameObj(const float& fTimeDelta);
	virtual void			Render_GameObj(HDC hdc);

public:
	HRESULT				Add_Frame(wstring strTag, wstring strFilePath);
	HRESULT				Delete_Frame(int iIndex);
	HRESULT				Frame_Up(int iIndex);
	HRESULT				Frame_Down(int iIndex);
	HRESULT				Clear_Frame();
	HRESULT				Change_Frame(int iIndex, wstring strTag, wstring strFilePath);
	HRESULT				Save_Animation(wstring strPath);
	HRESULT				Load_Animation(wstring strPath);

public:
	HDC m_PicHdc;
	HWND m_PicHwnd;
	POINT m_tAddPoint[2];
	CListBox* m_FrameList;
	CListBox* m_CollList;
	bool m_bAddRect = false;
	vector<FRAME*> m_vecFrame;
	CAnimationDialog* m_pDialog = nullptr;
	HPEN			m_hPen;
	HGDIOBJ	m_hOldPen;
	HBRUSH	m_hBrush;
	HGDIOBJ	m_hOldBrush;
	RECT m_tPicRect;

public:
	bool m_bPlay = false;
	float m_fCurrFrame = 0;
	const int m_iWindowSize = 420;

public:
	static CAnimation* Create();

private:
	virtual void			Free();
};

