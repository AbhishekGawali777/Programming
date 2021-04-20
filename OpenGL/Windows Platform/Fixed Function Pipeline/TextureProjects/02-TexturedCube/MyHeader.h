#ifndef __MYHEADER_H__
#define __MYHEADER_H__

// Header Files

#include<Windows.h>
#include<stdio.h>
#include<tchar.h>
#include<gl/GL.h>
#include<gl/GLU.h>

// External Libraries

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

// MACROS

#define		WIN_WIDTH		800
#define		WIN_HEIGHT		600

#define		MYICON			101

#define		KUNDALI_BITMAP	201

// Function Declarations

void Update(void);
void Display(void);
void DrawCube(void);
void Initialize(void);
void Resize(int, int);
void Uninitialize(void);
void ToggleFullScreen(void);

bool LoadGLTexture(GLuint*, TCHAR*);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#endif		// __MYHEADER_H__
