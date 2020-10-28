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

#define COORDINATE		0.5f

// Global Function Declarations

void Display(void);
void Initialize(void);
void Resize(int, int);
void Uninitialize(void);
void ToggleFullScreen(void);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#endif			//  _MYHEADER_H__
