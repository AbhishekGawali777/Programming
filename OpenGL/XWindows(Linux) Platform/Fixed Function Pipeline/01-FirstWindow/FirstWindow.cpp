    
// Header Files

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

#include<X11/Xlib.h>            // For all X*** API's
#include<X11/Xutil.h>           // For VisualInfo XMatchVisualInfo
#include<X11/XKBlib.h>          // For XkbKeyCodeToKeysym
#include<X11/keysym.h>          // For KeySym (keyBoard Inputs)

// Namespaces

using namespace std;

// Global Variable Declarations

Window gWindow;
Colormap gColormap;
FILE* gpFile = NULL;
Display *gpDisplay = NULL;
bool gbFullScreen = false;
XVisualInfo *gpXVisualInfo = NULL;

int giWindowWidth = 800;
int giWindowHeight = 600;

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
    
    // Message Loop
    
    XEvent event;       // Union of 33 Structures. (Win32 : MSG msg (Likewise))
    KeySym keysym;      // Key Sysmbol : Symbols for Keyboard key (Win32 Like Virtual Key code : (VK_ESCAPE))
                        // X11/keysym.h
    
    while(1)
    {
        XNextEvent(gpDisplay, &event);
        
        switch(event.type)
        {
            case MapNotify:     // WM_CREATE
                break;
                
            case KeyPress:      // WM_KEYDOWN
                
                // OS Asks us that you want KeyCode Symbols or Real Keycodes
                // Here we are asking for keycode Symbol becase same was used at the time of Windows Programming
                
                keysym = XkbKeycodeToKeysym(gpDisplay, event.xkey.keycode, 0, 0);   // 3rd param : KeyCode Group, 4th : Shift key State with the key combination
                                                
                switch(keysym)
                {
                    case XK_Escape:     // XK : X server's Key Symbol
                        Uninitialize();
                        exit(0);
                        
                    case XK_F:
                    case XK_f:
                        fprintf(gpFile, "f Pressed %d", gbFullScreen);
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
            
            case ButtonPress: //Mouse Button
                
                switch(event.xbutton.button)
                {
                    case 1:     // Left Mouse Button
                        break;
                        
                    case 2:     // Middle Mouse Button
                        break;
                        
                    case 3:     // Right Mouse Button
                        break;
                        
                    case 4:     // Upward Mouse Wheel Scroll
                        break;
                        
                    case 5:     // Down Mouse Wheel Scroll
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case MotionNotify:      // WM_MOVE
                break;
                
            case ConfigureNotify:   // WM_SIZE
                
                iWinWidth = event.xconfigure.width;
                iWinHeight = event.xconfigure.height;
                break;
                
            case Expose:            // WM_PAINT
                break;
                
            case DestroyNotify:     // WM_DESTROY
                break;
                
            case 33:                // Close Button Click (Numerical representation of "WM_DELETE_WINDOW")
                Uninitialize();
                exit(0);
                
            default:
                break;
        }
    }
    
    Uninitialize();
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
    
    // Code
    
    gpDisplay = XOpenDisplay(NULL);
    
    if(NULL == gpDisplay)
    {
        fprintf(gpFile, "ERROR : Unable to open X Display.\n");
        Uninitialize();
        exit(-1);
    }
    
    iDefaultScreen = XDefaultScreen(gpDisplay);
    iDefaultDepth = DefaultDepth(gpDisplay, iDefaultScreen);
    gpXVisualInfo = (XVisualInfo*)malloc(sizeof(XVisualInfo));
    
    if(NULL == gpXVisualInfo)
    {
        fprintf(gpFile, "ERROR : Unable to allocate memory for XVisualInfo.\n");
        Uninitialize();
        exit(-1);
    }
    
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
    
    XStoreName(gpDisplay, gWindow, "First Window");
    
    Atom windowManagerDelete = XInternAtom(gpDisplay, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(gpDisplay, gWindow, &windowManagerDelete, 1);
    
    XMapWindow(gpDisplay, gWindow); // Sends event MapNotify
}

// ToggleFullScreen()

void ToggleFullScreen(void)
{
    // Local Variable Declarations
    
    Atom wm_state;
    Atom fullscreen;
    XEvent xev = {0};
    
    // Code
    
    wm_state = XInternAtom(gpDisplay, "_NET_WM_STATE", False); // Getting current state of window (_NET_ : Across the network you can get window state)
                                                                // False : If buffer have already this state then no need to create new
    memset(&xev, 0, sizeof(xev));
    
    xev.type = ClientMessage;           // As Xlib is a client API that's why sending ClientMessage
    xev.xclient.window = gWindow;
    xev.xclient.message_type = wm_state;
    xev.xclient.format = 32;            // 32 BIT message
    if(gbFullScreen)
        xev.xclient.data.l[0] = 0;
    else
        xev.xclient.data.l[0] = 1;
    
    //xev.xclient.data.l[0] = gbFullScreen ? 0 : 1;   // fullscreen decision making here
    fullscreen = XInternAtom(gpDisplay, "_NET_WM_STATE_FULLSCREEN", False);
    xev.xclient.data.l[1] = fullscreen;
    
    XSendEvent(gpDisplay, 
                RootWindow(gpDisplay, gpXVisualInfo->screen),
                False, // Only fullscreen this window not it's childs
                StructureNotifyMask,
                &xev
              );
}

// Uninitialize()

void Uninitialize(void)
{
    // Code
    
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

/*
 How to get pressed keyboard alphabates by other way (like WM_CHAR): 
 
 - Declare globally one array
    char keys[26];
- In case KeyPress:
            XkbKeyCodeToKeysym();
            
            switch(keysym)
            {
            case XK_Escape:     // XK : X server's Key Symbol
                Uninitialize();
                exit(0);
                break;
            }
                    
            XLookUpString(gpDisplay, keys, sizeof(keys), NULL, NULL); 
            //  last parameter : Compose (Saves character for further used as giving NULL we don't want to save that character)
                
            switch(keys[0])
            {
                case 'A':
                case 'a':
                    break;
                    So on...
            }
            
            break;
 
 */

