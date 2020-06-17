#pragma once

class CBitmap;
class CResourceManager
{
	DECLARE_SINGLETON(CResourceManager)

private:
	explicit CResourceManager();
	~CResourceManager();

public:
	HDC Find_Bmp(wstring strImgKey);
	CImage* Find_Sprite(wstring strImgKey);

public:
	HRESULT Load_Bmp(wstring strImgKey, wstring strFilePath);
	HRESULT Load_Sprite(wstring strImgKey, wstring strFilePath);

public:
	BOOL Check_Bmp(wstring strImgKey);
	BOOL Check_Sprite(wstring strImgKey);

private:
	// For Bitmap
	map<wstring, CBitmap*> m_mapBmp;
	map<wstring, CImage*> m_mapSprite;

private:
	void Free();
};

