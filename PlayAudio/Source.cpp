#include <Windows.h>
#include <process.h>
#include <memory>
#include"PlayAudio.h"

BOOL InitApp(HINSTANCE, WNDPROC, LPCTSTR);
BOOL InitInstance(HINSTANCE, int, LPCTSTR, LPCSTR);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChilWndProc(HWND, UINT, WPARAM, LPARAM);

const char CLASS_NAME[] = "MainWindowClass";
const char CHIL_CLASS_NAME[] = "Child";
const char WINDOW_NAME[] = "Learn to Program Windows";
const char CHIL_WINDOW_NAME[] = "Child Window";

#define ID_MYCHILD 100

std::unique_ptr<PlayAudio> pAudio(nullptr);

int APIENTRY WinMain(
    _In_ HINSTANCE hInstance,       // handle to current instance 
    _In_opt_ HINSTANCE hInstPrev,   // handle to previous instance 
    _In_ LPSTR lpCmdLine,           // address of command-line string 
    _In_ int nCmdShow)              // show-window type 
{
    
    if (!hInstPrev) {
        // Register the main window class.
        if (!InitApp(hInstance, MainWndProc, CLASS_NAME)) {
            return FALSE;
        }
    }
    if (!InitInstance(hInstance, nCmdShow, CLASS_NAME, WINDOW_NAME)) {
        return FALSE;
    }

    // Process other messages. 
    MSG msg = {};
    
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

BOOL InitApp(HINSTANCE hInstance, WNDPROC WmdProc, LPCTSTR szClassName)
{
    WNDCLASS wc;

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC)WmdProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szClassName;

    return RegisterClass(&wc);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, LPCTSTR szClassName, LPCSTR szWindowName)
{
    HWND hWnd = NULL;

    hWnd = CreateWindow(
        szClassName,
        szWindowName,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (!hWnd) return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK MainWndProc(
    HWND hWnd,        // handle to window
    UINT uMsg,        // message identifier
    WPARAM wParam,    // first message parameter
    LPARAM lParam)    // second message parameter
{
    static HWND hChilWnd = NULL;
    HINSTANCE hInstance = NULL;
    switch (uMsg)
    {
    case WM_CREATE:
        // Initialize the window.

        // Create child window.
        hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
        InitApp(hInstance, ChilWndProc, CHIL_CLASS_NAME);

        hChilWnd = CreateWindow(
            CHIL_CLASS_NAME,
            CHIL_WINDOW_NAME,
            WS_CHILD | WS_SYSMENU | WS_THICKFRAME | WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            200,
            100,
            hWnd,
            (HMENU)ID_MYCHILD,
            hInstance,
            NULL
        );
        ShowWindow(hChilWnd, SW_SHOW);
        UpdateWindow(hChilWnd);
        return 0;

    case WM_PAINT:
        // Paint the window's client area. 
        return 0;

    case WM_SIZE:
        // Set the size and position of the window. 
        return 0;

    case WM_CLOSE:
        DestroyWindow(hWnd);
        return 0;

    case WM_DESTROY:
        // Clean up window-specific data objects.
        PostQuitMessage(0);
        return 0;

        // 
        // Process other messages. 
        // 

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK ChilWndProc(
    HWND hWnd,        // handle to window
    UINT uMsg,        // message identifier
    WPARAM wParam,    // first message parameter
    LPARAM lParam)    // second message parameter
{

    switch (uMsg)
    {
    case WM_CREATE:
        // Initialize the window.

        // Start to playing audio.
        pAudio.reset(new PlayAudio(hWnd, "C:\\Windows\\Media\\Alarm01.wav"));
        pAudio->Play();
        
        return 0;

    case WM_PAINT:
        // Paint the window's client area. 
        return 0;

    case WM_SIZE:
        // Set the size and position of the window. 
        return 0;
    
    case WM_CLOSE:
        // stop to playing audio.
        pAudio->Stop();
        pAudio.reset(nullptr);

        DestroyWindow(hWnd);
        return 0;

    case WM_DESTROY:
        // Clean up window-specific data objects.

        PostQuitMessage(0);
        return 0;

        // 
        // Process other messages. 
        // 
    case MM_MCINOTIFY:
        pAudio->Repeat();

        return 0;

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}
