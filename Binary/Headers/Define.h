#pragma once

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include <list>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

// CImage
#include <atlimage.h>

// FMOD (Sound Library)
#include <io.h>
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_dsp.h"
#include "fmod_errors.h"
#pragma comment (lib, "fmodex_vc.lib")
#pragma comment (lib, "fmodex64_vc.lib")

// User
#include "Enum.h"
#include "Extern.h"
#include "Struct.h"
#include "Function.h"
#include "Functor.h"
#include "Macro.h"

#define WINCX 1280
#define WINCY 720

#define TOOLCX 1780
#define TOOLCY 720

#define MIN_STR 64
#define MID_STR 128
#define MAX_STR 256

#define PI 3.141592f;
#define MAX_VKEY 0xff
// Default

#define OBJ_NOEVENT 0
#define OBJ_DEAD 1

#define TILE_SIZE 32

#ifdef TOOL
#define MSG_BOX(msg)									\
	AfxMessageBox(msg)
#else
#define MSG_BOX(msg)									\
	MessageBox(nullptr, msg, L"System Error!", MB_OK)
#endif

#ifdef CLIENT
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 
#endif  // _DEBUG  

#endif
#endif