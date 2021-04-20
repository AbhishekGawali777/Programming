    
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

#include<SOIL/SOIL.h>

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

GLfloat fAngle = 0.0f;

GLuint texture_stone;
GLuint texture_kundali;

// Entry-Point Function

int main(void)
{
    // Function Prototypes
    
    void Update(void);
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
    
    XStoreName(gpDisplay, gWindow, "Textured Pyramid And Cube");
    
    Atom windowManagerDelete = XInternAtom(gpDisplay, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(gpDisplay, gWindow, &windowManagerDelete, 1);
    
    XMapWindow(gpDisplay, gWindow); // Sends event MapNotify
}

// Initialize()

void Initialize(void)
{
    /* Function Prototype */
    
    void Resize(int, int);
    GLuint LoadBitmapAsTexture(const char*);
     
    /* Code */
    
    gGLXContext = glXCreateContext(gpDisplay, gpXVisualInfo, NULL, GL_TRUE);
    
    glXMakeCurrent(gpDisplay, gWindow, gGLXContext);
    
    texture_stone = LoadBitmapAsTexture("Stone.bmp");
    texture_kundali = LoadBitmapAsTexture("Vijay_Kundali.bmp");
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    glEnable(GL_TEXTURE_2D);

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
    /* Function Declarations */
    
    void DrawPyramid(void);
    void DrawCube(void);
    
    // Code
    
    glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    DrawPyramid();
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	DrawCube();

    glXSwapBuffers(gpDisplay, gWindow);
}

void DrawPyramid(void)
{
    // Local Variable Declarations
    
    GLfloat fZero = 0.0f;
    GLfloat fTexHalf = 0.5f;
    GLfloat fTexOne = 1.0f;
        
	// Code

	glTranslatef(-2.0f, 0.0f, -7.0f);
	glRotatef(fAngle, 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, texture_stone);
	glBegin(GL_TRIANGLES);

		// Front 

		glTexCoord2f(fTexHalf, fZero);
		glVertex3f(0.0f, 1.0f, 0.0f);
		
		glTexCoord2f(fZero, fTexOne);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		
		glTexCoord2f(fTexOne, fTexOne);
		glVertex3f(1.0f, -1.0f, 1.0f);
	
		// Right

		glTexCoord2f(fTexHalf, fZero);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glTexCoord2f(fZero, fTexOne);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glTexCoord2f(fTexOne, fTexOne);
		glVertex3f(1.0f, -1.0f, -1.0f);


		// Back

		glTexCoord2f(fTexHalf, fZero);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glTexCoord2f(fZero, fTexOne);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glTexCoord2f(fTexOne, fTexOne);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		// Left

		glTexCoord2f(fTexHalf, fZero);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glTexCoord2f(fZero, fTexOne);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glTexCoord2f(fTexOne, fTexOne);
		glVertex3f(-1.0f, -1.0f, 1.0f);

	glEnd();
}

void DrawCube(void)
{
    /* Local Variable Declarations */
    
    GLfloat fTexOne = 1.0f;
    GLfloat fTexZero = 0.0f;    
	
    // Code

	glTranslatef(2.0f, 0.0f, -8.0f);
	glBindTexture(GL_TEXTURE_2D, texture_kundali);
	glRotatef(fAngle, 1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);

		// Front

		glTexCoord2f(fTexOne, fTexZero);
		glVertex3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f(fTexZero, fTexZero);
		glVertex3f(-1.0f, 1.0f, 1.0f);

		glTexCoord2f(fTexZero, fTexOne);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		
		glTexCoord2f(fTexOne, fTexOne);
		glVertex3f(1.0f, -1.0f, 1.0f);

		// Right

		glTexCoord2f(fTexOne, fTexZero);
		glVertex3f(1.0f, 1.0f, -1.0f);

		glTexCoord2f(fTexZero, fTexZero);
		glVertex3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f(fTexZero, fTexOne);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glTexCoord2f(fTexOne, fTexOne);
		glVertex3f(1.0f, -1.0f, -1.0f);

		// Back

		glTexCoord2f(fTexOne, fTexZero);
		glVertex3f(-1.0f, 1.0f, -1.0f);

		glTexCoord2f(fTexZero, fTexZero);
		glVertex3f(1.0f, 1.0f, -1.0f);

		glTexCoord2f(fTexZero, fTexOne);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glTexCoord2f(fTexOne, fTexOne);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		// Left

		glTexCoord2f(fTexOne, fTexZero);
		glVertex3f(-1.0f, 1.0f, 1.0f);

		glTexCoord2f(fTexZero, fTexZero);
		glVertex3f(-1.0f, 1.0f, -1.0f);

		glTexCoord2f(fTexZero, fTexOne);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glTexCoord2f(fTexOne, fTexOne);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		// Top

		glTexCoord2f(fTexOne, fTexZero);
		glVertex3f(1.0f, 1.0f, -1.0f);

		glTexCoord2f(fTexZero, fTexZero);
		glVertex3f(-1.0f, 1.0f, -1.0f);

		glTexCoord2f(fTexZero, fTexOne);
		glVertex3f(-1.0f, 1.0f, 1.0f);

		glTexCoord2f(fTexOne, fTexOne);
		glVertex3f(1.0f, 1.0f, 1.0f);

		// Bottom

		glTexCoord2f(fTexOne, fTexZero);
		glVertex3f(1.0f, -1.0f, -1.0f);
		
		glTexCoord2f(fTexZero, fTexZero);
		glVertex3f(-1.0, -1.0f, -1.0f);

		glTexCoord2f(fTexZero, fTexOne);
		glVertex3f(-1.0, -1.0f, 1.0f);

		glTexCoord2f(fTexOne, fTexOne);
		glVertex3f(1.0, -1.0f, 1.0f);

	glEnd();

}

// LoadBitmapAsTexture()

GLuint LoadBitmapAsTexture(const char* path)
{
    // Local Variable Declarations
    
    int width, height;
    unsigned char* imageData = NULL;
    GLuint textureID;
    
    // Code
    
    imageData = SOIL_load_image(path, &width, &height, NULL, SOIL_LOAD_RGB); // Image Channels    
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    
    SOIL_free_image_data(imageData);
  
    return(textureID);
}

// Update()

void Update(void)
{
    if(fAngle >= 360.0f)
        fAngle = 0.0f;
        
    fAngle += 1.0f;    
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
    
