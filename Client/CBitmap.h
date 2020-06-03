#pragma once
class CBitmap
{
public:
	CBitmap();
	~CBitmap();

public:
	HDC Get_MemDC() { return m_hMemDC; }
	HRESULT Load_Bitmap(wstring strFilePath);

private:
	void Free();

public:
	static CBitmap* Create(wstring strFilePath);

private:
	HDC m_hMemDC;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
};

