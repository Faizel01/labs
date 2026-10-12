#include <windows.h>
#include <stdio.h>
#include <tchar.h>

// Віконна процедура для обробки повідомлень
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Отримання системних метрик
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
        int hScrollWidth = GetSystemMetrics(SM_CXHSCROLL);
        int hScrollHeight = GetSystemMetrics(SM_CYHSCROLL);
        int frameWidth = GetSystemMetrics(SM_CXFRAME);
        int frameHeight = GetSystemMetrics(SM_CYFRAME);

        TCHAR buffer[256];
        int yPos = 20;

        // Виведення системної інформації у вікно програми
        TextOut(hdc, 20, yPos, TEXT("System Information (Metrics):"), 29);
        yPos += 30;

        _stprintf_s(buffer, TEXT("1. Screen Width: %d pixels"), screenWidth);
        TextOut(hdc, 40, yPos, buffer, (int)_tcslen(buffer));
        yPos += 25;

        _stprintf_s(buffer, TEXT("2. Screen Height: %d pixels"), screenHeight);
        TextOut(hdc, 40, yPos, buffer, (int)_tcslen(buffer));
        yPos += 25;

        _stprintf_s(buffer, TEXT("3. Horizontal Scroll Bar Width: %d pixels"), hScrollWidth);
        TextOut(hdc, 40, yPos, buffer, (int)_tcslen(buffer));
        yPos += 25;

        _stprintf_s(buffer, TEXT("4. Horizontal Scroll Bar Height: %d pixels"), hScrollHeight);
        TextOut(hdc, 40, yPos, buffer, (int)_tcslen(buffer));
        yPos += 25;

        _stprintf_s(buffer, TEXT("5. Window Frame Width: %d pixels"), frameWidth);
        TextOut(hdc, 40, yPos, buffer, (int)_tcslen(buffer));
        yPos += 25;

        _stprintf_s(buffer, TEXT("6. Window Frame Height: %d pixels"), frameHeight);
        TextOut(hdc, 40, yPos, buffer, (int)_tcslen(buffer));

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// Головна функція програми
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"StudentClass"; // Ім'я класу вікна (латиницею)[cite: 1]

    WNDCLASS wc = {};
    wc.style = CS_HREDRAW;                        // Вирівнювання клієнтської області по горизонталі[cite: 1]
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);   // Тип іконки[cite: 1]
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);     // Тип курсору[cite: 1]
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Колір фону вікна - білий[cite: 1]
    wc.lpszClassName = CLASS_NAME;

    // Реєстрація класу вікна в системі
    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("Window Registration Failed!"), TEXT("Error"), MB_ICONERROR);
        return 0;
    }

    // Створення вікна програми
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        TEXT("Lab Work - System Information"),         // Заголовок вікна[cite: 1]
        WS_OVERLAPPEDWINDOW,                           // Стиль вікна (має заголовок і рамку)[cite: 1]
        CW_USEDEFAULT, CW_USEDEFAULT,                  // Позиція вікна за замовчуванням[cite: 1]
        650, 350,                                      // Ширина та висота вікна
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    // Відображення та оновлення вікна
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Цикл обробки повідомлень операційної системи
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}