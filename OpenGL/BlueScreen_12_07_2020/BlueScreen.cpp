
// Header Files

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <gl/GL.h>
#include "OpenGLHeader.h"
#pragma comment(lib, "OpenGL32.lib")

#define WIN_WIDTH	800
#define WIN_HEIGHT	600


// Global Variable Declarations

FILE* gpFile = NULL;

DWORD dwStyle;

bool gbFullScreen = false;
bool gbActiveWindow = false;

HDC ghdc = NULL;
HWND ghwnd = NULL;
HGLRC ghrc = NULL;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

// Function Declaration

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// WinMain

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, INT iCmdShow)
{
	// Function Declarations

	void Initialize(void);
//	void Display(void);

	// Loacal variable Declarations
	bool bDone = false;

	MSG msg;
	HWND hwnd;
	WNDCLASSEX WndClass;
	TCHAR szAppName[] = { TEXT("MyWindow") };

	// Code


	// Log File Creation

	if (fopen_s(&gpFile, "Log.txt", "w"))
	{
		MessageBox(NULL, TEXT("Cannot Create Log File"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	else
	{
		fprintf(gpFile, "Log File Created Successfully.\n\n");
	}

	// Initializing Custom Window Class.

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.lpfnWndProc = WndProc;
	WndClass.hInstance = hInstance;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszClassName = szAppName;
	WndClass.lpszMenuName = NULL;
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	WndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}

	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
						szAppName,
						TEXT("Blue Screen"),
						WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
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
		MessageBox(NULL, TEXT("CreateWindowEx Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}

	ghwnd = hwnd;

	Initialize();
	ShowWindow(hwnd, iCmdShow);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	while (bDone == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
		
			if (msg.message == WM_QUIT)
			{
				bDone = true;
			}
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
//				Display();
			}
		}
	}

	return((INT)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uiMessage, WPARAM wParam, LPARAM lParam)
{
	// Function Declarations

	void Display(void);
	void Resize(int, int);
	void Uninitialize(void);
	void ToggleFullScreen(void);
	
	// Code

	switch (uiMessage)
	{
	case WM_PAINT:
		Display();
		break;

	case WM_SETFOCUS:
		gbActiveWindow = true;
		break;

	case WM_KILLFOCUS:
		gbActiveWindow = false;
		break;

	case WM_ERASEBKGND:
		return(0);
		break;
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

	return(DefWindowProc(hwnd, uiMessage, wParam, lParam));
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
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd,
					HWND_TOP,
					mi.rcMonitor.left,
					mi.rcMonitor.top,
					mi.rcMonitor.right - mi.rcMonitor.left,
					mi.rcMonitor.bottom - mi.rcMonitor.top,
					SWP_NOZORDER | SWP_FRAMECHANGED
					);
			}
		}
		ShowCursor(FALSE);
		gbFullScreen = true;
	}
	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd,
			HWND_TOP, 
			0,
			0,
			0,
			0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED
			);

		ShowCursor(TRUE);
		gbFullScreen = false;
	}
}

void Initialize(void)
{
	// Function Decalrations

	void Resize(int, int);

	// Variable Declaraions

	INT iPixelFormatIndex;
	PIXELFORMATDESCRIPTOR pfd;

	// Code

	ghdc = GetDC(ghwnd);

	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);

	if (0 == iPixelFormatIndex)
	{
		fprintf(gpFile, "ChoosePixelFormat() Failed\n");
		DestroyWindow(ghwnd);
	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		fprintf(gpFile, "SetPixelFormat() Failed\n");
		DestroyWindow(ghwnd);
	}

	ghrc = wglCreateContext(ghdc);

	if (NULL == ghrc)
	{
		fprintf(gpFile, "wglCreateContext() Failed\n");
		DestroyWindow(ghwnd);
	}

	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fprintf(gpFile, "wglMakeCurrent() Failed\n");
		DestroyWindow(ghwnd);
	}

	// Set Clear Color

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	// Warmup Resize Call

	Resize(WIN_WIDTH, WIN_HEIGHT);

}

void Resize(int iWidth, int iHeight)
{
	// Code

	if (0 == iHeight)
		iHeight = 1;

	glViewport(0, 0, (GLsizei) iWidth, (GLsizei) iHeight);
}

void Display()
{
	// Code
	
	fprintf(gpFile, "In Display()\n");

	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	//glFinish();
}

void Uninitialize(void)
{
	// Code

	if (true == gbFullScreen)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		
		SetWindowLong(ghwnd, GWL_STYLE, (dwStyle | WS_OVERLAPPEDWINDOW));
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);

		ShowCursor(TRUE);
	}

	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if (gpFile)
	{
		fprintf(gpFile, "Log File Successfully Closed\n");
		fclose(gpFile);
		gpFile = NULL;
	}

}
