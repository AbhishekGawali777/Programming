// Header Files

#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include "MyHeader.h"

/// Macros

#define WIN_WIDTH  800
#define WIN_HEIGHT 600

// Global Variable Declarations

FILE* gpFile;
DWORD dwStyle;
HWND ghwnd = NULL;
bool gbDone = false;
bool gbFullScreen = false;
bool gbActiveWindow = false;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

// Global Function Declarations

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// WinMain

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, INT iCmdShow)
{
	// Function Declarations

	void Display(void);
	void Initialize(void);

	// Local Variable Declarations

	MSG msg;
	HWND hwnd;
	WNDCLASSEX WndClass;
	TCHAR szAppName[] = TEXT("MyWindow");

	// Code


	if (fopen_s(&gpFile, "LogFile.txt", "w"))
	{
		MessageBox(NULL, TEXT("Cannot Create Desired File"), TEXT("ERROR..!!!"), MB_OK | MB_ICONERROR);
		exit(0);
	}


	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.lpfnWndProc = WndProc;
	WndClass.hInstance = hInstance;
	WndClass.lpszClassName = szAppName;
	WndClass.lpszMenuName = NULL;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	WndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx Failed To Register Class"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}

	hwnd = CreateWindow(szAppName,
		TEXT("Window With Icon"),
		WS_OVERLAPPEDWINDOW, //| WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		100,
		100,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (NULL == hwnd)
	{
		MessageBox(NULL, TEXT("CreateWindow Failed To Create Window"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}

	ghwnd = hwnd;

	Initialize();
	ShowWindow(hwnd, iCmdShow);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);
	
	//UpdateWindow(hwnd);

	///////////////////////		 Game Loop		////////////////////

	while (gbDone == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				gbDone = true;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (gbActiveWindow == true)
			{
				// Here You should call Update() Function For OpenGL Rendering

				// Here You should call Display() Function For OpenGL Rendering
				Display();
			}
		}
	}

	return((INT)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	// Local Function Declaration

	void ToggleFullScreen(void);
	void Resize(int, int);
	void Uninitialize(void);

	// Code

	switch (iMessage)
	{
	case WM_SETFOCUS:
		gbActiveWindow = true;
		break;
	
	case WM_KILLFOCUS:
		gbActiveWindow = false;
		break;

	case WM_ERASEBKGND:
		return(0);

	case WM_SIZE:
		Resize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;

		case 0x46:
		case 0x66:
			ToggleFullScreen();
			break;

		default:
			break;
		}
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		Uninitialize();
		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(hwnd, iMessage, wParam, lParam));
}

void ToggleFullScreen(void)
{
	// Local Variable Declarations

	MONITORINFO mi = { sizeof(MONITORINFO) };

	// Code

	if (gbFullScreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);

		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{

				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & (~WS_OVERLAPPEDWINDOW));

				SetWindowPos(ghwnd,
					HWND_TOP,
					mi.rcMonitor.left,
					mi.rcMonitor.top,
					mi.rcMonitor.right - mi.rcMonitor.left,
					mi.rcMonitor.bottom - mi.rcMonitor.top,
					//100, 100, WIN_WIDTH, WIN_HEIGHT,
					SWP_NOZORDER | SWP_FRAMECHANGED
				);
			}
		}

		ShowCursor(FALSE);
		gbFullScreen = true;
	}
	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, (dwStyle | WS_OVERLAPPEDWINDOW));
		SetWindowPlacement(ghwnd, &wpPrev);

		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0,
			SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED
		);

		ShowCursor(TRUE);
		gbFullScreen = false;

	}
}

void Initialize(void)
{
	// Function Declaration

	void Resize(int, int);

	// Variable Declarations

	// Code 

	// Warmup Call To Resize()

	Resize(WIN_WIDTH, WIN_HEIGHT);
}

void Resize(int iWidth, int iHeight)
{
	// Code

	if (iHeight == 0)
		iHeight = 1;
}

void Display(void)
{
	// Code
}

void Uninitialize(void)
{
	if (gpFile)
	{
		free(gpFile);
		gpFile = NULL;
	}
}