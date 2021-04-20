    
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

GLfloat tAngle = 0.0f;
GLfloat rAngle = 0.0f;

// Entry-Point Function

int main(void)
{
    // Function Prototypes
    
    void Update(void);
    void CreateWindow(void);
    void Uninitialize(void);
    void ToggleFullScreen(void);
    
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
        Update();
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
        GLX_DEPTH_SIZE, 24, // V4L : (Video for Linux)recommands bitsize of depth should be 24
        /* V4L is under device driver control. Device Driver che 2 component astat
         1. VA API Component. (Video Accelaration API)
         2. VDPAU Component. (Video Driver Presentation UNIX API)
         */
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
    
    XStoreName(gpDisplay, gWindow, "2D Animation");
    
    Atom windowManagerDelete = XInternAtom(gpDisplay, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(gpDisplay, gWindow, &windowManagerDelete, 1);
    
    XMapWindow(gpDisplay, gWindow); // Sends event MapNotify
}

// Initialize()

void Initialize(void)
{
    /* Function Prototype */
    
    void Resize(int, int);
    
    /* Code */
    
    gGLXContext = glXCreateContext(gpDisplay, gpXVisualInfo, NULL, GL_TRUE);
    
    glXMakeCurrent(gpDisplay, gWindow, gGLXContext);
    
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        
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
    // Code
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
  
	glTranslatef(-1.5f, 0.0f, -5.0f);
    glRotatef(tAngle, 0.0f, 1.0f, 0.0f);
    
	// Triangle

	glBegin(GL_TRIANGLES);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 0.0f);

	glEnd();

	// Rectangle
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(1.5f, 0.0f, -6.0f);
    glRotatef(rAngle, 1.0f, 0.0f, 0.0f);
	
    glBegin(GL_QUADS);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 0.0f);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 0.0f);
        
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 0.0f);
		
	glEnd();
    
    glXSwapBuffers(gpDisplay, gWindow);
}

// Update()

void Update(void)
{
	if (tAngle >= 360.0f)
		tAngle = 0.0f;
	tAngle = tAngle + 2.0f;

	if (rAngle >= 360.0f)
		rAngle = 0.0f;
	rAngle = rAngle + 2.0f;
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
    
