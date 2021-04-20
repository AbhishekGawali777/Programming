//  Header Files

#include"MyHeader.h"

// Global Variable Declarations

DWORD dwStyle;
HDC ghdc = NULL;
HWND ghwnd = NULL;
HGLRC ghrc = NULL;
FILE* gpFile = NULL;

WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

bool gbActiveWindow = false;
bool gbFullScreen = false;

GLubyte CheckImage[CHECK_IMAGE_HEIGHT][CHECK_IMAGE_WIDTH][4];
GLuint TexImage;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
	// Local Variable Declarations

	MSG msg;
	HWND hwnd;
	bool bDone = false;
	WNDCLASSEX WndClass;

	TCHAR szAppName[] = TEXT("CheckerBoardWindow");

	// Code

	if (fopen_s(&gpFile, "LogFile.txt", "w") != 0)
	{
		MessageBox(NULL, TEXT("LogFile Creation Failed...!!!"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	else
		fprintf(gpFile, "\nLogFile Created Successfully...!!!\n\n");


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
		fprintf(gpFile, "RegisterClassEx Failed\n");
		exit(EXIT_FAILURE);
	}

	hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		szAppName,
		TEXT("Checker Board"),
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE,
		100, 100,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (NULL == hwnd)
	{
		fprintf(gpFile, "CreateWindowEx Failed\n");
		exit(EXIT_FAILURE);
	}

	ghwnd = hwnd;

	Initialize();
	ShowWindow(hwnd, iCmdShow);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	// Game Loop

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

	case WM_ERASEBKGND:

		return(0);

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
			glDisable(GL_TEXTURE_2D);
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
	// Variable Declarations

	int iPixelFormatIndex;
	PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR) };

	// Code

	ZeroMemory(&pfd, sizeof(pfd));

	ghdc = GetDC(ghwnd);

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
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
		fprintf(gpFile, "ChoosePixelFormat Failed\n");
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

	glShadeModel(GL_SMOOTH);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);

	LoadGLTexture();

	// Warm-up Call

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
	gluPerspective(60.0f, (GLfloat)iWidth / (GLfloat)iHeight, 0.1f, 30.0f);
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

	DrawCheckerBoard();

	SwapBuffers(ghdc);
}

void DrawCheckerBoard(void)
{
	// Code

	glTranslatef(0.0f, 0.0f, -3.6f);
	
	glBegin(GL_QUADS);

		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(-2.0f, -1.0f, 0.0f);
		
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(-2.0f, 1.0f, 0.0f);
		
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(0.0f, -1.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);

		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(2.41421f, 1.0f, -1.41421f);
		
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(2.41421f, -1.0f, -1.41421f);

	glEnd();
}

// LoadGlTextures()

void LoadGLTexture(void)
{
	// Code

	MakeCheckImage();
	glGenTextures(1, &TexImage);
	glBindTexture(GL_TEXTURE_2D, TexImage);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Texture wrap in Horizontal Direction
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Texture wrap in Vertical Direction
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, CHECK_IMAGE_WIDTH, CHECK_IMAGE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, CheckImage);
	// MipMap level  = 0 : OpenGL should decide the MipMap.
	// 4 : GL_RGBA
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

// MakeCheckImage()

void MakeCheckImage(void)
{
	// Variable Declarations

	int i, j, c;

	// Code

	for (i = 0; i < CHECK_IMAGE_HEIGHT; i++)
	{
		for (j = 0; j < CHECK_IMAGE_WIDTH; j++)
		{
			c = (((i & 0x8) == 0) ^ ((j & 0x8) == 0)) * 255;

			CheckImage[i][j][0] = (GLubyte)c;
			CheckImage[i][j][1] = (GLubyte)c;
			CheckImage[i][j][2] = (GLubyte)c;
			CheckImage[i][j][3] = 255;
		}
	}
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
