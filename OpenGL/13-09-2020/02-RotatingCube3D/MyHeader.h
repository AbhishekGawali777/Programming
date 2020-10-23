#ifndef __MYHEADER_H__
#define __MYHEADER_H__

// Header Files

#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<tchar.h>
#include<gl/GL.h>
#include<gl/GLU.h>

// External Library Linking

#pragma comment(lib, "OpenGl32.lib")
#pragma comment(lib, "GLU32.lib")

// MACROS

#define WIN_WIDTH   800
#define WIN_HEIGHT  600
#define MYICON      101

// Function Declaration

void Update(void);
void Display(void);
void Initialize(void);
void Resize(int, int);
void Uninitialize(void);
void ToggleFullScreen(void);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#endif      // __MYHEADER_H__
 