#include "pch.h"
#include "MouseHook.h"

HHOOK g_hook = nullptr;
HWND g_hwnd = nullptr;

bool caplbtn = false;
bool capmbtn = false;
bool caprbtn = false;
bool capxbtn = false;
bool capwheel = false;
bool capmove = false;

LRESULT CALLBACK hook_proc(int code, WPARAM wParam, LPARAM lParam);
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
void __cdecl start_hook(HWND hwnd, bool lbtn, bool mbtn, bool rbtn, bool xbtn, bool wheel, bool move)
{
    if (!g_hook) {
        caplbtn = lbtn;
        capmbtn = mbtn;
        caprbtn = rbtn;
        capxbtn = xbtn;
        capwheel = wheel;
        capmove = move;

        g_hwnd = hwnd;
        g_hook = SetWindowsHookEx(WH_MOUSE_LL, hook_proc, nullptr, 0);
    }
}
void __cdecl end_hook()
{
    if (g_hook)
        UnhookWindowsHookEx(g_hook);
    g_hook = nullptr;
    g_hwnd = nullptr;
}
LRESULT CALLBACK hook_proc(int code, WPARAM wParam, LPARAM lParam)
{
    if (!g_hwnd || code < 0)
        return CallNextHookEx(g_hook, code, wParam, lParam);

    bool enable = false;
    if (caplbtn && (WM_LBUTTONDBLCLK == wParam || WM_NCLBUTTONDBLCLK == wParam)) {
        enable = true;
    } else if (caplbtn && (WM_LBUTTONDOWN == wParam || WM_NCLBUTTONDOWN == wParam)) {
        enable = true;
    } else if (caplbtn && (WM_LBUTTONUP == wParam || WM_NCLBUTTONUP == wParam)) {
        enable = true;


    } else if (capmbtn && (WM_MBUTTONDBLCLK == wParam || WM_NCMBUTTONDBLCLK == wParam)) {
        enable = true;
    } else if (capmbtn && (WM_MBUTTONDOWN == wParam || WM_NCMBUTTONDOWN == wParam)) {
        enable = true;
    } else if (capmbtn && (WM_MBUTTONUP == wParam || WM_NCMBUTTONUP == wParam)) {
        enable = true;


    } else if (caprbtn && (WM_RBUTTONDBLCLK == wParam || WM_NCRBUTTONDBLCLK == wParam)) {
        enable = true;
    } else if (caprbtn && (WM_RBUTTONDOWN == wParam || WM_NCRBUTTONDOWN == wParam)) {
        enable = true;
    } else if (caprbtn && (WM_RBUTTONUP == wParam || WM_NCRBUTTONUP == wParam)) {
        enable = true;


    } else if (capxbtn && (WM_XBUTTONDBLCLK == wParam || WM_NCXBUTTONDBLCLK == wParam)) {
        enable = true;
    } else if (capxbtn && (WM_XBUTTONDOWN == wParam || WM_NCXBUTTONDOWN == wParam)) {
        enable = true;
    } else if (capxbtn && (WM_XBUTTONUP == wParam || WM_NCXBUTTONUP == wParam)) {
        enable = true;


    } else if (capwheel && WM_MOUSEHWHEEL == wParam) {
        enable = true;
    } else if (capwheel && WM_MOUSEWHEEL == wParam) {
        enable = true;


    } else if (capmove && WM_MOUSEMOVE == wParam) {
        enable = true;
    } else if (capmove && WM_NCMOUSEMOVE == wParam) {
        enable = true;
    }

    if (enable) {
        LPMSLLHOOKSTRUCT lpmshook = new MSLLHOOKSTRUCT;
        memcpy(lpmshook, (LPMSLLHOOKSTRUCT)lParam, sizeof(MSLLHOOKSTRUCT));
        PostMessage(g_hwnd, WM_MOUSE_GLOBAL_HOOK, wParam, (LPARAM)lpmshook);
    }

    return CallNextHookEx(g_hook, code, wParam, lParam);
}
