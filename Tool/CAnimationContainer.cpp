#include "pch.h"
#include "CAnimationContainer.h"

CAnimationContainer::CAnimationContainer()
{
}

CAnimationContainer::~CAnimationContainer()
{
}

INT CAnimationContainer::Update_AnimationContainer(const float& fTimeDelta)
{
	for (auto iter : m_AnimationMap)
	{
		for (auto iter2 : iter.second)
		{
			iter2->Update_GameObj(fTimeDelta);
		}
	}

	return 0;
}

void CAnimationContainer::Render_AnimationContainer(HDC hdc)
{
	for (auto& Mapiter : m_AnimationMap)
	{
		for (auto& ListIter : Mapiter.second)
		{
			ListIter->Render_GameObj(hdc);
		}
	}
}

HRESULT CAnimationContainer::Add_Animation(wstring strTag, CAnimation* pAnimation)
{
	if (pAnimation == nullptr)
		return E_FAIL;

	auto iter = m_AnimationMap.find(strTag);

	if (iter == m_AnimationMap.end())
	{
		// �߰��� �±װ� ã�Ƶ� ���ٸ� ���ο� �±� �߰�
		m_AnimationMap[strTag] = ANILIST();
	}

	m_AnimationMap[strTag].emplace_back(pAnimation);

	return NOERROR;
}
