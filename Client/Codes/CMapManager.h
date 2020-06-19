#pragma once

class CMap;
class CMapManager
{
	DECLARE_SINGLETON(CMapManager)

private:
	explicit CMapManager();
	~CMapManager();

public:
	HRESULT		Load_Map(wstring strTag, wstring strPath);
	CMap*			Find_Map(wstring strTag);

public:
	HRESULT		Load_MapPath(wstring strPath);

private:
	map<wstring, CMap*> m_mapGameMap;

private:
	void Free();
};

