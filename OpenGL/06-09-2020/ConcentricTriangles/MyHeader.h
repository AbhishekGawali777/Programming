#ifndef _MYHEADER_H__
#define _MYHEADER_H__

// Header Files

#include<windows.h>
#include<math.h>
#include<stdio.h>
#include<tchar.h>
#include<gl/GL.h>
#include<gl/GLU.h>

// External Libraries

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")

// MACROS

#define PI				3.141592653589793238
#define WIN_WIDTH		800
#define WIN_HEIGHT		600

#define MYICON			101

// Global Function Declarations

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
FILE*	gpFile = NULL;

WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

bool gbFullScreen = false;
bool gbActiveWindow = false;

typedef struct COLOR
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
}colors;


colors gfColors[] = {	gfColors[0].r = 1.0f, gfColors[0].g = 0.0f, gfColors[0].b = 0.0f,
						gfColors[1].r = 0.0f, gfColors[1].g = 1.0f, gfColors[1].b = 0.0f,
						gfColors[2].r = 0.0f, gfColors[2].g = 0.0f, gfColors[2].b = 1.0f,
						gfColors[3].r = 1.0f, gfColors[3].g = 0.0f, gfColors[3].b = 1.0f,
						gfColors[4].r = 0.0f, gfColors[4].g = 1.0f, gfColors[4].b = 1.0f,
						gfColors[5].r = 1.0f, gfColors[5].g = 1.0f, gfColors[5].b = 0.0f,
						gfColors[6].r = 1.0f, gfColors[6].g = 1.0f, gfColors[6].b = 1.0f,
						gfColors[7].r = 0.5f, gfColors[7].g = 0.5f, gfColors[7].b = 0.5f,
						gfColors[8].r = 1.0f, gfColors[8].g = 0.5f, gfColors[8].b = 0.0f,
						gfColors[9].r = 0.80f, gfColors[9].g = 0.56f, gfColors[9].b = 1.0f
};

#endif			//  _MYHEADER_H__
