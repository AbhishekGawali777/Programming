
// Header Files

#include"TwoPositionalLights.h"

// Global Variable Declarations

HDC   ghdc = NULL;
HWND  ghwnd = NULL;
FILE* gpFile = NULL;
HGLRC ghrc = NULL;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

bool gbFullScreen = false;
bool gbActiveWindow = false;
bool gbIsLightEnabled = false;

GLfloat ABG_lightAmbient0[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat ABG_lightDiffuse0[] = { 1.0f, 0.0f, 0.0f, 0.0f };
GLfloat ABG_lightSpecular0[] = { 1.0f, 0.0f, 0.0f, 0.0f };
GLfloat ABG_lightPosition0[] = { 2.0f, 0.0f, 0.0f, 1.0f };

GLfloat ABG_lightAmbient1[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat ABG_lightDiffuse1[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat ABG_lightSpecular1[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat ABG_lightPosition1[] = { -2.0f, 0.0f, 0.0f, 1.0f };

GLfloat ABG_materialAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat ABG_materialDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat ABG_materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat ABG_materialShininess = 128.0f;
GLfloat fAngle = 0.0f;

GLUquadric* quadric = NULL;

// WinMain()

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpSzCmdLine, INT iCmdShow)
{
	// Local Variable Declaration

	MSG		msg;
	HWND	hwnd;
	WNDCLASSEX WndClass;
	bool	bDone = false;
	TCHAR	szAppName[] = TEXT("LightAndMaterialWindow");

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

	if (fopen_s(&gpFile, "LogFile.txt", "w") != 0)
	{
		MessageBox(NULL, TEXT("LogFile Creation Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	else
	{
		fprintf(gpFile, "\n\nLogFile Created Successfully...!!!\n");
	}

	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szAppName,
		TEXT("Lights : Two Positional Lights"),
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

	// Game Loop

	while (bDone == false)
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
			//case 0x1B:
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;

		case 0x46:
		case 0x66:
			ToggleFullScreen();
			break;

		case 'L':
		case'l':

			if (gbIsLightEnabled == false)
			{
				glEnable(GL_LIGHTING);
				gbIsLightEnabled = true;
			}
			else
			{
				glDisable(GL_LIGHTING);
				gbIsLightEnabled = false;
			}

		default:
			break;
		}

		break;

	case WM_ERASEBKGND:
		return(0);

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		Uninitialize();
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return(DefWindowProc(hwnd, uiMessage, wParam, lParam));
}

// Initialize()

void Initialize(void)
{
	// Local Variable Declarations

	ghdc = GetDC(ghwnd);

	int iPixelFormatIndex;
	PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR) };

	// Code

	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = { sizeof(PIXELFORMATDESCRIPTOR) };
	pfd.nVersion = 1;
	pfd.cRedBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cGreenBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW;

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

	glShadeModel(GL_SMOOTH);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ABG_lightAmbient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, ABG_lightDiffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, ABG_lightSpecular0);
	glLightfv(GL_LIGHT0, GL_POSITION, ABG_lightPosition0);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ABG_lightAmbient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, ABG_lightDiffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, ABG_lightSpecular1);
	glLightfv(GL_LIGHT1, GL_POSITION, ABG_lightPosition1);
	glEnable(GL_LIGHT1);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ABG_materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ABG_materialDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ABG_materialSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, ABG_materialShininess);

	// Warm up call

	Resize(WIN_WIDTH, WIN_HEIGHT);
}

// Resize

void Resize(int iWidth, int iHeight)
{
	// Code

	if (iHeight == 0)
		iHeight = 1;

	glViewport(0, 0, (GLsizei)iWidth, (GLsizei)iHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)iWidth / (GLfloat)iHeight, 0.1f, 100.0f);
}

// ToggleFullScreen()

void ToggleFullScreen(void)
{
	// Local Variable Declararion

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
	// Code

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(0.0f, 0.0f, 4.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);
	glRotatef(fAngle, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);

		// Front

		glNormal3f(0.0f, 0.447214f, 0.894427f);
		glVertex3f(0.0f, 1.0f, 0.0f);
	
		glNormal3f(0.0f, 0.447214f, 0.894427f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
	
		glNormal3f(0.0f, 0.447214f, 0.894427f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		// Right
	
		glNormal3f(0.894427f, 0.447214f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
	
		glNormal3f(0.894427f, 0.447214f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
	
		glNormal3f(0.894427f, 0.447214f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		// Back


		glNormal3f(0.0f, 0.447214f, -0.894427f);
		glVertex3f(0.0f, 1.0f, 0.0f);
	
		glNormal3f(0.0f, 0.447214f, -0.894427f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
	
		glNormal3f(0.0f, 0.447214f, -0.894427f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		// Left

		glNormal3f(-0.894427f, 0.447214f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
	
		glNormal3f(-0.894427f, 0.447214f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
	
		glNormal3f(-0.894427f, 0.447214f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

	glEnd();

	SwapBuffers(ghdc);
}

// Update()

void Update(void)
{
	// Code
	
	fAngle += 1.0f;

	if (fAngle >= 360.0f)
		fAngle = 0.0f;

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

	if (quadric)
	{
		gluDeleteQuadric(quadric);
		quadric = NULL;
	}

	if (gpFile)
	{
		fprintf(gpFile, "\n\nLogFile Closed Successfully...!!!\n");
		DestroyWindow(ghwnd);
	}
}
