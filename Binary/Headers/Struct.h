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

typedef struct tagFrame
{
	tagFrame() {}
	tagFrame(float _fCurFrame, float _fFrameCnt, float _fSpeed)
		: fCurFrame(_fCurFrame), fFrameCnt(_fFrameCnt), fFrameSpeed(_fSpeed)
	{}

	float fCurFrame;
	float fFrameCnt;
	float fFrameSpeed;
}FRAME;

