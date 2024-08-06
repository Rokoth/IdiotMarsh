#include "framework.h"
#include "IdiotMarsch.h"
#include <stdio.h>
#include "sqlite3.h"
#include <array>
#include "MapManager.h"

using namespace std;

constexpr auto MAX_LOADSTRING = 100;

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
BOOL isAuth = false;
int x = 1;
int y = 1;

sqlite3* db = 0; // хэндл объекта соединение к БД
char* err = 0;

BOOL NEED_AUTH = true;

MapManager* _mapManager = new MapManager();

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Auth(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_IDIOTMARSCH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_IDIOTMARSCH));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_IDIOTMARSCH));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_IDIOTMARSCH);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    DialogBox(hInst, MAKEINTRESOURCE(IDD_AUTHBOX), hWnd, Auth);

    if (!isAuth)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    POINT ptClientUL; // client area upper left corner  
    POINT ptClientLR; // client area lower right corner  
    static HDC hdcCompat; // handle to DC for bitmap  
    static POINT pt;      // x- and y-coordinates of cursor  
    static RECT rcTarget; // rect to receive filled shape  
    static RECT rcClient; // client area rectangle  

    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_AUTH:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_AUTHBOX), hWnd, Auth);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_LEFT:
            _mapManager->MoveLeft();
            break;
        case VK_RIGHT:
            _mapManager->MoveRight();
            break;

        case VK_UP:
            _mapManager->MoveUp();
            break;
        case VK_DOWN:
            _mapManager->MoveDown();
            break;
        default:
            break;
        }
        RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
    }
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        std::array<std::array<int, 10>, 10> current_map = _mapManager->GetCurrentMap();
        std::tuple<int, int> current_position = _mapManager->GetCurrentPosition();
        for (int i = 0; i < current_map.size(); i++)
        {
            for (int j = 0; j < current_map[i].size(); j++)
            {
                if (current_map[i][j] == 1)
                {
                    SelectObject(ps.hdc, GetStockObject(GRAY_BRUSH));
                }
                else
                {
                    SelectObject(ps.hdc, GetStockObject(WHITE_BRUSH));
                }
                Rectangle(ps.hdc, 30 + 30 * i, 30 + 30 * j, 60 + 30 * i, 60 + 30 * j);
            }
        }
        const COLORREF rgbRed = 0x000000FF;
        HBRUSH hbr = CreateSolidBrush(rgbRed);
        SelectObject(ps.hdc, hbr);
        Ellipse(ps.hdc,
            30 + 30 * std::get<0>(current_position),
            30 + 30 * std::get<1>(current_position),
            60 + 30 * std::get<0>(current_position),
            60 + 30 * std::get<1>(current_position));
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        DeleteDC(hdcCompat);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

static int check_login(void* NotUsed, int argc, char** argv, char** azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

// Обработчик сообщений для окна "Авторизация".
INT_PTR CALLBACK Auth(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            TCHAR loginInput[MAX_PATH];
            GetWindowTextW(GetDlgItem(hDlg, IDC_EDIT_LOGIN), loginInput, MAX_PATH);
            TCHAR passwordInput[MAX_PATH];
            GetWindowTextW(GetDlgItem(hDlg, IDC_EDIT_PASSWORD), passwordInput, MAX_PATH);
            if (NEED_AUTH)
            {
                string SELECT_USERS = "select * from users where name = ";
                SELECT_USERS.append(MAX_PATH, *loginInput);
                SELECT_USERS.append(" and password = ");
                SELECT_USERS.append(MAX_PATH, *passwordInput);
                SELECT_USERS.append(";");

                // открываем соединение
                if (sqlite3_open("local.sqlite", &db))
                    fprintf(stderr, "Ошибка открытия/создания БД: %s\n", sqlite3_errmsg(db));
                // выполняем SQL
                else if (sqlite3_exec(db, SELECT_USERS.c_str(), check_login, 0, &err))
                {
                    fprintf(stderr, "Ошибка SQL: %sn", err);
                    sqlite3_free(err);
                }
                // закрываем соединение
                sqlite3_close(db);

                if (!_tcscmp(loginInput, L"admin") && !_tcscmp(passwordInput, L"admin"))
                {
                    isAuth = true;
                    EndDialog(hDlg, LOWORD(wParam));
                    return (INT_PTR)TRUE;
                }
            }
            else
            {
                isAuth = true;
            }
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
