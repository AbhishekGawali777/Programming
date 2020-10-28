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

bool gbFullScreen	= false;
bool gbActiveWindow = false;

GLfloat ScaleMatrix[16];
GLfloat IdentityMatrix[16];
GLfloat TranslationMatrix[16];

GLfloat RotationMatrix_X[16];
GLfloat RotationMatrix_Y[16];
GLfloat RotationMatrix_Z[16];

GLfloat fAngle = 0.0f;
GLfloat fRotationAngle_rad = 0.0f;

// WinMain()

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Local Variable Declarations

	MSG msg;
	bool bDone = false;
	HWND hwnd;
	WNDCLASSEX WndClass;
	TCHAR szAppName[] = { TEXT("MyWindow") };

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

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rcRect, 0);

	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szAppName,
		TEXT("Rotating Cube Using Matrix"),
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE,
		/*rcRect.right / 4 + rcRect.left,
		rcRect.bottom / 4 + rcRect.top,
		rcRect.right / 2,
		rcRect.bottom / 2,*/
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

	if(NULL == ghrc)
	{
		fprintf(gpFile, "wglCreateContext() failed\n\n");
		DestroyWindow(ghwnd);
	}

	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fprintf(gpFile, "wglMakeCurrent() failed\n\n");
		DestroyWindow(ghwnd);
	}

	// IdentityMatrix Initialization

	IdentityMatrix[0] = 1.0f;
	IdentityMatrix[1] = 0.0f;
	IdentityMatrix[2] = 0.0f;
	IdentityMatrix[3] = 0.0f;
	IdentityMatrix[4] = 0.0f;
	IdentityMatrix[5] = 1.0f;
	IdentityMatrix[6] = 0.0f;
	IdentityMatrix[7] = 0.0f;
	IdentityMatrix[8] = 0.0f;
	IdentityMatrix[9] = 0.0f;
	IdentityMatrix[10] = 1.0f;
	IdentityMatrix[11] = 0.0f;
	IdentityMatrix[12] = 0.0f;
	IdentityMatrix[13] = 0.0f;
	IdentityMatrix[14] = 0.0f;
	IdentityMatrix[15] = 1.0f;

	// TranslationMatrix Initialization

	TranslationMatrix[0] = 1.0f;
	TranslationMatrix[1] = 0.0f;
	TranslationMatrix[2] = 0.0f;
	TranslationMatrix[3] = 0.0f;
	TranslationMatrix[4] = 0.0f;
	TranslationMatrix[5] = 1.0f;
	TranslationMatrix[6] = 0.0f;
	TranslationMatrix[7] = 0.0f;
	TranslationMatrix[8] = 0.0f;
	TranslationMatrix[9] = 0.0f;
	TranslationMatrix[10] = 1.0f;
	TranslationMatrix[11] = 0.0f;
	TranslationMatrix[12] = 0.0f;  // tx
	TranslationMatrix[13] = 0.0f;  // ty
	TranslationMatrix[14] = -5.0f; // tz
	TranslationMatrix[15] = 1.0f;

	// ScaleMatrix Initialization

	ScaleMatrix[0] = 0.75f;
	ScaleMatrix[1] = 0.0f;
	ScaleMatrix[2] = 0.0f;
	ScaleMatrix[3] = 0.0f;
	ScaleMatrix[4] = 0.0f;
	ScaleMatrix[5] = 0.75f;
	ScaleMatrix[6] = 0.0f;
	ScaleMatrix[7] = 0.0f;
	ScaleMatrix[8] = 0.0f;
	ScaleMatrix[9] = 0.0f;
	ScaleMatrix[10] = 0.75f;
	ScaleMatrix[11] = 0.0f;
	ScaleMatrix[12] = 0.0f;
	ScaleMatrix[13] = 0.0f;
	ScaleMatrix[14] = 0.0f;
	ScaleMatrix[15] = 1.0f;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_SMOOTH);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// warm up  call

	Resize(WIN_WIDTH, WIN_HEIGHT);
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


// Resize

void Resize(int iWidth, int iHeight)
{
	// Code

	if (iHeight == 0)
		iHeight = 1;

	glViewport(0, 0, (GLsizei)iWidth, (GLsizei)iHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(IdentityMatrix);

	gluPerspective(45.0f, (GLfloat)iWidth / (GLfloat)iHeight, 0.1f, 100.0f);
}

// Display()

void Display(void)
{
	// Code
	fprintf(gpFile, "Display()");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(IdentityMatrix);
	glMultMatrixf(TranslationMatrix);

	//glRotatef(fAngle, 1.0f, 1.0f, 1.0f);
	fRotationAngle_rad = fAngle * (M_PI / 180.0f);

	// X-Rotation Matrix

	RotationMatrix_X[0] = 1.0f;
	RotationMatrix_X[1] = 0.0f;
	RotationMatrix_X[2] = 0.0f;
	RotationMatrix_X[3] = 0.0f;
	RotationMatrix_X[4] = 0.0f;
	RotationMatrix_X[5] = cosf(fRotationAngle_rad);
	RotationMatrix_X[6] = sinf(fRotationAngle_rad);
	RotationMatrix_X[7] = 0.0f;
	RotationMatrix_X[8] = 0.0f;
	RotationMatrix_X[9] = -sinf(fRotationAngle_rad);
	RotationMatrix_X[10] = cosf(fRotationAngle_rad);
	RotationMatrix_X[11] = 0.0f;
	RotationMatrix_X[12] = 0.0f;
	RotationMatrix_X[13] = 0.0f;
	RotationMatrix_X[14] = 0.0f;
	RotationMatrix_X[15] = 1.0f;

	// Y-Rotation Matrix

	RotationMatrix_Y[0] = cosf(fRotationAngle_rad);
	RotationMatrix_Y[1] = 0.0f;
	RotationMatrix_Y[2] = -sinf(fRotationAngle_rad);
	RotationMatrix_Y[3] = 0.0f;
	RotationMatrix_Y[4] = 0.0f;
	RotationMatrix_Y[5] = 1.0f;
	RotationMatrix_Y[6] = 0.0f;
	RotationMatrix_Y[7] = 0.0f;
	RotationMatrix_Y[8] = sinf(fRotationAngle_rad);
	RotationMatrix_Y[9] = 0.0f;
	RotationMatrix_Y[10] = cosf(fRotationAngle_rad);
	RotationMatrix_Y[11] = 0.0f;
	RotationMatrix_Y[12] = 0.0f;
	RotationMatrix_Y[13] = 0.0f;
	RotationMatrix_Y[14] = 0.0f;
	RotationMatrix_Y[15] = 1.0f;

	// Z-Rotation Matrix

	RotationMatrix_Z[0] = cosf(fRotationAngle_rad);
	RotationMatrix_Z[1] = sinf(fRotationAngle_rad);
	RotationMatrix_Z[2] = 0.0f;
	RotationMatrix_Z[3] = 0.0f;
	RotationMatrix_Z[4] = -sinf(fRotationAngle_rad);
	RotationMatrix_Z[5] = cosf(fRotationAngle_rad);
	RotationMatrix_Z[6] = 0.0f;
	RotationMatrix_Z[7] = 0.0f;
	RotationMatrix_Z[8] = 0.0f;
	RotationMatrix_Z[9] = 0.0f;
	RotationMatrix_Z[10] = 1.0f;
	RotationMatrix_Z[11] = 0.0f;
	RotationMatrix_Z[12] = 0.0f;
	RotationMatrix_Z[13] = 0.0f;
	RotationMatrix_Z[14] = 0.0f;
	RotationMatrix_Z[15] = 1.0f;

	// Rotation

	glMultMatrixf(RotationMatrix_X);
	glMultMatrixf(RotationMatrix_Y);
	glMultMatrixf(RotationMatrix_Z);


	DrawCube3D();

	SwapBuffers(ghdc);

}

// DrawCube3D()

void DrawCube3D(void)
{
	// Code

	glBegin(GL_QUADS);

	// Front

	glColor3f(1.0f, 0.0f, 0.0f);

	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Right

	glColor3f(0.0f, 1.0f, 0.0f);

	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Back

	glColor3f(0.0f, 0.0f, 1.0f);

	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	// Left

	glColor3f(0.0f, 1.0f, 1.0f);

	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Top

	glColor3f(1.0f, 0.0f, 1.0f);

	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom

	glColor3f(1.0f, 1.0f, 0.0f);

	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glEnd();
}

void Update(void)
{
	// Code

	if (fAngle >= 360.0f)
		fAngle = 0.0f;

	fAngle = fAngle + 1.0f;
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

	if (gpFile)
	{
		fprintf(gpFile, "\n\nLogFile Closed Successfully...!!!\n");
		gpFile = NULL;
		DestroyWindow(ghwnd);
	}
}
