#pragma once

class CSingleBitmap
{
public:
	CSingleBitmap();
	~CSingleBitmap();

public:
	HDC Get_MemDC() { return m_hMemDC; }
	HRESULT LoadBmp(wstring strFilePath);
	void Release();

public:
	static CSingleBitmap* Create(wstring strFilePath);

private:
	HDC m_hMemDC;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
};

