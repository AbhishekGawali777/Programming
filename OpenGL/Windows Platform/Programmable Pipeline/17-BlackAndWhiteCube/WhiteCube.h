#ifndef _LIGHTSONCUBE_H__
#define _LIGHTSONCUBE_H__

// Header Files

#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<tchar.h>

#include<gl/glew.h>

#include<gl/GL.h>

// External Linkable Libraries

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")

// Macros

#define WIN_WIDTH	800
#define WIN_HEIGHT	600

#define MYICON		101

#define STONE_BITMAP	201
#define KUNDALI_BITMAP	202

// Function Declarations

void Display(void);
void Initialize(void);
void Resize(int, int);
GLfloat Update(GLfloat);
void Uninitialize(void);
void ToggleFullScreen(void);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#endif	// _LIGHTSONCUBE_H__
