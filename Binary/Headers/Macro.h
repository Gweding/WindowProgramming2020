#pragma once

class	CGameObj;
typedef list<CGameObj*>			OBJLIST;
typedef OBJLIST::iterator			OBJITER;

class CAnimation;
typedef list<CAnimation*>		ANILIST;
typedef OBJLIST::iterator			ANIITER;

class CScene;
typedef list<CScene*>				SCENELIST;
typedef SCENELIST::iterator	SCENEITER;

class CMapLayer;
typedef list<CMapLayer*>		LAYERLIST;
typedef LAYERLIST::iterator		LAYERITER;

#define NO_COPY(ClassName)						\
private:										\
	ClassName(const ClassName& Obj);			\
	ClassName& operator=(const ClassName& Obj);

#define DECLARE_SINGLETON(ClassName)		\
		NO_COPY(ClassName)					\
public:										\
	static ClassName* GetInstance()			\
	{										\
		if(nullptr == m_pInstance)			\
		{									\
			m_pInstance = new ClassName;	\
		}									\
		return m_pInstance;					\
	}										\
	void DestroyInstance()					\
	{										\
		if(m_pInstance)						\
		{									\
			delete m_pInstance;				\
			m_pInstance = nullptr;			\
		}									\
	}										\
private:									\
	static ClassName*	m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)		\
ClassName* ClassName::m_pInstance = nullptr;


#define NULL_CHECK(ptr) if(nullptr == (ptr)) return;
#define NULL_CHECK_RETURN(ptr, val) if(nullptr == (ptr)) return val;
#define NULL_CHECK_MSG(ptr, msg) if(nullptr == (ptr)) { MSG_BOX(msg); return; }
#define NULL_CHECK_MSG_RETURN(ptr, msg, val) if(nullptr == (ptr)) { MSG_BOX(msg); return val; }

#define FAILED_CHECK(hr) if(FAILED(hr)) return;
#define FAILED_CHECK_RETURN(hr, val) if(FAILED(hr)) return val;
#define FAILED_CHECK_MSG(hr, msg) if(FAILED(hr)) { MSG_BOX(msg); return; }
#define FAILED_CHECK_MSG_RETURN(hr, msg, val) if(FAILED(hr)) { MSG_BOX(msg); return val; }
