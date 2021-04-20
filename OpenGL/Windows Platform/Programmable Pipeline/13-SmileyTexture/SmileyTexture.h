#ifndef _SMILEYTEXTURE_H__
#define _SMILEYTEXTURE_H__

/* Header Files */

#include<Windows.h>
#include<stdio.h>
#include<tchar.h>

#include<gl/glew.h>

#include<gl/GL.h>

/* External Linkable Libraries */

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")

/* Function Declarations */

// Macros

#define WIN_WIDTH	800
#define WIN_HEIGHT	600

#define MYICON		101

#define SMILEY_BITMAP	201

// Function Declarations

void Display(void);
void Initialize(void);
void Resize(int, int);
GLfloat Update(GLfloat);
void Uninitialize(void);
void ToggleFullScreen(void);
bool LoadGLTexture(GLuint*, TCHAR*);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#endif	// _SMILEYTEXTURE_H__
