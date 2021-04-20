#ifndef _WHITEPYRAMID_H__
#define _WHITEPYRAMID_H__

/* Header Files */

#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<tchar.h>

#include<gl/glew.h>

#include<gl/GL.h>

#include"../../vmath.h"

/* External Linkable Libraries */

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")


/* Macros */

#define MYICON 101

#define WIN_WIDTH	800
#define WIN_HEIGHT	600

/* Function Declarations */

void Display(void);
void Initialize(void);
void Uninitialize(void);
GLfloat Update(GLfloat);
void Resize(GLint, GLint);
void ToggleFullScreen(void);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#endif // _WHITEPYRAMID_H__
