#pragma once
#include "CAnimation.h"

class CAnimationContainer
{
	// 각 객체의 애니메이션 파일을 태그별로 담아두는 컨테이너.

public:
	explicit CAnimationContainer();
	~CAnimationContainer();

public:
	virtual INT			Update_AnimationContainer(const float& fTimeDelta);
	virtual void		Render_AnimationContainer(HDC hdc);

public:
	HRESULT			Add_Animation(wstring strTag, CAnimation* pAnimation);

private:
	map<wstring, ANILIST>		m_AnimationMap;
};

