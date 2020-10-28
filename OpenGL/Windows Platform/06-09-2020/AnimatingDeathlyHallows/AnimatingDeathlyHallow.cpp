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

GLfloat x = 2.0f;
GLfloat y = -2.0f;
GLfloat fRotationAngle = 0.0f;

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
		TEXT("Animating Deathly Hallows"),
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

void Display(void)
{
	// Function Delcarations

	void DrawTriangle(void);
	void DrawIncircle(void);
	void DrawVerticalLine(void);


	// Code

	glClear(GL_COLOR_BUFFER_BIT);

	// Deathly Hallows

	if (x && y)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		DrawTriangle();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		DrawIncircle();
	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		DrawVerticalLine();
	}

	SwapBuffers(ghdc);
}

void DrawTriangle(void)
{
	glTranslatef(x, y, -3.0f);
	glRotatef(fRotationAngle, 0.0f, 1.0f, 0.0f);

	glBegin(GL_LINES);

	glColor3f(1.0f, 1.0f, 0.0f);

	glVertex3f(0.0f, COORDINATE, 0.0f);
	glVertex3f(-COORDINATE, -COORDINATE, 0.0f);

	glVertex3f(-COORDINATE, -COORDINATE, 0.0f);
	glVertex3f(COORDINATE, -COORDINATE, 0.0f);

	glVertex3f(COORDINATE, -COORDINATE, 0.0f);
	glVertex3f(0.0f, COORDINATE, 0.0f);

	glEnd();
}

void DrawIncircle(void)
{
	// Local Variable Declarations

	GLfloat fArea = 0.0f;
	GLfloat fSide_A = 0.0f;
	GLfloat fSide_B = 0.0f;
	GLfloat fSide_C = 0.0f;
	GLfloat fRadius = 0.0f;
	GLfloat fPerimeter = 0.0f;
	GLfloat fSemiperimeter = 0.0f;
	GLfloat fxIncenter = 0.0f;
	GLfloat fyIncenter = 0.0f;

	// Code

	// Sides Of Triangle

	fSide_A = sqrtf((powf(COORDINATE + COORDINATE, 2)));
	fSide_B = sqrtf((powf(COORDINATE, 2)) + (powf((COORDINATE + COORDINATE), 2)));
	fSide_C = sqrtf((powf(COORDINATE, 2)) + (powf((COORDINATE + COORDINATE), 2)));

	fPerimeter = fSide_A + fSide_B + fSide_C;

	fSemiperimeter = fPerimeter / 2;

	fArea = sqrtf(fSemiperimeter * (fSemiperimeter - fSide_A) * (fSemiperimeter - fSide_B) * (fSemiperimeter - fSide_C));

	fRadius = fArea / fSemiperimeter;

	fxIncenter = ((fSide_A * 0) + (fSide_B * (-COORDINATE)) + (fSide_C * COORDINATE)) / fPerimeter;
	fyIncenter = ((fSide_A * COORDINATE) + (fSide_B * (-COORDINATE)) + (fSide_C * (-COORDINATE))) / fPerimeter;

	if(x >= fxIncenter /*&& y <= fyIncenter*/)
		glTranslatef(-x, y, -3.0f);
	else
		glTranslatef(fxIncenter, fyIncenter, -3.0f);

	glRotatef(fRotationAngle, 0.0f, 1.0f, 0.0f);

	glBegin(GL_POINTS);


	for (GLfloat fAngle = 0.0f; fAngle <= 2 * PI; fAngle = fAngle + 0.01f)
	{
		glVertex3f(((GLfloat)cos(fAngle) * fRadius), ((GLfloat)sin(fAngle) * fRadius), 0.0f);
	}

	glEnd();

}

void DrawVerticalLine(void)
{
	// Local Variable

	static GLfloat yLine = 2.0f;

	// Code

	glTranslatef(0.0, yLine, -3.0f);
	glRotatef(fRotationAngle, 0.0f, 1.0f, 0.0f);

	glBegin(GL_LINES);

	glVertex3f(0.0f, COORDINATE, 0.0f);
	glVertex3f(0.0f, -COORDINATE, 0.0f);

	glEnd();

	if (yLine <= 0.0f)
		yLine = 0.0f;

	yLine = yLine - 0.01f;
}

// Update()

void Update(void)
{
	// Code

	if (fRotationAngle >= 360.0f)
		fRotationAngle = 0.0f;

	if (y >= 0.0f)
		y = 0.0f;

	if (x <= 0.0f)
		x = 0.0f;

	x = x - 0.01f;
	y = y + 0.01f;
	fRotationAngle = fRotationAngle + 2.0f;
}

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