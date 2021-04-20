#ifndef __SPHERE_H__
#define __SPHERE_H__

// Header Files

#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<gl/GL.h>
#include<gl/GLU.h>



#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

// MACROS

#define WIN_WIDTH	800
#define WIN_HEIGHT	600

#define MYICON		101

// Function Delcarations

void Update(void);
void Display(void);
void Initialize(void);
void Resize(int, int);
void Uninitialize(void);
void ToggleFullScreen(void);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#endif // __SPHERE_H__
