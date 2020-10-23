#ifndef _MYHEADER_H__
#define _MYHEADER_H__

// Header Files

#include<windows.h>
#include<stdio.h>
#include<tchar.h>
#include<gl/GL.h>
#include<gl/GLU.h>


// External Libraries

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "GLU32.lib")

// MACROS

#define WIN_WIDTH		800
#define WIN_HEIGHT		600

#define MYICON			101

// Global Function Declarations

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void Display(void);
void Resize(int, int);
void Initialize(void);
void Uninitialize(void);
void ToggleFullScreen(void);

// Global Variable Declarations

DWORD	dwStyle;
HDC		ghdc  = NULL;
HWND	ghwnd = NULL;
HGLRC	ghrc  = NULL;
FILE*	gpFile = NULL;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

bool gbFullScreen = false;
bool gbActiveWindow = false;



#endif		// _MYHEADER_H__
