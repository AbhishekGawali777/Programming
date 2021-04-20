    
// Header Files

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

#include<X11/Xlib.h>            // For all X*** API's
#include<X11/Xutil.h>           // For VisualInfo XMatchVisualInfo
#include<X11/XKBlib.h>          // For XkbKeyCodeToKeysym
#include<X11/keysym.h>          // For KeySym (keyBoard Inputs)

#include<GL/gl.h>               // For OpenGL API's
#include<GL/glu.h>
#include<GL/glx.h>              // For GLX API's

#define CHECK_IMAGE_WIDTH  64
#define CHECK_IMAGE_HEIGHT 64

// Namespaces

using namespace std;

/* Function Prototypes */

void DisplayProgram(void);
void Initialize(void);
void Resize(int, int);

// Global Variable Declarations

Window gWindow;
Colormap gColormap;
FILE* gpFile = NULL;
Display *gpDisplay = NULL;
bool gbFullScreen = false;
XVisualInfo *gpXVisualInfo = NULL;

GLXContext gGLXContext; // Like HGLRC

int giWindowWidth = 800;
int giWindowHeight = 600;

GLubyte CheckImage[CHECK_IMAGE_HEIGHT][CHECK_IMAGE_WIDTH][4];
GLuint TexImage;

// Entry-Point Function

int main(void)
{
    // Function Prototypes
    
    void CreateWindow(void);
    void ToggleFullScreen(void);
    void Uninitialize(void);
    
    // Local Variable Declarations
    
    int iWinWidth = giWindowWidth;
    int iWinHeight = giWindowHeight;
    
    static GC gc;   // GC : Graphic Context Software context of Display Structure.
    static XFontStruct* pXFontStruct = NULL;
    
    XGCValues gcValues;
    XColor greenColor;
    
    char str[] = "Hello XWindows.";
    
    int stringLength;
    int stringWidth;
    int fontHeight;
    
    bool bDone = false;
    
    // Code
    
    if((gpFile = fopen("LogFile.txt", "w")) == NULL)
    {
        printf("ERROR : LogFile Cannot be Created.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        fprintf(gpFile, "LogFile Created Successfully...!!!\n\n");
    }
    
    CreateWindow();
    Initialize();
    
    // Message Loop
    
    XEvent event;      
    KeySym keysym;     
    
    while(bDone == false)
    {
        while(XPending(gpDisplay))          // PeekMessage() Loop
        {
             XNextEvent(gpDisplay, &event);
    
            switch(event.type)
            {
                case MapNotify:     // WM_CREATE
                    
                    pXFontStruct = XLoadQueryFont(gpDisplay, "fixed"); // XServer gives fixed(Default)font
                    
                    break;
                    
                case KeyPress:      // WM_KEYDOWN
                                
                    keysym = XkbKeycodeToKeysym(gpDisplay, event.xkey.keycode, 0, 0);   // 3rd param : KeyCode Group, 4th : Shift key State with the key combination
                                                    
                    switch(keysym)
                    {
                        case XK_Escape:     // XK : X server's Key Symbol
                            
                            bDone =  true;
                            break;
                           
                        case XK_F:
                        case XK_f:
                            
                            if(gbFullScreen == false)
                            {
                                ToggleFullScreen();
                                gbFullScreen = true;                           
                            }
                            else
                            {
                                ToggleFullScreen();
                                gbFullScreen = false;
                            }
                            
                            break;
                            
                        default:
                            glDisable(GL_TEXTURE_2D);
                            break;
                    }
                    break;
                
                case ButtonPress:
                    
                    switch(event.xbutton.button)
                    {
                        case 1:
                            break;
                            
                        case 2:
                            break;
                            
                        case 3:
                            break;
                            
                        default:
                            break;
                    }
                    break;
                    
                case MotionNotify:   // WM_MOVE
                
                    break;
                    
                case ConfigureNotify:
                    
                    iWinWidth = event.xconfigure.width;
                    iWinHeight = event.xconfigure.height;
                    
                    Resize(iWinWidth, iWinHeight);
                    break;
                    
                case Expose:    // WM_PAINT
                    break;
                    
                case DestroyNotify:
                    break;
                    
                case 33:
                  
                    bDone = true;
                    break; 
                    
                default:
                    break;
            }
        }
        
        DisplayProgram();
    }
    
    Uninitialize();
    
    return(0);
}

// CreateWindow()

void CreateWindow(void)
{
    // Function Prototypes
    
    void Uninitialize(void);
    
    // Local Variable Declarations
    
    XSetWindowAttributes winAttribs;
    int iDefaultDepth;
    int iDefaultScreen;
    int styleMask;
    
    static int frameBufferAttributes[] = 
    {
        GLX_DOUBLEBUFFER, True,
        GLX_RGBA,
        GLX_RED_SIZE, 8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE, 8,
        GLX_ALPHA_SIZE, 8,
        None
    };
    
    // Code
    
    gpDisplay = XOpenDisplay(NULL);
    
    if(NULL == gpDisplay)
    {
        fprintf(gpFile, "ERROR : Unable to open X Display.\n");
        Uninitialize();
        exit(-1);
    }
    
    iDefaultScreen = XDefaultScreen(gpDisplay);
    //iDefaultDepth = DefaultDepth(gpDisplay, iDefaultScreen);
    gpXVisualInfo = (XVisualInfo*)malloc(sizeof(XVisualInfo));
    
    if(NULL == gpXVisualInfo)
    {
        fprintf(gpFile, "ERROR : Unable to allocate memory for XVisualInfo.\n");
        Uninitialize();
        exit(-1);
    }
    gpXVisualInfo = glXChooseVisual(gpDisplay, iDefaultScreen, frameBufferAttributes);
    
    XMatchVisualInfo(gpDisplay, iDefaultScreen, iDefaultDepth, TrueColor, gpXVisualInfo);
    
    if(NULL == gpXVisualInfo)
    {
        fprintf(gpFile, "ERROR : Unable to get Visual\n");
        Uninitialize();
        exit(-1);
    }
    
    winAttribs.border_pixel = 0;
    winAttribs.background_pixmap = 0;
    winAttribs.colormap = XCreateColormap(gpDisplay, RootWindow(gpDisplay, gpXVisualInfo->screen), gpXVisualInfo->visual, AllocNone);
    gColormap = winAttribs.colormap;
    winAttribs.background_pixel = BlackPixel(gpDisplay, iDefaultScreen);
    winAttribs.event_mask = ExposureMask | VisibilityChangeMask | ButtonPressMask | KeyPressMask | PointerMotionMask | StructureNotifyMask;
    styleMask = CWBorderPixel | CWBackPixel | CWEventMask | CWColormap;
    
    gWindow = XCreateWindow(gpDisplay,
            RootWindow(gpDisplay, gpXVisualInfo->screen),
            0,
            0,
            giWindowWidth,
            giWindowHeight,
            0,
            gpXVisualInfo->depth,
            InputOutput,
            gpXVisualInfo->visual,
            styleMask,
            &winAttribs);
    
    if(!gWindow)
    {
        fprintf(gpFile, "ERROR : Failed to create Main Window\n");
        Uninitialize();
        exit(-1);
    }
    
    XStoreName(gpDisplay, gWindow, "Checker Board");
    
    Atom windowManagerDelete = XInternAtom(gpDisplay, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(gpDisplay, gWindow, &windowManagerDelete, 1);
    
    XMapWindow(gpDisplay, gWindow); // Sends event MapNotify
}

// Initialize()

void Initialize(void)
{
    /* Function Prototype */
    
    void Resize(int, int);
    void LoadGLTexture(void);
    
    /* Code */
    
    gGLXContext = glXCreateContext(gpDisplay, gpXVisualInfo, NULL, GL_TRUE);
    
    glXMakeCurrent(gpDisplay, gWindow, gGLXContext);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    glEnable(GL_TEXTURE_2D);
    
    LoadGLTexture();
    
    // Warm-up call
    
    Resize(giWindowWidth, giWindowHeight);
}

// Resize()

void Resize(int winWidth, int winHeight)
{
    // Code
    
    if(winHeight == 0)
        winHeight = 1;
    
    glViewport(0, 0, (GLsizei)winWidth, (GLsizei)winHeight);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(45.0f, (GLfloat)winWidth / (GLfloat)winHeight, 0.1f, 100.0f);    
}

// DisplayProgram()

void DisplayProgram(void)
{
    // Function Declarations
    
    void DrawCheckerBoard(void);
    
    // Code
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	DrawCheckerBoard();
    
    glXSwapBuffers(gpDisplay, gWindow);
}

void DrawCheckerBoard(void)
{
	// Code

	glTranslatef(0.0f, 0.0f, -5.6f);
	
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

// LoadGLTexture()

void LoadGLTexture(void)
{
    /* Function Prototypes */
    
    void MakeCheckImage(void);
    
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

// ToggleFullScreen()

void ToggleFullScreen(void)
{
    // Local Variable Declarations
    
    Atom wm_state;
    Atom fullscreen;
    XEvent xev = {0};
    
    // Code
    
    wm_state = XInternAtom(gpDisplay, "_NET_WM_STATE", False);
    memset(&xev, 0, sizeof(xev));
    
    xev.type = ClientMessage;
    xev.xclient.window = gWindow;
    xev.xclient.message_type = wm_state;
    xev.xclient.format = 32;          
    xev.xclient.data.l[0] = gbFullScreen ? 0 : 1;
    fullscreen = XInternAtom(gpDisplay, "_NET_WM_STATE_FULLSCREEN", False);
    xev.xclient.data.l[1] = fullscreen;
    
    XSendEvent(gpDisplay, 
                RootWindow(gpDisplay, gpXVisualInfo->screen),
                False,
                StructureNotifyMask,
                &xev
              );
}

// Uninitialize()

void Uninitialize(void)
{
    // Local Variable Declarations
    
    GLXContext currentGLXContext;
    
    // Code
    
    currentGLXContext = glXGetCurrentContext();
    
    if(currentGLXContext == gGLXContext)
    {
        glXMakeCurrent(gpDisplay, 0, 0);
    }
    
    if(gGLXContext)
    {
        glXDestroyContext(gpDisplay, gGLXContext);
    }
        
    if(gWindow)
    {
        XDestroyWindow(gpDisplay, gWindow);
    }
    
    if(gColormap)
    {
        XFreeColormap(gpDisplay, gColormap);
    }
    
    if(gpXVisualInfo)
    {
        free(gpXVisualInfo);
        gpXVisualInfo = NULL;
    }
    
    if(gpDisplay)
    {
        XCloseDisplay(gpDisplay);
        gpDisplay = NULL;
    }
    
    if(gpFile)
    {
        fprintf(gpFile, "\n\nLog File Closed Successfully...!!!\n");
        fclose(gpFile);
        gpFile = NULL;
    }
}
    
