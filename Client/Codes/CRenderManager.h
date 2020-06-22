#pragma once

class CRenderManager
{
	DECLARE_SINGLETON(CRenderManager)

private:
	explicit CRenderManager();
	~CRenderManager();

public:
	// �������� ����
	HRESULT	RenderObject(HDC hdc);

public:
	HRESULT	Clear_RenderList();
	HRESULT	AddBack_RenderList(CGameObj* pGameObj);
	HRESULT	AddFront_RenderList(CGameObj* pGameObj);

private:
	OBJLIST		m_RenderLst;
};

