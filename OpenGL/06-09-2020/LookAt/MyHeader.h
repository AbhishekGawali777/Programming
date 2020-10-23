#ifndef _MYHEADER_H__
#define _MYHEADER_H__

// Header Files

#include<windows.h>
#include<stdio.h>
#include<tchar.h>
#include<gl/GL.h>
#include<gl/GLU.h>

// External Libraries

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")

// MACROS

#define WIN_WIDTH		800
#define WIN_HEIGHT		600
#define MYICON			101

// Global Function Declarations

void Update(void);
void Display(void);
void Initialize(void);
void Resize(int, int);
void Uninitialize(void);
void ToggleFullScreen(void);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global Variable Declarations

DWORD	dwStyle;
HDC		ghdc = NULL;
HGLRC	ghrc = NULL;
HWND	ghwnd = NULL;
FILE* gpFile = NULL;

WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

GLfloat tAngle = 0.0f;
GLfloat rAngle = 0.0f;

bool gbFullScreen = false;
bool gbActiveWindow = false;

#endif			//  _MYHEADER_H__

