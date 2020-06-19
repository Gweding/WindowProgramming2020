#include "stdafx.h"
#include "CAnimationManager.h"

#include "CAnimation.h"

IMPLEMENT_SINGLETON(CAnimationManager)

CAnimationManager::CAnimationManager()
{
}

CAnimationManager::~CAnimationManager()
{
	Free();
}

HRESULT CAnimationManager::Load_Animation(wstring strTag, wstring strPath)
{
	std::locale::global(std::locale("Korean"));
#ifdef _UNICODE
	wifstream fin;
#else
	wifstream fin;
#endif // _UNICODE

	fin.open(strPath);

	if (fin.fail())
		return E_FAIL;

	CAnimation* pAnimation = CAnimation::Create();
	if (pAnimation == nullptr)
		return E_FAIL;
	
	RECT tCollRect = {};

	while (true)
	{
		FRAME* pFrame = new FRAME;

		fin >> pFrame->strTag >> pFrame->fSpeed >> pFrame->tInfo.x >> pFrame->tInfo.y >> pFrame->tInfo.cx >> pFrame->tInfo.cy
			>> tCollRect.left >> tCollRect.top >> tCollRect.right >> tCollRect.bottom >> pFrame->strPath;

		if (fin.eof())
		{
			SafeDelete(pFrame);
			break;
		}

		if (FAILED(pAnimation->Add_Frame(pFrame)))
		{
			SafeDelete(pAnimation);
			return E_FAIL;
		}
	}

	fin.close();

	pAnimation->Add_CollRect(tCollRect);

	m_mapAnimation.emplace(strTag, pAnimation);

	return NOERROR;
}

CAnimation* CAnimationManager::Find_Animation(wstring strTag)
{
	auto iter = m_mapAnimation.find(strTag);

	if (iter == m_mapAnimation.end())
		return nullptr;

	return iter->second;
}

HRESULT CAnimationManager::Load_AnimationPath(wstring strPath)
{
	std::locale::global(std::locale("Korean"));
#ifdef _UNICODE
	wifstream fin;
#else
	wifstream fin;
#endif // _UNICODE

	fin.open(strPath);

	if (fin.fail())
		return E_FAIL;

	wstring strAniTag = L"";
	wstring strAniPath = L"";

	while (true)
	{
		fin >> strAniTag >> strAniPath;

		if (fin.eof())
			break;

		if (FAILED(Load_Animation(strAniTag, strAniPath)))
			return E_FAIL;
	}

	fin.close();

	return NOERROR;
}

void CAnimationManager::Free()
{
	for (auto& iter : m_mapAnimation)
		SafeDelete(iter.second);
	m_mapAnimation.clear();
}
