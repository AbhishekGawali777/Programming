
/* Header Files */

#include"WhiteSpehre.h"
#include"../../vmath.h"
#include"Sphere.h"

/* enum */

enum {

	ABG_ATTRIBUTE_POSITION = 0,
	ABG_ATTRIBUTE_COLOR,
	ABG_ATTRIBUTE_NORMALS,
	ABG_ATTRIBUTE_TEXTURE0
};

using namespace vmath;

// Global Variable Declarations

DWORD			dwStyle;
HDC				ghdc = NULL;
HWND			ghwnd = NULL;
HGLRC			ghrc = NULL;
FILE*			gpLogFile = NULL;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

bool gbFullScreen = false;
bool gbActiveWindow = false;

GLuint gVertexShaderObject;
GLuint gFragmentShaderbject;
GLuint gShaderProgramObject;

mat4 gPerspectiveProjectionMatrix;

float SphereVertices[1146];
float SphereNormals[1146];
float SphereTextures[764];
unsigned short SphereElements[2280];

unsigned int gNumVertices;
unsigned int gNumElements;

/* VAO */
GLuint gVao_Sphere;

/* VBO */
GLuint gVbo_SpherePosition;
GLuint gVbo_SphereNormals;
GLuint gVbo_SphereElements;

GLuint gMVPUniform;

// WinMain()

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
	// Local Variable Declaration


	MSG			msg;
	HWND		hwnd;
	WNDCLASSEX	WndClass;
	bool		bDone = false;
	TCHAR		szAppName[] = { TEXT("SphereWindow") };

	/* Code */
	
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
		TEXT("Lights : White Sphere"),
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

	/*Create VertexShader  */

	gVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	const GLchar* vertexShaderSourceCode =
		"#version 450 core"\
		"\n"\
		"out vec4 out_color;"\
		"in vec4 vPosition;"\
		"uniform mat4 u_mvp_matrix;"\
		"void main(void)"\
		"\n"\
		"{"\
		"gl_Position = u_mvp_matrix * vPosition;"\
		"out_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);"\
		"\n"\
		"}";

	glShaderSource(gVertexShaderObject, 1, (const GLchar**)&vertexShaderSourceCode, NULL);

	/* Compile Shader */

	glCompileShader(gVertexShaderObject);

	/* Error Handling during Compilation */

	GLint iLogInfoLength = 0;
	GLint iShaderCompiledStatus = 0;
	char* szLogInfo = NULL;

	glGetShaderiv(gVertexShaderObject, GL_COMPILE_STATUS, &iShaderCompiledStatus);

	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(gVertexShaderObject, GL_INFO_LOG_LENGTH, &iLogInfoLength);

		if (iLogInfoLength > 0)
		{
			szLogInfo = (char*)malloc(iLogInfoLength);

			if (NULL != szLogInfo)
			{
				GLsizei written;
				glGetShaderInfoLog(gVertexShaderObject, iLogInfoLength, &written, szLogInfo);
				fprintf(gpLogFile, "Vertex Shader Compilation log : %s \n", szLogInfo);
				free(szLogInfo);
				Uninitialize();
				exit(0);
			}
		}
	}

	/* Create Fragment Shader */

	gFragmentShaderbject = glCreateShader(GL_FRAGMENT_SHADER);

	/* Fragment Shader */

	const GLchar* fragmentShaderSourceCode =
		"#version 450 core"\
		"\n"\
		"in vec4 out_color;"\
		"out vec4 FragColor;"\
		"void main(void)"\
		"\n"\
		"{"\
		"FragColor = out_color;"\
		"}";

	glShaderSource(gFragmentShaderbject, 1, (const GLchar**)&fragmentShaderSourceCode, NULL);

	/* Compile Shader */

	glCompileShader(gFragmentShaderbject);

	/* Get Compilation Logs */

	glGetShaderiv(gFragmentShaderbject, GL_COMPILE_STATUS, &iShaderCompiledStatus);

	if (iShaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(gFragmentShaderbject, GL_INFO_LOG_LENGTH, &iLogInfoLength);

		if (iLogInfoLength > 0)
		{
			szLogInfo = (GLchar*)malloc(iLogInfoLength);

			if (NULL != szLogInfo)
			{
				GLsizei written = 0;
				glGetShaderInfoLog(gFragmentShaderbject, iLogInfoLength, &written, szLogInfo);
				fprintf(gpLogFile, "%s", szLogInfo);
				free(szLogInfo);
				Uninitialize();
				exit(0);
			}
		}
	}

	/* Create shader Prgram Object */

	gShaderProgramObject = glCreateProgram();

	/* Attach Vetex Shader to program */

	glAttachShader(gShaderProgramObject, gVertexShaderObject);

	/* Attach Fragment Shader to program */

	glAttachShader(gShaderProgramObject, gFragmentShaderbject);

	/* Pre-Link Binding of shader program with vertex shader position attribute */

	glBindAttribLocation(gShaderProgramObject, ABG_ATTRIBUTE_POSITION, "vPosition");
	glBindAttribLocation(gShaderProgramObject, ABG_ATTRIBUTE_NORMALS, "vNormal");

	/* Link Shader */

	glLinkProgram(gShaderProgramObject);

	/* Linker Error Handling */

	GLint iShaderProgramLinkStatus = 0;
	glGetProgramiv(gShaderProgramObject, GL_LINK_STATUS, &iShaderProgramLinkStatus);

	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(gShaderProgramObject, GL_INFO_LOG_LENGTH, &iLogInfoLength);

		if (iLogInfoLength > 0)
		{
			szLogInfo = (GLchar*)malloc(iLogInfoLength);

			if (NULL != szLogInfo)
			{
				GLsizei written = 0;
				glGetProgramInfoLog(gShaderProgramObject, iLogInfoLength, &written, szLogInfo);
				fprintf(gpLogFile, "%s", szLogInfo);
				free(szLogInfo);
				Uninitialize();
				exit(0);
			}
		}
	}

	/* MVP Uniform Locations */

	gMVPUniform = glGetUniformLocation(gShaderProgramObject, "u_mvp_matrix");

	/* Getting Sphere Data */

	getSphereVertexData(SphereVertices, SphereNormals, SphereTextures, SphereElements);
	
	gNumVertices = getNumberOfSphereVertices();
	gNumElements = getNumberOfSphereElements();

	// Vao Of Sphere

	glGenVertexArrays(1, &gVao_Sphere);
	glBindVertexArray(gVao_Sphere);

	// Position vbo

	glGenBuffers(1, &gVbo_SpherePosition);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_SpherePosition);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SphereVertices), SphereVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(ABG_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(ABG_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Normal Vbo

	glGenBuffers(1, &gVbo_SphereNormals);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_SphereNormals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SphereNormals), SphereNormals, GL_STATIC_DRAW);

	glVertexAttribPointer(ABG_ATTRIBUTE_NORMALS, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(ABG_ATTRIBUTE_NORMALS);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Element vbo

	glGenBuffers(1, &gVbo_SphereElements);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_SphereElements);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SphereElements), SphereElements, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// Set Clear Color

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Warmup Resize Call

	gPerspectiveProjectionMatrix = mat4::identity();

	Resize(WIN_WIDTH, WIN_HEIGHT);
}

void Display(void)
{
	/* Code */

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Start using OpenGL program object

	glUseProgram(gShaderProgramObject);

	// OpenGL Drawing 
	// set modelview & modelviewpeojection matrices to identity

	mat4 modelViewMatrix = mat4::identity();
	mat4 modelViewProjectionMatrix = mat4::identity();

	modelViewMatrix = vmath::translate(0.0f, 0.0f, -3.0f);
	modelViewProjectionMatrix = gPerspectiveProjectionMatrix * modelViewMatrix;

	glUniformMatrix4fv(gMVPUniform, 1, GL_FALSE, modelViewProjectionMatrix);

	glBindVertexArray(gVao_Sphere);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gVbo_SphereElements);
	glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);

	/* Unbinf Vao */
	glBindVertexArray(0);

	glUseProgram(0);

	SwapBuffers(ghdc);
}

void Resize(int iWidth, int iHeight)
{
	// Code

	if (0 == iHeight)
		iHeight = 1;

	glViewport(0, 0, (GLsizei)iWidth, (GLsizei)iHeight);

	// Perspective Projection

	gPerspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)iWidth / (GLfloat)iHeight, 0.1f, 100.0f);
}

GLfloat Update(GLfloat p_fAngle)
{
	p_fAngle = p_fAngle + 2.0f;
	if (p_fAngle >= 360.0f)
	{
		p_fAngle = 0.0f;
	}
	return(p_fAngle);
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

	if (gVao_Sphere)
	{
		glDeleteVertexArrays(1, &gVao_Sphere);
		gVao_Sphere = 0;
	}

	if (gVbo_SpherePosition)
	{
		glDeleteVertexArrays(1, &gVbo_SpherePosition);
		gVbo_SpherePosition = 0;
	}

	if (gVbo_SphereElements)
	{
		glDeleteVertexArrays(1, &gVbo_SphereElements);
		gVbo_SphereElements = 0;
	}

	if (gVbo_SphereNormals)
	{
		glDeleteVertexArrays(1, &gVbo_SphereNormals);
		gVbo_SphereNormals = 0;
	}

	/* Safe Release */

	if (gShaderProgramObject)
	{
		glUseProgram(gShaderProgramObject);
		GLsizei shaderCount;
		glGetProgramiv(gShaderProgramObject, GL_ATTACHED_SHADERS, &shaderCount);
		GLuint* pShader = NULL;
		pShader = (GLuint*)malloc(shaderCount * sizeof(shaderCount));
		glGetAttachedShaders(gShaderProgramObject, shaderCount, &shaderCount, pShader);
		for (GLsizei i = 0; i < shaderCount; i++)
		{
			glDetachShader(gShaderProgramObject, pShader[i]);
			glDeleteShader(pShader[i]);
			pShader[i] = 0;
		}
		if (pShader)
		{
			free(pShader);
		}
		glDeleteProgram(gShaderProgramObject);
		gShaderProgramObject = 0;
		glUseProgram(0);
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

	if (gpLogFile)
	{
		fprintf(gpLogFile, "Log File Closed Successfully...!!!\n");
		fclose(gpLogFile);
		gpLogFile = NULL;
	}
}
