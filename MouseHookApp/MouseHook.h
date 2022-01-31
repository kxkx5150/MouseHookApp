#pragma once
#include <Windows.h>

#ifdef MOUSEHOOK_EXPORTS
#define __DLL_PORT extern "C" __declspec(dllexport)
#else
#define __DLL_PORT extern "C" __declspec(dllimport)
#endif
#define WM_MOUSE_GLOBAL_HOOK WM_APP + 55

__DLL_PORT void __cdecl start_hook(HWND hwnd, bool lbtn, bool mbtn, bool rbtn, bool xbtn, bool wheel, bool move);
__DLL_PORT void __cdecl end_hook();
