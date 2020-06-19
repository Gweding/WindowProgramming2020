#pragma once

class CAnimation;
class CAnimationManager
{
	DECLARE_SINGLETON(CAnimationManager)

private:
	explicit CAnimationManager();
	~CAnimationManager();

public:
	HRESULT Load_Animation(wstring strTag, wstring strPath);
	CAnimation* Find_Animation(wstring strTag);

public:
	HRESULT Load_AnimationPath(wstring strPath);

private:
	map<wstring, CAnimation*> m_mapAnimation;

private:
	void Free();
};

