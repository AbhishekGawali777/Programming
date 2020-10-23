// Header Files

#include"MyHeader.h"

// Global Variable Declarations

DWORD	dwStyle;
HDC		ghdc = NULL;
HGLRC	ghrc = NULL;
HWND	ghwnd = NULL;
FILE* gpFile = NULL;

WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

bool gbFullScreen = false;
bool gbActiveWindow = false;

static GLfloat  fx1 = -2.0f;
static GLfloat  fy1 = 2.5f;
static GLfloat  fy2 = -2.0f;
static GLfloat  fx2 = 2.0f;
static GLfloat fPlane = -3.5f;
static GLfloat fRed = 0.0f;
static GLfloat fGreen = 0.0f;
static GLfloat fZmin = 1.0f;


// WinMain()

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, INT iCmdShow)
{
	// Local Variable Declarations

	MSG		msg;
	HWND	hwnd;
	bool	bDone = false;
	TCHAR	szAppName[] = TEXT("MyWindow");
	WNDCLASSEX WndClass;

	// Code

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = szAppName;
	WndClass.lpszMenuName = NULL;
	WndClass.hInstance = hInstance;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	WndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}

	if (fopen_s(&gpFile, "LogFile.txt", "w"))
	{
		MessageBox(NULL, TEXT("LogFile Creation Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}

	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szAppName,
		TEXT("Dynamic India"),
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
	ToggleFullScreen();
	
	PlaySound(MAKEINTRESOURCE(MYSONG), hInstance, SND_ASYNC | SND_RESOURCE);

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
				Update();
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

	case WM_SIZE:

		Resize(LOWORD(lParam), HIWORD(lParam));
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

		default:
			break;
		}

		break;

	case WM_ERASEBKGND:
		return(0);

	case WM_DESTROY:

		PlaySound(NULL, NULL, NULL);
		Uninitialize();
		PostQuitMessage(0);
		break;
	}


	return(DefWindowProc(hwnd, uiMessage, wParam, lParam));
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
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;

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

	// Warmup Call

	Resize(WIN_WIDTH, WIN_HEIGHT);
}

void ToggleFullScreen(void)
{
	// Local Variable Declaration

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
			0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED
		);

		ShowCursor(TRUE);
		gbFullScreen = false;
	}

}

// Display()

void Display(void)
{
	// Local variable Declarations

	

	// Code

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//DrawFlag();
	DrawINDIA();
	DrawIAFPlanes();

	// -

	/*glColor3f(8.0f, 0.5f, 0.0f);
	glVertex3f(1.33f, 0.0f, 0.0f);
	glVertex3f(1.22f, 0.0f, 0.0f);

	glColor3f(0.0f, 0.5f, 0.0f);
	glVertex3f(1.18f, -0.1f, 0.0f);
	glVertex3f(1.35f, -0.1f, 0.0f);*/


	//glEnd();

	SwapBuffers(ghdc);

}

// DrawFlag()

void DrawFlag(void)
{
	// Code

	if (fPlane <= -5.0f)
	{
		glTranslatef(0.0f, 0.0f, -4.0f);

		glBegin(GL_QUADS);

		glColor3f(1.0f, 0.5f, 0.0f);

		glVertex3f(1.0f, 0.4f, 0.0f);
		glVertex3f(-1.0f, 0.4f, 0.0f);
		glVertex3f(-1.0f, 0.1f, 0.0f);
		glVertex3f(1.0f, 0.1f, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);

		glVertex3f(1.0f, 0.1f, 0.0f);
		glVertex3f(-1.0f, 0.1f, 0.0f);
		glVertex3f(-1.0f, -0.2f, 0.0f);
		glVertex3f(1.0f, -0.2f, 0.0f);

		glColor3f(0.0f, 0.5f, 0.0f);

		glVertex3f(1.0f, -0.2f, 0.0f);
		glVertex3f(-1.0f, -0.2f, 0.0f);
		glVertex3f(-1.0f, -0.5f, 0.0f);
		glVertex3f(1.0f, -0.5f, 0.0f);

		glEnd();


		glLineWidth(3.0f);
		glTranslatef(0.0f, 0.0f, fZmin);
		glBegin(GL_LINE_LOOP);

		glColor3f(0.0f, 0.0f, 1.0f);

		for (GLfloat f = 0.0f; f < 2 * PI; f = f + 0.01f)
		{
			glVertex3f((GLfloat)cos(f), (GLfloat)sin(f), 0.0f);
		}

		glEnd();
	}

	if (fZmin < -15.0f)
		fZmin = -15.0f;

	fZmin = fZmin - 0.2f;
}

// DrawIAFPlanes()

void DrawIAFPlanes(void)
{
	// Code

	// IAF Plane Middle

	if (fPlane <= 5.5f)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(fPlane, 0.0f, -4.0f);

		glBegin(GL_TRIANGLES);

		glColor3f(0.2f, 0.3f, 0.4f);

		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.3f, 0.2f, 0.0f);
		glVertex3f(0.3f, -0.2f, 0.0f);

		glColor3f(0.0f, 0.0f, 0.5f);

		glVertex3f(0.7f, 0.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.5f);

		glVertex3f(0.4f, 0.1f, 0.0f);
		glVertex3f(0.4f, -0.1f, 0.0f);


		glEnd();

		glBegin(GL_QUADS);

		glColor3f(0.2f, 0.3f, 0.4f);

		glVertex3f(0.3f, 0.2f, 0.0f);
		glVertex3f(0.2f, 0.2f, 0.0f);
		glVertex3f(0.2f, -0.2f, 0.0f);
		glVertex3f(0.3f, -0.2f, 0.0f);

		glEnd();

		glBegin(GL_QUADS);

		glColor3f(0.2f, 0.3f, 0.4f);

		glVertex3f(0.2f, 0.2f, 0.0f);
		glVertex3f(-0.3f, 0.5f, 0.0f);
		glVertex3f(-0.3f, -0.5f, 0.0f);
		glVertex3f(0.2f, -0.2f, 0.0f);

		glEnd();

		glBegin(GL_TRIANGLES);

		glVertex3f(0.1f, 0.5f, 0.0f);
		glVertex3f(-0.3f, 0.5f, 0.0f);
		glVertex3f(-0.3f, 0.4f, 0.0f);

		glVertex3f(0.1f, -0.5f, 0.0f);
		glVertex3f(-0.3f, -0.5f, 0.0f);
		glVertex3f(-0.3f, -0.4f, 0.0f);

		glEnd();

		glBegin(GL_QUADS);

		glVertex3f(-0.3f, 0.2f, 0.0f);
		glVertex3f(-0.5f, 0.4f, 0.0f);
		glVertex3f(-0.5f, -0.4f, 0.0f);
		glVertex3f(-0.3f, -0.2f, 0.0f);

		glEnd();

		// Indian Flag

		glTranslatef(fPlane, 0.0f, -4.0f);

		glBegin(GL_QUADS);

		glColor3f(1.0f, 0.5f, 0.0f);

		glVertex3f(-1.0f, 0.4f, 0.0f);
		glVertex3f(-3.0f, 0.4f, 0.0f);
		glVertex3f(-3.0f, 0.1f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, 0.1f, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);

		glVertex3f(-1.0f, 0.1f, 0.0f);
		glVertex3f(-3.0f, 0.1f, 0.0f);
		glVertex3f(-3.0f, -0.2f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, -0.2f, 0.0f);

		glColor3f(0.0f, 0.5f, 0.0f);

		glVertex3f(-1.0f, -0.2f, 0.0f);
		glVertex3f(-3.0f, -0.2f, 0.0f);
		glVertex3f(-3.0f, -0.4f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, -0.4f, 0.0f);

		glEnd();


		fPlane = fPlane + 0.001f;
	}

	// Second plane Upper

	if (fPlane <= 5.5f)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(fPlane - 1.0f, 1.0f, -4.0f);

		glBegin(GL_TRIANGLES);

		glColor3f(0.2f, 0.3f, 0.4f);

		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.3f, 0.2f, 0.0f);
		glVertex3f(0.3f, -0.2f, 0.0f);

		glColor3f(0.0f, 0.0f, 0.5f);

		glVertex3f(0.7f, 0.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.5f);

		glVertex3f(0.4f, 0.1f, 0.0f);
		glVertex3f(0.4f, -0.1f, 0.0f);


		glEnd();

		glBegin(GL_QUADS);

		glColor3f(0.2f, 0.3f, 0.4f);

		glVertex3f(0.3f, 0.2f, 0.0f);
		glVertex3f(0.2f, 0.2f, 0.0f);
		glVertex3f(0.2f, -0.2f, 0.0f);
		glVertex3f(0.3f, -0.2f, 0.0f);

		glEnd();

		glBegin(GL_QUADS);

		glColor3f(0.2f, 0.3f, 0.4f);

		glVertex3f(0.2f, 0.2f, 0.0f);
		glVertex3f(-0.3f, 0.5f, 0.0f);
		glVertex3f(-0.3f, -0.5f, 0.0f);
		glVertex3f(0.2f, -0.2f, 0.0f);

		glEnd();

		glBegin(GL_TRIANGLES);

		glVertex3f(0.1f, 0.5f, 0.0f);
		glVertex3f(-0.3f, 0.5f, 0.0f);
		glVertex3f(-0.3f, 0.4f, 0.0f);

		glVertex3f(0.1f, -0.5f, 0.0f);
		glVertex3f(-0.3f, -0.5f, 0.0f);
		glVertex3f(-0.3f, -0.4f, 0.0f);

		glEnd();

		glBegin(GL_QUADS);

		glVertex3f(-0.3f, 0.2f, 0.0f);
		glVertex3f(-0.5f, 0.4f, 0.0f);
		glVertex3f(-0.5f, -0.4f, 0.0f);
		glVertex3f(-0.3f, -0.2f, 0.0f);

		glEnd();

		// Indian Flag

		glTranslatef(fPlane - 1.0f, 1.0f, -4.0f);

		glBegin(GL_QUADS);

		glColor3f(1.0f, 0.5f, 0.0f);

		glVertex3f(-1.0f, 0.4f, 0.0f);
		glVertex3f(-3.0f, 0.4f, 0.0f);
		glVertex3f(-3.0f, 0.1f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, 0.1f, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);

		glVertex3f(-1.0f, 0.1f, 0.0f);
		glVertex3f(-3.0f, 0.1f, 0.0f);
		glVertex3f(-3.0f, -0.2f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, -0.2f, 0.0f);

		glColor3f(0.0f, 0.5f, 0.0f);

		glVertex3f(-1.0f, -0.2f, 0.0f);
		glVertex3f(-3.0f, -0.2f, 0.0f);
		glVertex3f(-3.0f, -0.4f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, -0.4f, 0.0f);

		glEnd();


		fPlane = fPlane + 0.001f;
	}

	// Third plane Bottom

	if (fPlane <= 5.5f)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(fPlane - 1.0f, -1.0f, -4.0f);

		glBegin(GL_TRIANGLES);

		glColor3f(0.2f, 0.3f, 0.4f);

		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.3f, 0.2f, 0.0f);
		glVertex3f(0.3f, -0.2f, 0.0f);

		glColor3f(0.0f, 0.0f, 0.5f);

		glVertex3f(0.7f, 0.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.5f);

		glVertex3f(0.4f, 0.1f, 0.0f);
		glVertex3f(0.4f, -0.1f, 0.0f);


		glEnd();

		glBegin(GL_QUADS);

		glColor3f(0.2f, 0.3f, 0.4f);

		glVertex3f(0.3f, 0.2f, 0.0f);
		glVertex3f(0.2f, 0.2f, 0.0f);
		glVertex3f(0.2f, -0.2f, 0.0f);
		glVertex3f(0.3f, -0.2f, 0.0f);

		glEnd();

		glBegin(GL_QUADS);

		glColor3f(0.2f, 0.3f, 0.4f);

		glVertex3f(0.2f, 0.2f, 0.0f);
		glVertex3f(-0.3f, 0.5f, 0.0f);
		glVertex3f(-0.3f, -0.5f, 0.0f);
		glVertex3f(0.2f, -0.2f, 0.0f);

		glEnd();

		glBegin(GL_TRIANGLES);

		glVertex3f(0.1f, 0.5f, 0.0f);
		glVertex3f(-0.3f, 0.5f, 0.0f);
		glVertex3f(-0.3f, 0.4f, 0.0f);

		glVertex3f(0.1f, -0.5f, 0.0f);
		glVertex3f(-0.3f, -0.5f, 0.0f);
		glVertex3f(-0.3f, -0.4f, 0.0f);

		glEnd();

		glBegin(GL_QUADS);

		glVertex3f(-0.3f, 0.2f, 0.0f);
		glVertex3f(-0.5f, 0.4f, 0.0f);
		glVertex3f(-0.5f, -0.4f, 0.0f);
		glVertex3f(-0.3f, -0.2f, 0.0f);

		glEnd();

		// Indian Flag

		glTranslatef(fPlane - 1.0f, -1.0f, -4.0f);

		glBegin(GL_QUADS);

		glColor3f(1.0f, 0.5f, 0.0f);

		glVertex3f(-1.0f, 0.4f, 0.0f);
		glVertex3f(-3.0f, 0.4f, 0.0f);
		glVertex3f(-3.0f, 0.1f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, 0.1f, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);

		glVertex3f(-1.0f, 0.1f, 0.0f);
		glVertex3f(-3.0f, 0.1f, 0.0f);
		glVertex3f(-3.0f, -0.2f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, -0.2f, 0.0f);

		glColor3f(0.0f, 0.5f, 0.0f);

		glVertex3f(-1.0f, -0.2f, 0.0f);
		glVertex3f(-3.0f, -0.2f, 0.0f);
		glVertex3f(-3.0f, -0.4f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, -0.4f, 0.0f);

		glEnd();


		fPlane = fPlane + 0.001f;
	}
}

// DrawINDIA()

void DrawINDIA(void)
{
	// Code

	if (fx1 <= 0.0f && fPlane >= 5.5f)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(fx1, 0.0f, -4.0f);

		glBegin(GL_QUADS);

		// I

		glColor3f(1.0f, 0.5f, 0.0f);

		glVertex3f(-1.0f, 0.3f, 0.0f);
		glVertex3f(-1.5f, 0.3f, 0.0f);
		glVertex3f(-1.5f, 0.2f, 0.0f);
		glVertex3f(-1.0f, 0.2f, 0.0f);

		glVertex3f(-1.3f, 0.2f, 0.0f);
		glVertex3f(-1.2f, 0.2f, 0.0f);

		glColor3f(0.0f, 0.5f, 0.0f);

		glVertex3f(-1.2f, -0.2f, 0.0f);
		glVertex3f(-1.3f, -0.2f, 0.0f);

		glVertex3f(-1.0f, -0.3f, 0.0f);
		glVertex3f(-1.5f, -0.3f, 0.0f);
		glVertex3f(-1.5f, -0.2f, 0.0f);
		glVertex3f(-1.0f, -0.2f, 0.0f);

		glEnd();

		fx1 = fx1 + 0.001f;
	}

	// N

	if (fx1 > 0.0f)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(0.0f, fy1, -4.0f);

		glBegin(GL_QUADS);

		glColor3f(1.0f, 0.5f, 0.0f);

		glVertex3f(-0.8f, 0.3f, 0.0f);
		glVertex3f(-0.9f, 0.3f, 0.0f);

		glColor3f(0.0f, 0.5f, 0.0f);

		glVertex3f(-0.9f, -0.3f, 0.0f);
		glVertex3f(-0.8f, -0.3f, 0.0f);

		glColor3f(1.0f, 0.5f, 0.0f);

		glVertex3f(-0.8f, 0.3f, 0.0f);
		glVertex3f(-0.9f, 0.3f, 0.0f);

		glColor3f(0.0f, 0.5f, 0.0f);

		glVertex3f(-0.5f, -0.3f, 0.0f);
		glVertex3f(-0.4f, -0.3f, 0.0f);

		glColor3f(1.0f, 0.5f, 0.0f);

		glVertex3f(-0.5f, 0.3f, 0.0f);
		glVertex3f(-0.4f, 0.3f, 0.0f);

		glColor3f(0.0f, 0.5f, 0.0f);

		glVertex3f(-0.4f, -0.3f, 0.0f);
		glVertex3f(-0.5f, -0.3f, 0.0f);

		glEnd();

		fy1 = fy1 - 0.001f;

	}

	// D

	if (fy1 < 0.0f)
	{

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(0.0f, 0.0f, -4.0f);

		glBegin(GL_QUADS);

		glColor3f(fRed, fGreen, 0.0f);

		glVertex3f(0.3f, 0.3f, 0.0f);
		glVertex3f(-0.3f, 0.3f, 0.0f);
		glVertex3f(-0.3f, 0.2f, 0.0f);
		glVertex3f(0.3f, 0.2f, 0.0f);

		glVertex3f(0.3f, 0.2f, 0.0f);
		glVertex3f(0.2f, 0.2f, 0.0f);

		glColor3f(0.0f, fGreen, 0.0f);

		glVertex3f(0.2f, -0.3f, 0.0f);
		glVertex3f(0.3f, -0.3f, 0.0f);

		glVertex3f(0.3f, -0.3f, 0.0f);
		glVertex3f(-0.3f, -0.3f, 0.0f);
		glVertex3f(-0.3f, -0.2f, 0.0f);
		glVertex3f(0.3f, -0.2f, 0.0f);

		glColor3f(fRed, fGreen, 0.0f);

		glVertex3f(0.0f, 0.2f, 0.0f);
		glVertex3f(-0.1f, 0.2f, 0.0f);

		glColor3f(0.0f, fGreen, 0.0f);

		glVertex3f(-0.1f, -0.3f, 0.0f);
		glVertex3f(0.0f, -0.3f, 0.0f);

		fRed = fRed + 0.00015f;
		fGreen = fGreen + 0.0001f;

		glEnd();
	}

	// I

	if (fy1 < 0.0f)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(0.0f, fy2, -4.0f);

		glBegin(GL_QUADS);

		glColor3f(1.0f, 0.5f, 0.0f);

		glVertex3f(0.4f, 0.3f, 0.0f);
		glVertex3f(0.9f, 0.3f, 0.0f);
		glVertex3f(0.9f, 0.2f, 0.0f);
		glVertex3f(0.4f, 0.2f, 0.0f);

		glVertex3f(0.6f, 0.2f, 0.0f);
		glVertex3f(0.7f, 0.2f, 0.0f);

		glColor3f(0.0f, 0.5f, 0.0f);

		glVertex3f(0.7f, -0.2f, 0.0f);
		glVertex3f(0.6f, -0.2f, 0.0f);

		glVertex3f(0.4f, -0.3f, 0.0f);
		glVertex3f(0.9f, -0.3f, 0.0f);
		glVertex3f(0.9f, -0.2f, 0.0f);
		glVertex3f(0.4f, -0.2f, 0.0f);

		glEnd();

		fy2 = fy2 + 0.001f;
	}

	// A

	if (fy2 > 0.0f)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(fx2, 0.0f, -4.0f);

		glBegin(GL_QUADS);

		glColor3f(1.0f, 0.5f, 0.0f);
		glVertex3f(1.25f, 0.3f, 0.0f);
		glVertex3f(1.35f, 0.3f, 0.0f);

		glColor3f(0.0f, 0.5f, 0.0f);

		glVertex3f(1.1f, -0.3f, 0.0f);
		glVertex3f(1.0f, -0.3f, 0.0f);


		glColor3f(1.0f, 0.5f, 0.0f);
		glVertex3f(1.35f, 0.3f, 0.0f);
		glVertex3f(1.25f, 0.3f, 0.0f);

		glColor3f(0.0f, 0.5f, 0.0f);

		glVertex3f(1.4f, -0.3f, 0.0f);
		glVertex3f(1.5f, -0.3f, 0.0f);

		glEnd();

		fx2 = fx2 - 0.001f;
	}

}

//DrawTranslateIAFPlanes()

void DrawTranslateIAFPlanes(void)
{
	// Code


}

// Resize()

void Resize(int iWidth, int iHeight)
{
	// Code

	if (0 == iHeight)
		iHeight = 1;

	glViewport(0, 0, (GLsizei)iWidth, (GLsizei)iHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)iWidth / (GLfloat)iHeight, 0.1f, 100.0f);
}

void Update(void)
{
	// Code

	if (fx1 >= 0.0f)
		fx1 = 0.0f;

	if (fy1 <= 0.0f)
		fy1 = 0.0f;

	if (fy2 >= 0.0f)
		fy2 = 0.0f;

	if (fx2 <= 0.0f)
		fx2 = 0.0f;

	if (fRed > 1.0f)
		fRed = 1.0f;

	if (fGreen > 0.5f)
		fGreen = 0.5f;
}

// Uninitialize()

void Uninitialize(void)
{
	// Code

	if (true == gbFullScreen)
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd,
			HWND_TOP,
			0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED
		);

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
		fprintf(gpFile, "\n\nLogFile Closed Successfully...!!!\n");
		DestroyWindow(ghwnd);
	}
}
