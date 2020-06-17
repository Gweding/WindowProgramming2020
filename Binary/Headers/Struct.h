#pragma once

typedef struct tColorRGB
{
	tColorRGB(int iR = 0, int iG = 0, int iB = 0)
		: r(iR), g(iG), b(iB)
	{}

public:
	int r = 0;
	int g = 0;
	int b = 0;
}COLOR;

typedef struct tagInfo
{
	tagInfo()
	{}

	tagInfo(float X, float Y, float CX = 0, float CY = 0)
		: x(X), y(Y), cx(CX), cy(CY)
	{}

	// 중심
	float x;
	float y;
	// 크기
	float cx;
	float cy;
}INFO;

//typedef struct tagFrame
//{
//	tagFrame() {}
//	tagFrame(float _fCurFrame, float _fFrameCnt, float _fSpeed)
//		: fCurFrame(_fCurFrame), fFrameCnt(_fFrameCnt), fFrameSpeed(_fSpeed)
//	{}
//
//	float fCurFrame;
//	float fFrameCnt;
//	float fFrameSpeed;
//}FRAME;

typedef struct tagImage
{
	wstring strImageTag;
	wstring strRelativePath;
}IMAGE;

enum COLL_TYPE { COLL_ALL, COLL_JUMP, COLL_INTERACT, COLL_END };
typedef struct tagCollRect
{
	COLL_TYPE iType;
	RECT tRect;
}COLL_RECT;

typedef struct tagFrame
{
	tagFrame() {}
	tagFrame(wstring Tag, float Speed, float fX, float fY, float fCX, float fCY)
		: strTag(Tag), fSpeed(Speed), x(fX), y(fY), cx(fCX), cy(fCY)
	{}

	float x;
	float y;
	float cx;
	float cy;
	RECT tRect;
	float fSpeed;
	wstring strTag;
	wstring strPath;
	RECT tCollRect;
}FRAME;

typedef struct tagTile
{
	tagTile() {}
	tagTile(wstring tag, RECT rect)
		: strTag(tag), tRect(rect)
	{}

	// 중심
	float x;
	float y;
	// 크기
	float cx;
	float cy;
	// 타일 정보
	RECT tRect;
	wstring strTag;
	wstring strPath;
}TILE;
