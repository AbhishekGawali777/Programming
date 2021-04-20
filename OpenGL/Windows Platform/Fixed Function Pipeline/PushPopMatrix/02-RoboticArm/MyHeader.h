#ifndef _MYHEADER_H__
#define _MYHEADER_H__

// Header Files 

#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<tchar.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include<corecrt_math_defines.h>

// External Libraries To Link

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")

// MACROS

#define WIN_WIDTH	800
#define WIN_HEIGHT	600

#define MYICON		101

// Function Declaration

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Drawing Function Ddeclarations

void Update(void);
void Display(void);
void Resize(int, int);
void Initialize(void);
void Uninitialize(void);
void ToggleFullScreen(void);

#endif  // _MYHEADER_H__
