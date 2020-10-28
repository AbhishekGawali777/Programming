#ifndef __MYHEADER_H__
#define __MYHEADER_H__

// Header Files

#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<tchar.h>
#include<GL/GL.h>
#include<GL/GLU.h>
#include<corecrt_math_defines.h>

// MACROS

#define MYICON 101

#define WIN_WIDTH	800
#define WIN_HEIGHT	600

#define DEGTORAD(X)	 (GLfloat)(X * (M_PI / 180.0f))

// Extrernal Libraries

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")

// Function Declarations

void Display(void);
void Resize(int, int);
void Initialize(void);
void Uninitialize(void);
void ToggleFullScreen(void);

// Drawing Functions

void DrawCube3D(void);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#endif

