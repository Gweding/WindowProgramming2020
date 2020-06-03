#pragma once
#include "CAnimation.h"

class CAnimationContainer
{
	// �� ��ü�� �ִϸ��̼� ������ �±׺��� ��Ƶδ� �����̳�.

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

