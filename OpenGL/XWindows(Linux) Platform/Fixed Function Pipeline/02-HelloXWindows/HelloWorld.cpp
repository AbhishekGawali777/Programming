    
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
    
    static GC gc;   // GC : Graphic Context Software context of Display Structure.
    static XFontStruct* pXFontStruct = NULL;
    
    XGCValues gcValues;
    XColor greenColor;
    
    char str[] = "Hello XWindows From Abhishek Balasaheb Gawali.";
    
    int stringLength;
    int stringWidth;
    int fontHeight;
    
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
    
    XEvent event;      
    KeySym keysym;     
    
    while(1)
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
                        
                        XUnloadFont(gpDisplay, pXFontStruct->fid); // Full Structure or fid is depend on API Deprecation. if fid won't worked, then pass full Structure
                        XFreeGC(gpDisplay, gc);
                        
                        Uninitialize();
                        exit(0);
                        
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
                break;
                
            case Expose:    // WM_PAINT
                
                gc = XCreateGC(gpDisplay, gWindow, 0, &gcValues);    // 3rd : 0 (Default values) 4th : XGCValues like PAINTSTRUCT
                XSetFont(gpDisplay, gc, pXFontStruct->fid); // fid : Font ID
                XAllocNamedColor(gpDisplay, gColormap, "green", &greenColor, &greenColor);   // Get Color from ColorMap 4th : Nearly equal color 5th: Exact Color
                // May be changes in API at XAllocNamedColor. Old is XLoadNamedColor
                XSetForeground(gpDisplay, gc, greenColor.pixel);
                
                stringLength = strlen(str);
                stringWidth = XTextWidth(pXFontStruct, str, stringLength); // Local XWindows Function Not a XServer function
                fontHeight = pXFontStruct->ascent + pXFontStruct->descent;
                XDrawString(gpDisplay, gWindow, gc, (iWinWidth / 2 - stringWidth / 2), (iWinHeight / 2 - fontHeight / 2), str, stringLength);
                
                break;
                
            case DestroyNotify:
                break;
                
            case 33:
                
                XUnloadFont(gpDisplay, pXFontStruct->fid);
                XFreeGC(gpDisplay, gc);
                
                Uninitialize();
                exit(0);
                
            default:
                break;
        }
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
    
    XStoreName(gpDisplay, gWindow, "Hello XWindows");
    
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
    
