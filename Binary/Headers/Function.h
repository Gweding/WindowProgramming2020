#pragma once

#ifndef __FUNCTION_H__
#define __FUNCTION_H__

template <typename T>
void SafeDelete(T& ptr)
{
	if (ptr != nullptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

template <typename T>
void SafeDelete_Array(T& ptr)
{
	if (ptr)
	{
		delete[] ptr;
		ptr = nullptr;
	}
}

template<typename T>
bool CompareZ(T src, T dst)
{
	return src->vPos.z < dst->vPos.z;
}

template<typename T>
bool ComparebyZ(T src, T dst)
{
	return src->GetZ() < dst->GetZ();
}

template<typename T>
bool SortByIndex(T src, T dst)
{
	return src->iIndex < dst->iIndex;
}

template<typename T>
bool SortByItemIndex(T src, T dst)
{
	return src->iIndex < dst->iIndex;
}


#endif