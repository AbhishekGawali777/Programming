// Header Files

#include <windows.h>
#include <tchar.h>

// Global Variable Declarations

DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
bool gbFullScreen = false;
HWND ghwnd = NULL;

// Global Function Declarations

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// WinMain

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, INT iCmdShow)
{
	// Local Variable Declarations

	MSG msg;
	HWND hwnd;
	RECT rcWorkArea;
	WNDCLASSEX WndClass;

	TCHAR szAppName[] = TEXT("MyWindow");

	// Code

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.lpfnWndProc = WndProc;
	WndClass.hInstance = hInstance;
	WndClass.lpszClassName = szAppName;
	WndClass.lpszMenuName = NULL;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx Failed To Register Class"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}

	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0);

	hwnd = CreateWindow(szAppName,
						TEXT("Full Screen Aplication"),
						WS_OVERLAPPEDWINDOW,
						rcWorkArea.right / 4 + rcWorkArea.left,
						rcWorkArea.bottom / 4 + rcWorkArea.top,
						rcWorkArea.right / 2,
						rcWorkArea.bottom / 2,
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

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((INT)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	// Local Function Declaration

	void ToggleFullScreen(void);

	// Code

	switch (iMessage)
	{
	case WM_KEYDOWN:

		switch (wParam)
		{
		case 0x46:
		case 0x66:
			ToggleFullScreen();
			break;

		default:
			break;
		}

		break;

	case WM_DESTROY:
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
			0, 0, 0, 0,
			SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED
		);

		ShowCursor(TRUE);
		gbFullScreen = false;

	}
}