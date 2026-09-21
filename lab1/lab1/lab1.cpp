// lab1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "lab1.h"

#define MAX_LOADSTRING 100


HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    wcscpy_s(szTitle, L"Лабораторна робота №1");

    wcscpy_s(szWindowClass, L"Egor");

    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg = {};

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex{};

    wcex.cbSize = sizeof(WNDCLASSEX);


    wcex.style = CS_HREDRAW | CS_VREDRAW;

    wcex.lpfnWndProc = WndProc;

    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;

    wcex.hInstance = hInstance;

    wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);

    wcex.hCursor = LoadCursor(nullptr, IDC_HELP);

    wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);

    wcex.lpszMenuName = nullptr;

    wcex.lpszClassName = szWindowClass;

    wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    return RegisterClassExW(&wcex);
}



BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    HWND hWnd = CreateWindowW(
        szWindowClass,              // ім'я класу
        szTitle,                    // заголовок вікна
        WS_OVERLAPPEDWINDOW,        // стиль вікна

        0,                          // X - лівий край екрану
        0,                          // Y - верхній край екрану

        500,                        // ширина
        200,                        // висота

        nullptr,                    
        nullptr,
        hInstance,
        nullptr
    );

    if (!hWnd)
    {
        return FALSE;
    }


    HMENU hSystemMenu = GetSystemMenu(hWnd, FALSE);

    if (hSystemMenu)
    {
        DeleteMenu(
            hSystemMenu,
            SC_CLOSE,
            MF_BYCOMMAND
        );
    }


    ShowWindow(hWnd, nCmdShow);

    UpdateWindow(hWnd);

    return TRUE;
}


LRESULT CALLBACK WndProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (message)
    {

    case WM_PAINT:
    {
        PAINTSTRUCT ps;

        HDC hdc = BeginPaint(hWnd, &ps);



        HFONT hFont = CreateFontW(
            20,
            0,
            0,
            0,
            FW_NORMAL,
            FALSE,
            FALSE,
            FALSE,
            DEFAULT_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_DONTCARE,
            L"Arial"
        );


        HFONT hOldFont =
            (HFONT)SelectObject(hdc, hFont);


        TEXTMETRIC tm{};

        GetTextMetrics(hdc, &tm);

        int fontHeight = tm.tmHeight;

        int lineSpacing =
            tm.tmHeight + tm.tmExternalLeading;



        RECT rectTitle = {
            0,
            15,
            500,
            45
        };

        DrawTextW(
            hdc,
            L"Лабораторна робота №1",
            -1,
            &rectTitle,
            DT_CENTER
        );


        RECT rectClass = {
            20,
            55,
            480,
            80
        };

        DrawTextW(
            hdc,
            L"Ім'я класу: Egor",
            -1,
            &rectClass,
            DT_LEFT
        );


        WCHAR fontInfo[200];

        swprintf_s(
            fontInfo,
            L"Висота шрифту: %d px    Міжрядковий інтервал: %d px",
            fontHeight,
            lineSpacing
        );


        RECT rectFont = {
            20,
            90,
            480,
            115
        };

        DrawTextW(
            hdc,
            fontInfo,
            -1,
            &rectFont,
            DT_LEFT
        );


        RECT rectSize = {
            20,
            125,
            480,
            150
        };

        DrawTextW(
            hdc,
            L"Розмір вікна: 500 x 200 px",
            -1,
            &rectSize,
            DT_LEFT
        );


        SelectObject(hdc, hOldFont);

        DeleteObject(hFont);


        EndPaint(hWnd, &ps);

        return 0;
    }

    case WM_SIZE:
    {
        InvalidateRect(hWnd, nullptr, TRUE);

        return 0;
    }

    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }

    default:
    {
        return DefWindowProc(
            hWnd,
            message,
            wParam,
            lParam
        );
    }
    }
}