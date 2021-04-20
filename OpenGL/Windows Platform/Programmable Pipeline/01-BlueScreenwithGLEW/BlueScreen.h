#ifndef _BLUESCREEN_H__
#define _BLUESCREEN_H__

// Header Files

#include<Windows.h>
#include<stdio.h>

// For this do add the path of the specified "Include Directory"
// to the Project Settings > Configuration Properties > C/C++ > General > Additional Include Directories 

// NOTE : This Header file should be included before <gl/GL.h>

#include<GL/glew.h>

#include<gl/GL.h>

// External linkable libraries

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")

// Macros

#define WIN_WIDTH		800
#define WIN_HEIGHT		600

#define MYICON			101

// Function Declarations

void Display(void);
void Initialize(void);
void Resize(int, int);
void Uninitialize(void);
void ToggleFullScreen(void);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#endif // _BLUESCREEN_H__
