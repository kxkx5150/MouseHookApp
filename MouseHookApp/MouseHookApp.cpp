// MouseHookApp.cpp : Defines the entry point for the application.
#include "MouseHookApp.h"
#include "../MouseHook/MouseHook/MouseHook.h"
#include "framework.h"
#include <string>
#pragma comment(lib, "MouseHook.lib")

#define MAX_LOADSTRING 100
HINSTANCE hInst;
HWND g_hwnd = nullptr;
HWND g_eventedit_hwnd = nullptr;
HWND g_event_x_hwnd = nullptr;
HWND g_event_y_hwnd = nullptr;
HWND g_event_data_hwnd = nullptr;
HWND g_event_flg_hwnd = nullptr;
HWND g_event_time_hwnd = nullptr;

WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
void create_gui();
HWND create_edittext(HWND hParent, int nX, int nY, int nWidth, int nHeight, int id);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hpins, _In_ LPWSTR lccmd, _In_ int mcmd)
{
    UNREFERENCED_PARAMETER(hpins);
    UNREFERENCED_PARAMETER(lccmd);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MOUSEHOOKAPP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, mcmd)) {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MOUSEHOOKAPP));
    create_gui();
    start_hook(g_hwnd, true, true, true, true, true, true);
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    end_hook();
    return (int)msg.wParam;
}
HWND create_edittext(HWND hParent, int nX, int nY, int nWidth, int nHeight, int id)
{
    return CreateWindow(
        TEXT("EDIT"), L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_AUTOHSCROLL,
        nX, nY, nWidth, nHeight,
        hParent, (HMENU)id, hInst, NULL);
}
void create_gui()
{
    g_eventedit_hwnd = create_edittext(g_hwnd, 4, 4, 240, 26, 0);
    g_event_x_hwnd = create_edittext(g_hwnd, 4, 34, 100, 26, 0);
    g_event_y_hwnd = create_edittext(g_hwnd, 4, 64, 100, 26, 0);
    g_event_data_hwnd = create_edittext(g_hwnd, 4, 94, 100, 26, 0);
    g_event_flg_hwnd = create_edittext(g_hwnd, 4, 124, 100, 26, 0);
    g_event_time_hwnd = create_edittext(g_hwnd, 4, 154, 100, 26, 0);
}
void show_event(UINT message, WPARAM wParam, LPMSLLHOOKSTRUCT mousell)
{

    std::wstring ptx = std::to_wstring(mousell->pt.x);
    std::wstring pty = std::to_wstring(mousell->pt.y);
    std::wstring data = std::to_wstring(mousell->mouseData);
    std::wstring flg = std::to_wstring(mousell->flags);
    std::wstring time = std::to_wstring(mousell->time);

    SetWindowText(g_event_x_hwnd, ptx.c_str());
    SetWindowText(g_event_y_hwnd, pty.c_str());
    SetWindowText(g_event_data_hwnd, data.c_str());
    SetWindowText(g_event_flg_hwnd, flg.c_str());
    SetWindowText(g_event_time_hwnd, time.c_str());

    if (WM_LBUTTONDBLCLK == wParam || WM_NCLBUTTONDBLCLK == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_LBUTTONDBLCLK");

    } else if (WM_LBUTTONDOWN == wParam || WM_NCLBUTTONDOWN == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_LBUTTONDOWN");

    } else if (WM_LBUTTONUP == wParam || WM_NCLBUTTONUP == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_LBUTTONUP");

    } else if (WM_MBUTTONDBLCLK == wParam || WM_NCMBUTTONDBLCLK == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_MBUTTONDBLCLK");

    } else if (WM_MBUTTONDOWN == wParam || WM_NCMBUTTONDOWN == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_MBUTTONDOWN");

    } else if (WM_MBUTTONUP == wParam || WM_NCMBUTTONUP == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_MBUTTONUP");

    } else if (WM_RBUTTONDBLCLK == wParam || WM_NCRBUTTONDBLCLK == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_RBUTTONDBLCLK");

    } else if (WM_RBUTTONDOWN == wParam || WM_NCRBUTTONDOWN == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_RBUTTONDOWN");

    } else if (WM_RBUTTONUP == wParam || WM_NCRBUTTONUP == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_RBUTTONUP");

    } else if (WM_XBUTTONDBLCLK == wParam || WM_NCXBUTTONDBLCLK == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_XBUTTONDBLCLK");

    } else if (WM_XBUTTONDOWN == wParam || WM_NCXBUTTONDOWN == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_XBUTTONDOWN");

    } else if (WM_XBUTTONUP == wParam || WM_NCXBUTTONUP == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_XBUTTONUP");

    } else if (WM_MOUSEHWHEEL == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_MOUSEHWHEEL");

    } else if (WM_MOUSEWHEEL == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_MOUSEWHEEL");

    } else if (WM_MOUSEMOVE == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_MOUSEMOVE");

    } else if (WM_NCMOUSEMOVE == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_NCMOUSEMOVE");
    }
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MOUSEHOOKAPP));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MOUSEHOOKAPP);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;
    g_hwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 280, 260, nullptr, nullptr, hInstance, nullptr);
    if (!g_hwnd) {
        return FALSE;
    }

    ShowWindow(g_hwnd, nCmdShow);
    UpdateWindow(g_hwnd);
    return TRUE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        switch (wmId) {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    } break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    } break;

    case WM_MOUSE_GLOBAL_HOOK: {
        LPMSLLHOOKSTRUCT mousell = (LPMSLLHOOKSTRUCT)lParam;
        show_event(message, wParam, mousell);
        delete mousell;
    } break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message) {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
