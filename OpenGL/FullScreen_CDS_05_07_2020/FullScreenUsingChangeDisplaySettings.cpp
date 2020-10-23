// Header Files

#include <windows.h>
#include <tchar.h>


// Global Variable Declarations

RECT rcRect;
DWORD dwStyle;
HWND ghwnd = NULL;
bool gbFullScreen = false;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
//DWORD dwExStyle;

// Global Function Declarations

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


// WinMain()

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, INT iCmdShow)
{
	// Local Function Declarations

	void ToggleFullScreen(void);

	// Local Variable Declarations

	MSG msg;
	HWND hwnd;
	DEVMODE dm;
	//INT cxScreen;
	//INT cyScreen;
	WNDCLASSEX WndClass;
	MONITORINFO mi = { sizeof(MONITORINFO) };
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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx Failed To Register Class"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}

	//cxScreen = GetSystemMetrics(SM_CXSCREEN) / 2;
	//cyScreen = GetSystemMetrics(SM_CYSCREEN) / 2;


	dm.dmSize = { sizeof(DEVMODE) };
	
	if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm) == 0)
	{
		MessageBox(NULL, TEXT("EnumDisplaySettings Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	//dm.dmPelsWidth = 1920;
	//dm.dmPelsHeight = 1080;

	dm.dmPelsWidth = 800;
	dm.dmPelsHeight = 600;
	dm.dmBitsPerPel = 32;
	dm.dmFields = DM_PELSHEIGHT | DM_PELSWIDTH | DM_BITSPERPEL;

	if (DISP_CHANGE_SUCCESSFUL != ChangeDisplaySettings(&dm, CDS_FULLSCREEN))
	{
		MessageBox(NULL, TEXT("ChangeDisplaySettings Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcRect, 0);

	hwnd = CreateWindow(szAppName,
		TEXT("Full Screen : ChangeDisplaySettings"),
		WS_OVERLAPPEDWINDOW,
		rcRect.right / 4,
		rcRect.bottom / 4,
		rcRect.right / 2 - rcRect.left,
		rcRect.bottom / 2 - rcRect.top,
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

	if (gbFullScreen)
	{
		ChangeDisplaySettings(0, 0);
		ShowCursor(TRUE);
	}

	
	return((INT)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uiMessage, WPARAM wParam, LPARAM lParam)
{
	// Local Function Declaration

	void ToggleFullScreen();

	// Local Variable Declarations

	HDC hdc;
	PAINTSTRUCT ps;

	// Code

	switch (uiMessage)
	{
	case WM_PAINT:
		
		hdc = BeginPaint(ghwnd, &ps);

		GetClientRect(hwnd, &rcRect);

		SetBkColor(hdc, RGB(125, 125, 125));
		SetTextColor(hdc, RGB(0, 255, 0));

		DrawText(hdc, TEXT("Hello World"), -1, &rcRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		EndPaint(hwnd, &ps);

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

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
	}

	return(DefWindowProc(hwnd, uiMessage, wParam, lParam));
}


void ToggleFullScreen(void)
{
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

				SetWindowPos(ghwnd, HWND_TOP, 
					mi.rcMonitor.left, 
					mi.rcMonitor.top, 
					mi.rcMonitor.right - mi.rcMonitor.left,
					mi.rcMonitor.bottom - mi.rcMonitor.top,
					SWP_FRAMECHANGED | SWP_NOZORDER
					);
			}

			ShowCursor(FALSE);
			gbFullScreen = true;
		}
	}
	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, (dwStyle | WS_OVERLAPPEDWINDOW));
		SetWindowPlacement(ghwnd, &wpPrev);

		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);

		ShowCursor(TRUE);
		gbFullScreen = false;
	}

}