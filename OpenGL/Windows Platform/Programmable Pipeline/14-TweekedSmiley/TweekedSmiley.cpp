
/* Header Files */

#include"TweekedSmiley.h"
#include"../vmath.h"

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

GLuint gVao_Quad;
GLuint gVbo_Texture_Quad;
GLuint gVbo_Position_Quad;

GLuint gMVPUniform;
GLuint gTextureSamplerUniform;

GLuint gSmileyTexture;

GLuint gKeyPressed;

mat4 gPerspectiveProjectionMatrix;

// WinMain()

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
	// Local Variable Declaration


	MSG			msg;
	HWND		hwnd;
	WNDCLASSEX	WndClass;
	bool		bDone = false;
	TCHAR		szAppName[] = { TEXT("TextureWindow") };

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
		TEXT("Texture : Tweeked Smiley"),
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

		case 0x31:
			gKeyPressed = 1;
			break;

		case 0x32:
			gKeyPressed = 2;
			break;
		case 0x33:
			gKeyPressed = 3;
			break;
		case 0x34:
			gKeyPressed = 4;
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
		"#version 450 core"\
		"\n"\
		"in vec2 vTexCoord;"
		"out vec2 out_TexCoord;"
		"in vec4 vPosition;"\
		"uniform mat4 u_mvp_matrix;"\
		
		"void main(void)"\
		"\n"\
		"{"\
			"gl_Position = u_mvp_matrix * vPosition;"\
			"out_TexCoord = vTexCoord;"\
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
		"#version 450 core"\
		"\n"\
		"in vec2 out_TexCoord;"\
		"uniform sampler2D u_textureSampler;"\
		"out vec4 FragColor;"\
		
		"void main(void)"\
		"\n"\
		"{"\
			"FragColor = texture(u_textureSampler, out_TexCoord);"\
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
	glBindAttribLocation(gShaderProgramObject, ABG_ATTRIBUTE_TEXTURE0, "vTexCoord");

	// link shader

	glLinkProgram(gShaderProgramObject);

	GLint iShaderProgramLinkStatus = 0;
	glGetProgramiv(gShaderProgramObject, GL_LINK_STATUS, &iShaderProgramLinkStatus);

	if (iShaderProgramLinkStatus == GL_FALSE)
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
	gTextureSamplerUniform = glGetUniformLocation(gShaderProgramObject, "u_textureSampler");

	/*vertices, colors, shader attribs, vbo, vao, initializations*/
	GLfloat fCubeVertex = 1.0f;
	GLfloat fZero = 0.0f;
	GLfloat fCubeTexture = 1.0f;

	const GLfloat QuadVertices[] =
	{
		fCubeVertex,fCubeVertex,fCubeVertex,
		-fCubeVertex,fCubeVertex,fCubeVertex,
		-fCubeVertex,-fCubeVertex,fCubeVertex,
		fCubeVertex,-fCubeVertex,fCubeVertex
	};

	// Square Position (Vertices)

	glGenVertexArrays(1, &gVao_Quad);
	glBindVertexArray(gVao_Quad);

	/* Position vbo */
	glGenBuffers(1, &gVbo_Position_Quad);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Position_Quad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(QuadVertices), QuadVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(ABG_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(ABG_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Texture vbo*/
	glGenBuffers(1, &gVbo_Texture_Quad);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Texture_Quad);

	/* As coordinates are generated at runtine so we are creating dynamic array 
		NULL : As we are not creating array
		GL_DYNAMIC_ARRAY : As we don't have array at this point of time we are indicating that we will provide at runtime.
	*/	
	glBufferData(GL_ARRAY_BUFFER, sizeof(4 * 2 * sizeof(GLfloat)), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(ABG_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(ABG_ATTRIBUTE_TEXTURE0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_2D);

	LoadGLTexture(&gSmileyTexture, MAKEINTRESOURCE(SMILEY_BITMAP));

	// Set Clear Color

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Warmup Resize Call

	gPerspectiveProjectionMatrix = mat4::identity();

	Resize(WIN_WIDTH, WIN_HEIGHT);
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

void Display()
{
	/* Local Variable Declaration */

	static GLfloat TexCoord[8];

	// Code

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Start using OpenGL program object

	glUseProgram(gShaderProgramObject);

	// OpenGL Drawing 
	// set modelview & modelviewpeojection matrices to identity

	mat4 modelViewMatrix = mat4::identity();
	mat4 modelViewProjectionMatrix = mat4::identity();

	// Reset state to identity and start setting values for Square

	modelViewMatrix = mat4::identity();
	modelViewProjectionMatrix = mat4::identity();

	modelViewMatrix = vmath::translate(0.0f, 0.0f, -6.0f);

	modelViewProjectionMatrix = gPerspectiveProjectionMatrix * modelViewMatrix;

	glUniformMatrix4fv(gMVPUniform, 1, GL_FALSE, modelViewProjectionMatrix);

	glBindVertexArray(gVao_Quad);

	if (gKeyPressed == 1)
	{
		TexCoord[0] = 1.0f;
		TexCoord[1] = 1.0f;
		TexCoord[2] = 0.0f;
		TexCoord[3] = 1.0f;
		TexCoord[4] = 0.0f;
		TexCoord[5] = 0.0f;
		TexCoord[6] = 1.0f;
		TexCoord[7] = 0.0f;
	}
	else if (gKeyPressed == 2)
	{
		TexCoord[0] = 0.5f;
		TexCoord[1] = 0.5f;
		TexCoord[2] = 0.0f;
		TexCoord[3] = 0.5f;
		TexCoord[4] = 0.0f;
		TexCoord[5] = 0.0f;
		TexCoord[6] = 0.5f;
		TexCoord[7] = 0.0f;
	}
	else if (gKeyPressed == 3)
	{
		TexCoord[0] = 2.0f;
		TexCoord[1] = 2.0f;
		TexCoord[2] = 0.0f;
		TexCoord[3] = 2.0f;
		TexCoord[4] = 0.0f;
		TexCoord[5] = 0.0f;
		TexCoord[6] = 2.0f;
		TexCoord[7] = 0.0f;
	}
	else if (gKeyPressed == 4)
	{
		TexCoord[0] = 0.5f;
		TexCoord[1] = 0.5f;
		TexCoord[2] = 0.5f;
		TexCoord[3] = 0.5f;
		TexCoord[4] = 0.5f;
		TexCoord[5] = 0.5f;
		TexCoord[6] = 0.5f;
		TexCoord[7] = 0.5f;
	}

	glBindBuffer(GL_ARRAY_BUFFER, gVbo_Texture_Quad);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(GLfloat), TexCoord, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(ABG_ATTRIBUTE_TEXTURE0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(ABG_ATTRIBUTE_TEXTURE0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Drawing Square

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);	//0-4 (each with its x,y,z,w) vertices in cubevertices array.
	

	// unbind vao_Square
	glBindVertexArray(0);

	glUseProgram(0);
		
	SwapBuffers(ghdc);
}

// LoadGLTexture();

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

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);	// Instead of PACKSIZE 4, 1 gives faster performance in PP
		glGenTextures(1, Texture);
		glBindTexture(GL_TEXTURE_2D, *Texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);
		// gluBuild2DMipmaps() Internallly calls 2 gl  Funtions : glTexImage2D(); and glGenerateMipmap();

		glTexImage2D(GL_TEXTURE_2D,
			0,
			GL_RGB,
			bmp.bmWidth,
			bmp.bmHeight,
			0, // Border Width Of Texture
			GL_BGR, // Same as GL_BGR_EXT
			GL_UNSIGNED_BYTE,
			bmp.bmBits);

		glGenerateMipmap(GL_TEXTURE_2D);

		DeleteObject(hBitmap);
	}

	return(bResult);

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
	
	if (gVao_Quad)
	{
		glDeleteVertexArrays(1, &gVao_Quad);
		gVao_Quad= 0;
	}

	if (gVbo_Position_Quad)
	{
		glDeleteVertexArrays(1, &gVbo_Position_Quad);
		gVbo_Position_Quad= 0;
	}

	if (gVbo_Texture_Quad)
	{
		glDeleteVertexArrays(1, &gVbo_Texture_Quad);
		gVbo_Texture_Quad = 0;
	}

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
