// Header File

#include"MyHeader.h"

// WinMain()

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, INT iCmdShow)
{
	// Local Variable Declarations

	MSG msg;
	HWND hwnd;
	bool bDone = false;
	WNDCLASSEX WndClass;
	TCHAR szAppName[] = TEXT("MyWindow");

	// Code

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WndClass.lpszClassName = szAppName;
	WndClass.lpszMenuName = NULL;
	WndClass.cbWndExtra = 0;
	WndClass.cbClsExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	WndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	
	if ((fopen_s(&gpFile, "LogFile.txt", "w")))
	{
		MessageBox(NULL, TEXT("LogFile Creation Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	else
	{
		fprintf(gpFile, "LogFile Created Successfully...!!!\n\n");
	}

	if (!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}

	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szAppName,
		TEXT("Two 2D Shapes"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		150,
		150,
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

	while (false == bDone)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != FALSE)
		{
			if (WM_QUIT == msg.message)
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
			if (true == gbActiveWindow)
			{
				Display();
			}
		}
	}

	return((int)msg.wParam);
}

// WndProc()

LRESULT CALLBACK WndProc(HWND hwnd, UINT uiMessage, WPARAM wParam, LPARAM lParam)
{

	// Code

	switch (uiMessage)
	{
	case WM_SETFOCUS:
		gbActiveWindow = true;
		break;

	case WM_KILLFOCUS:

		gbActiveWindow = false;
		break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case 0x1B:
			DestroyWindow(hwnd);
			break;

		case 0x46:
		case 0x66:

			ToggleFullScreen();
			break;
		}

		break;

	case WM_ERASEBKGND:
		return(0);

	case WM_SIZE:

		Resize(LOWORD(lParam), HIWORD(lParam));
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


// ToggleFullScreen()

void ToggleFullScreen(void)
{
	// Local Variable Declarations

	MONITORINFO mi = { sizeof(MONITORINFO) };

	// Code

	dwStyle = GetWindowLong(ghwnd, GWL_STYLE);

	if (false == gbFullScreen)
	{
		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			if (GetWindowPlacement(ghwnd, &wpPrev) && 
				GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, (dwStyle & ~WS_OVERLAPPEDWINDOW));
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
			SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_FRAMECHANGED
			);

		ShowCursor(TRUE);
		gbFullScreen = false;
	}
}

// Initialize()

void Initialize(void)
{
	// Local Variable Declarations

	int iPixelFormatIndex;
	PIXELFORMATDESCRIPTOR pfd;

	// Code

	ghdc = GetDC(ghwnd);

	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = { sizeof(PIXELFORMATDESCRIPTOR) };
	pfd.nVersion = 1;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cBlueBits = 8;
	pfd.cGreenBits = 8;
	pfd.cAlphaBits = 8;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);

	if (0 == iPixelFormatIndex)
	{
		fprintf(gpFile, "\nChoosePixelFormat() Failed\n");
		DestroyWindow(ghwnd);
	}

	if (FALSE == SetPixelFormat(ghdc, iPixelFormatIndex, &pfd))
	{
		fprintf(gpFile, "\nSetPixelFormat() Failed\n");
		DestroyWindow(ghwnd);
	}

	ghrc = wglCreateContext(ghdc);

	if (NULL == ghrc)
	{
		fprintf(gpFile, "\nwglCreateContext() Failed\n");
		DestroyWindow(ghwnd);
	}

	if (FALSE == wglMakeCurrent(ghdc, ghrc))
	{
		fprintf(gpFile, "\nwglMakeCurrent() Failed\n");
		DestroyWindow(ghwnd);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Resize(WIN_WIDTH, WIN_HEIGHT);
}

// Display()

void Display(void)
{
	// Code

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-1.5f, 0.0f, -5.0f);

	// Triangle

	glBegin(GL_TRIANGLES);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);

	glEnd();

	// Rectangle
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(1.5f, 0.0f, -5.0f);

	glBegin(GL_QUADS);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
		
	glEnd();

	SwapBuffers(ghdc);
}

// Resize()

void Resize(int iWidth, int iHeight)
{
	// Code

	if (0 == iHeight)
		iHeight = 1;

	glViewport(0, 0, (GLsizei)iWidth, GLsizei(iHeight));

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)iWidth / (GLfloat)iHeight, 0.1f, 100.0f);
}

// Uninitialize()

void Uninitialize(void)
{
	// Code

	if (true == gbFullScreen)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);

		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd,
			HWND_TOP,
			0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_FRAMECHANGED
			);
		ShowCursor(TRUE);
	}

	if (wglGetCurrentContext() == ghrc)
		wglMakeCurrent(NULL, NULL);

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
		fprintf(gpFile, "\n\nLogFile Closed Successfully...!!!\n\n");
		gpFile = NULL;
	}
}
