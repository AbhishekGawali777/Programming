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

#pragma comment (lib, "Opengl32.lib")
#pragma comment (lib, "GlU32.lib")

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

// Drawing Functions

void DrawGraph(void);
void DrawCircle(void);
void DrawTriangle(void);
void DrawIncircle(void);
void DrawRectangle(void);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#endif			//  _MYHEADER_H__
