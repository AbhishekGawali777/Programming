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

GLuint ABG_SmileyTexture;

unsigned int iPressedDigit;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
	// Local Variable Declarations

	MSG msg;
	HWND hwnd;
	bool bDone = false;
	WNDCLASSEX WndClass;

	TCHAR szAppName[] = TEXT("TweekedSmilesWindow");

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
		TEXT("Tweeked Smilies"),
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
		case 49:			// Digit : 1
			iPressedDigit = 1;
			glEnable(GL_TEXTURE_2D);
			break;

		case 50:
			iPressedDigit = 2;
			glEnable(GL_TEXTURE_2D);
			break;

		case 51:
			iPressedDigit = 3;
			glEnable(GL_TEXTURE_2D);
			break;

		case 52:
			iPressedDigit = 4;
			glEnable(GL_TEXTURE_2D);
			break;

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

	LoadGLTexture(&ABG_SmileyTexture, MAKEINTRESOURCE(SMILEY_BITMAP));

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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

	DrawCube();

	SwapBuffers(ghdc);
}

void DrawCube(void)
{
	// Code

	glTranslatef(0.0f, 0.0f, -5.0f);
	glBindTexture(GL_TEXTURE_2D, ABG_SmileyTexture);

	if (1 == iPressedDigit)
	{
		glBegin(GL_QUADS);

		glColor3f(1.0f, 1.0f, 1.0f);
		
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);

		glEnd();
	}
	else if (2 == iPressedDigit)  // Wrapping and Clamping
	{
		glBegin(GL_QUADS);

		glColor3f(1.0f, 1.0f, 1.0f);

		glTexCoord2d(0.5f, 0.5f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		
		glTexCoord2d(0.0f, 0.5f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		
		glTexCoord2d(0.5f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);

		glEnd();
	}
	else if (3 == iPressedDigit)  // Repeat Mode /  Timing Mode /  Tiling
	{
		glBegin(GL_QUADS);

		glColor3f(1.0f, 1.0f, 1.0f);
		
		glTexCoord2d(2.0f, 2.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		
		glTexCoord2d(0.0f, 2.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		
		glTexCoord2d(2.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);

		glEnd();
	}
	else if (4 == iPressedDigit)
	{
		glBegin(GL_QUADS);

		glColor3f(1.0f, 1.0f, 1.0f);
		
		glTexCoord2d(0.5f, 0.5f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		
		glTexCoord2d(0.5f, 0.5f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		
		glTexCoord2d(0.5f, 0.5f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		
		glTexCoord2d(0.5f, 0.5f);
		glVertex3f(1.0f, -1.0f, 0.0f);

		glEnd();
	}
	else
	{
		glBegin(GL_QUADS);

		glColor3f(1.0f, 1.0f, 1.0f);

		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);

		glEnd();
	}
}

// LoadGlTextures()

bool LoadGLTexture(GLuint* Texture, TCHAR ResourceID[])
{
	// Variable Declarations

	bool bResult = false;

	HBITMAP hBitmap = NULL;
	BITMAP bmp;

	// Code

	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), ResourceID, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

	if (hBitmap)
	{
		bResult = true;

		GetObject(hBitmap, sizeof(BITMAP), &bmp);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glGenTextures(1, Texture);
		glBindTexture(GL_TEXTURE_2D, *Texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);

		DeleteObject(hBitmap);
	}

	return(bResult);

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

	glDeleteTextures(1, &ABG_SmileyTexture);

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
