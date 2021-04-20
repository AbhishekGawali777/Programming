
// Header Files

#include"OrthographicProjection.h"
#include"vmath.h"

using namespace vmath;

// enum
enum

{
	ABG_ATTRIBUTE_POSITION = 0,
	ABG_ATTRIBUTE_COLOR,
	ABG_ATTRIBUTE_NORMAL,
	ABG_ATTRIBUTE_TEXTURE0
};

// Global Variable Declarations

DWORD			dwStyle;
HDC				ghdc = NULL;
HWND			ghwnd = NULL;
HGLRC			ghrc = NULL;
FILE* gpLogFile = NULL;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

bool gbFullScreen = false;
bool gbActiveWindow = false;

GLuint gVertexShaderObject;
GLuint gFragmentShaderObject;
GLuint gShaderProgramObject;

GLuint gVao;
GLuint gVbo;
GLuint gMVPUniform;

mat4 gOrthographicProjectionMtrix;

// WinMain()

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
	// Local Variable Declaration


	MSG			msg;
	HWND		hwnd;
	WNDCLASSEX	WndClass;
	bool		bDone = false;
	TCHAR		szAppName[] = { TEXT("BlueScreenWindow") };

	// Code
// Log File Creation

	if (fopen_s(&gpLogFile, "LogFile.txt", "w"))
	{
		MessageBox(NULL, TEXT("Cannot Create Log File"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	else
	{
		fprintf(gpLogFile, "Log File Created Successfully...!!!\n\n");
	}

	// Initializing Custom Window Class.

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = szAppName;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	WndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}

	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szAppName,
		TEXT("Orthographic Projection"),
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

	ShowWindow(hwnd, nCmdShow);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	Initialize();

	while (bDone == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{

			if (msg.message == WM_QUIT)
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
			}
		}
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uiMessage, WPARAM wParam, LPARAM lParam)
{
	// Code

	switch (uiMessage)
	{
	case WM_ACTIVATE:
		if (HIWORD(wParam) == 0)
			gbActiveWindow = true;
		else
			gbActiveWindow = false;

		break;

	case WM_ERASEBKGND:
		return(0);
		break;

	case WM_SIZE:
		Resize(LOWORD(lParam), HIWORD(lParam));
		break;

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

void ToggleFullScreen(void)
{
	// Local Variable Declarations

	MONITORINFO mi = { sizeof(MONITORINFO) };


	// Code

	if (gbFullScreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);

		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
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
			0,
			0,
			0,
			0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED
		);

		ShowCursor(TRUE);
		gbFullScreen = false;
	}
}

void Initialize(void)
{
	// Local Variable Declarations

	int						iPixelFormatIndex;
	PIXELFORMATDESCRIPTOR	pfd;

	// Code

	ghdc = GetDC(ghwnd);

	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);

	if (0 == iPixelFormatIndex)
	{
		fprintf(gpLogFile, "ChoosePixelFormat() Failed\n");
		DestroyWindow(ghwnd);
	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		fprintf(gpLogFile, "SetPixelFormat() Failed\n");
		DestroyWindow(ghwnd);
	}

	ghrc = wglCreateContext(ghdc);

	if (NULL == ghrc)
	{
		fprintf(gpLogFile, "wglCreateContext() Failed\n");
		DestroyWindow(ghwnd);
	}

	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fprintf(gpLogFile, "wglMakeCurrent() Failed\n");
		DestroyWindow(ghwnd);
	}

	GLenum glew_error = glewInit();

	if (glew_error != GLEW_OK)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	// OpenGL Related Logs
	fprintf(gpLogFile, "******************************************************************************\n");
	fprintf(gpLogFile, "\nOpenGL Vendor		: %s\n", glGetString(GL_VENDOR));
	fprintf(gpLogFile, "\nOpenGL Renderer		: %s\n", glGetString(GL_RENDERER));
	fprintf(gpLogFile, "\nOpenGL Version		: %s\n", glGetString(GL_VERSION));
	fprintf(gpLogFile, "\nGLSL Version		: %s\n", glGetString(GL_VENDOR));
	fprintf(gpLogFile, "\n******************************************************************************\n\n");

	/* Vertex Shader */

	gVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	// Provide Source Code to Shader

	const GLchar* vertexShaderSourceCode =
		"#version 450"\
		"\n"\
		"in vec4 vPosition;"\
		"uniform mat4 u_mvp_matrix;"\
		"void main(void)"\
		"\n"\
		"{"\
		"gl_Position = u_mvp_matrix * vPosition;"\
		"}";

	glShaderSource(gVertexShaderObject, 1, (const GLchar**)&vertexShaderSourceCode, NULL);

	// Compile Shader

	glCompileShader(gVertexShaderObject);

	GLint iInfoLogLength = 0;
	GLint iShaderCompiledStatus = 0;
	char* szInfoLog = NULL;
	glGetShaderiv(gVertexShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);

	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(gVertexShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);

		if (iInfoLogLength > 0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);

			if (NULL != szInfoLog)
			{
				GLsizei written;
				glGetShaderInfoLog(gVertexShaderObject, iInfoLogLength, &written, szInfoLog);
				fprintf(gpLogFile, "Vertex Shader Compilation Log : %s \n", szInfoLog);
				free(szInfoLog);
				Uninitialize();
				exit(0);
			}
		}
	}

	/* Fragment Shader  */

	gFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	// provide shource code to shader

	const GLchar* fragmantShaderSourceCode =
		"#version 450"\
		"\n"\
		"out vec4 FragColor;"\
		"void main(void)"\
		"\n"\
		"{"\
		"FragColor = vec4(1.0, 1.0, 1.0, 1.0);"\
		"}";

	glShaderSource(gFragmentShaderObject, 1, (const GLchar**)&fragmantShaderSourceCode, NULL);

	// Compile Shader

	glCompileShader(gFragmentShaderObject);
	
	glGetShaderiv(gFragmentShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);

	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(gFragmentShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);

		if (iInfoLogLength > 0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);

			if (NULL != szInfoLog)
			{
				GLsizei written;
				glGetShaderInfoLog(gFragmentShaderObject, iInfoLogLength, &written, szInfoLog);
				fprintf(gpLogFile, "Vertex Shader Compilation Log : %s \n", szInfoLog);
				free(szInfoLog);
				Uninitialize();
				exit(0);
			}
		}
	}
	//glShaderSource(gFragmentShaderObject, 1, (const GLchar**)&fragmantShaderSourceCode, NULL);
	

	/********* SHADER PROGRAM ********/

	// Create Shader

	gShaderProgramObject = glCreateProgram();

	// attach vertex shader to shader program

	glAttachShader(gShaderProgramObject, gVertexShaderObject);

	// attach Fragment shader to shader program

	glAttachShader(gShaderProgramObject, gFragmentShaderObject);

	// Pre-link binding of shder program object with vertex shader position attribute/properties

	glBindAttribLocation(gShaderProgramObject, ABG_ATTRIBUTE_POSITION, "vPosition");

	// link shader

	glLinkProgram(gShaderProgramObject);

	GLint iShaderProgramLinkStatus = 0;
	glGetProgramiv(gShaderProgramObject, GL_LINK_STATUS, &iShaderProgramLinkStatus);

	if (iShaderProgramLinkStatus != GL_FALSE)
	{
		glGetProgramiv(gShaderProgramObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);

		if (iInfoLogLength > 0)
		{
			szInfoLog = (char*)malloc(iInfoLogLength);

			if (szInfoLog != NULL)
			{
				GLsizei written;
				glGetProgramInfoLog(gShaderProgramObject, iInfoLogLength, &written, szInfoLog);
				fprintf(gpLogFile, "Shader Program Link Log: %s\n", szInfoLog);
				free(szInfoLog);
				Uninitialize();
				exit(0);
			}
		}
	}

	// Get MVP Uniform location

	gMVPUniform = glGetUniformLocation(gShaderProgramObject, "u_mvp_matrix");

	/*vertices, colors, shader attribs, vbo, vao, initializations*/

	const GLfloat triangleVertices[] =
	{
		0.0f, 50.0f, 0.0f,// apex
		-50.0f, -50.0f, 0.0f,// left-bottom
		50.0f, -50.0f, 0.0f	// right-bottom
	};

	glGenVertexArrays(1, &gVao);
	glBindVertexArray(gVao);

	glGenBuffers(1, &gVbo);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(ABG_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(ABG_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_CULL_FACE);

	// Set Clear Color

	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

	// Warmup Resize Call

	gOrthographicProjectionMtrix = mat4::identity();

	Resize(WIN_WIDTH, WIN_HEIGHT);
}

void Resize(int iWidth, int iHeight)
{
	// Code

	if (0 == iHeight)
		iHeight = 1;

	glViewport(0, 0, (GLsizei)iWidth, (GLsizei)iHeight);

	if (iWidth < iHeight)
	{
		gOrthographicProjectionMtrix = ortho(-100.0f, 100.0f, (-100.0f * (iHeight / iWidth)), (100.0f * (iHeight / iWidth)), -100.0f, 100.0f);
	}
	else
	{
		gOrthographicProjectionMtrix = ortho(-100.0f, 100.0f, (-100.0f * (iWidth / iHeight)), (100.0f * (iWidth/ iHeight)), -100.0f, 100.0f);
	}
}

void Display()
{
	// Code

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Start using OpenGL program object

	glUseProgram(gShaderProgramObject);

	// OpenGL Drawing 
	// set modelview & modelviewpeojection matrices to identity
	mat4 modelViewMatrix = mat4::identity();
	mat4 modelViewProjectionMatrix = mat4::identity();

	modelViewProjectionMatrix = gOrthographicProjectionMtrix * modelViewMatrix;

	glUniformMatrix4fv(gMVPUniform, 1, GL_FALSE, modelViewProjectionMatrix);

	glBindVertexArray(gVao);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	// unbind vao

	glBindVertexArray(0);

	glUseProgram(0);

	SwapBuffers(ghdc);
}

void Uninitialize(void)
{
	// Code

	if (true == gbFullScreen)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);

		SetWindowLong(ghwnd, GWL_STYLE, (dwStyle | WS_OVERLAPPEDWINDOW));
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);

		ShowCursor(TRUE);
	}

	// destroy vao
	
	if (gVao)
	{
		glDeleteVertexArrays(1, &gVao);
		gVao = 0;
	}

	// destroy vbo

	if (gVbo)
	{
		glDeleteVertexArrays(1, &gVbo);
		gVbo = 0;
	}

	glDetachShader(gShaderProgramObject, gVertexShaderObject);
	glDetachShader(gShaderProgramObject, gFragmentShaderObject);

	glDeleteShader(gVertexShaderObject);
	gVertexShaderObject = 0;

	glDeleteShader(gFragmentShaderObject);
	gFragmentShaderObject = 0;

	glUseProgram(0);

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

	if (gpLogFile)
	{
		fprintf(gpLogFile, "Log File Closed Successfully...!!!\n");
		fclose(gpLogFile);
		gpLogFile = NULL;
	}
}
