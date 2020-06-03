#pragma once

class CSingleBitmap;
class CResourceManager
{
	DECLARE_SINGLETON(CResourceManager)

private:
	explicit CResourceManager();
	~CResourceManager();

public:
	HRESULT Ready_ResourceManager();

public:
	HDC Find_Bmp(wstring strImgKey);
	Image* Find_Sprite(wstring strImgKey);

public:
	HRESULT Load_Bmp(wstring strFilePath, wstring strImgKey);
	HRESULT Load_Sprite(wstring strFilePath, wstring strImgKey);

public:
	BOOL Check_Bmp(wstring strImgKey);
	BOOL Check_Sprite(wstring strImgKey);

private:
	// For Gdi+
	ULONG_PTR m_pGdiPlusTokenData;

private:
	// For Bitmap
	map<wstring, CSingleBitmap*> m_mapBmp;
	map<wstring, Image*> m_mapSprite;

private:
	void Free();
};

