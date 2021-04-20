// Header Files

#include"MyHeader.h"

// Global Variable Declarations

DWORD dwStyle;
RECT rcRect;
HDC ghdc = NULL;
HWND ghwnd = NULL;
HGLRC ghrc = NULL;
FILE* gpFile = NULL;

WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

bool gbFullScreen = false;
bool gbActiveWindow = false;
bool gbIsLightEnabled = false;

GLfloat ABG_lightAmbientZero[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat ABG_lightDiffuseZero[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat ABG_lightSpecularZero[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat ABG_lightPositionZero[] = { 0.0f, 0.0f, 0.0f, 1.0f };  // Positional Light


GLfloat ABG_lightAmbientOne[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat ABG_lightDiffuseOne[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat ABG_lightSpecularOne[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat ABG_lightPositionOne[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat ABG_lightAmbientTwo[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat ABG_lightDiffuseTwo[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat ABG_lightSpecularTwo[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat ABG_lightPositionTwo[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat ABG_materialAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat ABG_materialDiffuse[] = { 0.5f, 0.2f, 0.7f, 1.0f };
GLfloat ABG_materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat ABG_materialShininess = 128.0f;

GLfloat ABG_LightAngle0 = 0.0f;
GLfloat ABG_LightAngle1 = 0.0f;
GLfloat ABG_LightAngle2 = 0.0f;

GLUquadric* quadric = NULL;

// WinMain()

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Local Variable Declarations

	MSG msg;
	bool bDone = false;
	HWND hwnd;
	WNDCLASSEX WndClass;
	TCHAR szAppName[] = { TEXT("AlbedoWindow") };

	// Code

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.lpszClassName = szAppName;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszMenuName = NULL;
	WndClass.hInstance = hInstance;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	WndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	if (!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClasssEx Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}

	if (fopen_s(&gpFile, "LogFile.txt", "w") != 0)
	{
		MessageBox(NULL, TEXT("LogFile Creation Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	else
		fprintf(gpFile, "LogFile Created Successfully ..!!!\n\n");

	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szAppName,
		TEXT("Light : Three Lights"),
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE,
		100, 100, WIN_WIDTH, WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (NULL == hwnd)
	{
		MessageBox(NULL, TEXT("CreateWindowEx Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
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
			if (gbActiveWindow == true)
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

	case WM_ERASEBKGND:
		return(0);

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
	// Local Variable Declaration

	int iPixelFormatIndex;
	PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR) };

	// Code

	ghdc = GetDC(ghwnd);

	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = { sizeof(PIXELFORMATDESCRIPTOR) };
	pfd.nVersion = 1;
	pfd.cRedBits = 8;
	pfd.cBlueBits = 8;
	pfd.cGreenBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);

	if (0 == iPixelFormatIndex)
	{
		fprintf(gpFile, "ChoosePixelFormat() failed\n\n");
		DestroyWindow(ghwnd);
	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		fprintf(gpFile, "SetPixelFormat() failed\n\n");
		DestroyWindow(ghwnd);
	}

	ghrc = wglCreateContext(ghdc);

	if (NULL == ghrc)
	{
		fprintf(gpFile, "wglCreateContext() failed\n\n");
		DestroyWindow(ghwnd);
	}

	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fprintf(gpFile, "wglMakeCurrent() failed\n\n");
		DestroyWindow(ghwnd);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_SMOOTH);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// Initialization of light 

	GLfloat LightAngle0 = 0.0f;
	glLightfv(GL_LIGHT0, GL_AMBIENT, ABG_lightAmbientZero);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, ABG_lightDiffuseZero);
	glLightfv(GL_LIGHT0, GL_SPECULAR, ABG_lightSpecularZero);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ABG_lightAmbientOne);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, ABG_lightDiffuseOne);
	glLightfv(GL_LIGHT1, GL_SPECULAR, ABG_lightSpecularOne);
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT2, GL_AMBIENT, ABG_lightAmbientTwo);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, ABG_lightDiffuseTwo);
	glLightfv(GL_LIGHT2, GL_SPECULAR, ABG_lightSpecularTwo);
	glEnable(GL_LIGHT2);

	// Material Initialization

	glMaterialfv(GL_FRONT, GL_AMBIENT, ABG_materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ABG_materialDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ABG_materialSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, ABG_materialShininess);

	// warm up  call

	Resize(WIN_WIDTH, WIN_HEIGHT);
}

// Resize()

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

	glTranslatef(0.0f, 0.0f, -0.55f);

	glPushMatrix();

	gluLookAt(0.0f, 0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glPushMatrix();

	glRotatef(ABG_LightAngle0, 1.0f, 0.0f, 0.0f);
	ABG_lightPositionZero[1] = ABG_LightAngle0;
	glLightfv(GL_LIGHT0, GL_POSITION, ABG_lightPositionZero);

	glPopMatrix();

	glPushMatrix();

	glRotatef(ABG_LightAngle1, 0.0f, 1.0f, 0.0f);
	ABG_lightPositionOne[0] = ABG_LightAngle1;
	glLightfv(GL_LIGHT1, GL_POSITION, ABG_lightPositionOne);

	glPopMatrix();

	glPushMatrix();

	glRotatef(ABG_LightAngle2, 0.0f, 0.0f, 1.0f);
	ABG_lightPositionTwo[0] = ABG_LightAngle2;
	glLightfv(GL_LIGHT2, GL_POSITION, ABG_lightPositionTwo);

	glPopMatrix();

	glTranslatef(0.0f, 0.0f, -1.0f);


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	quadric = gluNewQuadric();
	gluSphere(quadric, 1.0f, 70, 70);

	glPopMatrix();

	SwapBuffers(ghdc);

	//lightPositionZero[0] = LightAngle0;
	//lightPositionOne[1] = LightAngle1;		// Gimble lock
	//lightPositionTwo[2] = LightAngle2;

}

void Update(void)
{
	// Code

	ABG_LightAngle0 = ABG_LightAngle0 + 1.0f;

	if (ABG_LightAngle0 >= 360.0f)
		ABG_LightAngle0 = 0.0f;

	ABG_LightAngle1 = ABG_LightAngle1 + 1.0f;

	if (ABG_LightAngle1 >= 360.0f)
		ABG_LightAngle1 = 0.0f;

	ABG_LightAngle2 = ABG_LightAngle2 + 1.0f;

	if (ABG_LightAngle2 >= 360.0f)
		ABG_LightAngle2 = 0.0f;
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

	if (wglCreateContext(ghdc) == ghrc)
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
	}

	if (quadric)
	{
		gluDeleteQuadric(quadric);
		quadric = NULL;
	}

	if (gpFile)
	{
		fprintf(gpFile, "\n\nLogFile Closed Successfully...!!!\n");
		gpFile = NULL;
		DestroyWindow(ghwnd);
	}
}
