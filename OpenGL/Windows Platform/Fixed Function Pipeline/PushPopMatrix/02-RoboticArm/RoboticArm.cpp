// Header Files

#include"MyHeader.h"

// Global Variables

RECT rcRect;
DWORD dwStyle;
HDC ghdc = NULL;
HWND ghwnd = NULL;
HGLRC ghrc = NULL;
FILE* gpFile = NULL;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

bool gbFullScreen = false;
bool gbActiveWindow = false;

int ABG_iElbow = 0;
int ABG_iShoulder = 0;

GLUquadric* quadric = NULL;

// WinMain()

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Local Variable Declarations

	MSG msg;
	HWND hwnd;
	bool bDone = false;
	WNDCLASSEX WndClass;
	const TCHAR* szAppName = TEXT("Robotic Arm Window");

	// Code

	if (fopen_s(&gpFile, "LogFile.txt", "w") != 0)
	{
		MessageBox(NULL, TEXT("File Creation Failed"), TEXT("ERROR"), MB_OKCANCEL | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}
	else
		fprintf(gpFile, "LogFile Created Successfully..!!!\n\n");

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.lpszClassName = szAppName;
	WndClass.lpszMenuName = NULL;
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	WndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx Failed"), TEXT("ERROR"), MB_OKCANCEL | MB_ICONERROR);
		exit(EXIT_FAILURE);
	}

	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcRect, 0);

	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szAppName,
		TEXT("Robotic Arm"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		/*	(rcRect.right / 4) + rcRect.left,
			(rcRect.bottom / 4) + rcRect.top,
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
		MessageBox(NULL, TEXT("CreateWindowEx Failed"), TEXT("ERROR"), MB_OKCANCEL | MB_ICONERROR);
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

	case WM_ERASEBKGND:
		return(0);

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
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

	case WM_CHAR:

		switch (wParam)
		{
		case 'S':

			ABG_iShoulder = (ABG_iShoulder + 3) % 360;
			break;

		case 's':

			ABG_iShoulder = (ABG_iShoulder - 3) % 360;
			break;

		case 'E':

			ABG_iElbow = (ABG_iElbow + 3) % 360;
			break;

		case 'e':

			ABG_iElbow = (ABG_iElbow - 3) % 360;
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
	// Local Variables

	int iPixelFormatIndex;
	PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR) };

	// Code

	ghdc = GetDC(ghwnd);

	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

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
		fprintf(gpFile, "ChoosePixelFormat Failed..!!!\n\n");
		DestroyWindow(ghwnd);
	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		fprintf(gpFile, "SetPixelFormat Failed..!!!\n\n");
		DestroyWindow(ghwnd);
	}

	ghrc = wglCreateContext(ghdc);

	if (NULL == ghrc)
	{
		fprintf(gpFile, "wglCreateContext Failed..!!!\n\n");
		DestroyWindow(ghwnd);
	}

	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fprintf(gpFile, "wglMakeCurrent Failed..!!!\n\n");
		DestroyWindow(ghwnd);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_SMOOTH);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// Warm-up call 

	Resize(WIN_WIDTH, WIN_HEIGHT);
	//Resize(rcRect.right / 2, rcRect.bottom / 2);
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

// Display()

void Display(void)
{
	// Code

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// By Default for GL_FRONT_AND_BACK Mode is GL_FILL

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw Shoulder

	gluLookAt(0.0f, 0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glPushMatrix();

		glRotatef((GLfloat)ABG_iShoulder, 0.0f, 0.0f, 1.0f);
		glTranslatef(1.0f, 0.0f, 0.0f);

		glPushMatrix();

			glScalef(2.0f, 0.5f, 0.0f);
			glColor3f(0.5f, 0.35f, 0.05f);
			quadric = gluNewQuadric();
			gluSphere(quadric, 0.5f, 10, 10);
	
		glPopMatrix();

		// Draw Arm

		glPushMatrix();

			glTranslatef(1.0f, 0.0f, 0.0f);
			glRotatef((GLfloat)ABG_iElbow, 0.0f, 0.0f, 1.0f);
			glTranslatef(1.0f, 0.0f, 0.0f);

			glPushMatrix();
				
				glScalef(2.2f, 0.5f, 0.0f);
				glColor3f(0.5f, 0.35f, 0.05f);
				quadric = gluNewQuadric();
				gluSphere(quadric, 0.5f, 10, 10);

			glPopMatrix();
	
	glPopMatrix();

	SwapBuffers(ghdc);
}

// Update()

void Update(void)
{
	// Code


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
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd, HWND_TOP,
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
		SetWindowPos(ghwnd, HWND_TOP,
			0, 0, 0, 0,
			SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED
		);

		ShowCursor(TRUE);
		gbFullScreen = false;
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
		SetWindowPos(ghwnd, HWND_TOP,
			0, 0, 0, 0,
			SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED
		);

		ShowCursor(TRUE);
		gbFullScreen = false;
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
		ghdc = NULL;
	}

	if (gpFile)
	{
		fprintf(gpFile, "LogFile Closed SuccessFully...!!!\n\n");
		fclose(gpFile);
		gpFile = NULL;
		DestroyWindow(ghwnd);
	}
}
