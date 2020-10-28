#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include "MyHeader.h"

// Global Function Declarations

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// WinMain()

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, INT iCmdShow)
{
	// Local Variable Declarations
	MSG msg;
	HWND hwnd;
	BOOL bRet;
	RECT rcRect;
	WNDCLASSEX WndClass;

	TCHAR szAppName[] = { TEXT("MyWindow") };

	// Code

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = szAppName;
	WndClass.lpszMenuName = NULL;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	WndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcRect, 0);

	if (!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx Failed"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
		exit(0);
	}

	hwnd = CreateWindow(szAppName,
		TEXT("EnumWindows"),
		WS_MINIMIZE | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU,
		rcRect.right/4,
		rcRect.bottom /4,
		rcRect.right / 2,
		rcRect.bottom /2,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (NULL == hwnd)
	{
		MessageBox(NULL, TEXT("CreateWindow Failed"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
		exit(0);
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			MessageBox(NULL, TEXT("GetMessage Failed"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
			exit(0);
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return((INT)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uiMessage, WPARAM wParam, LPARAM lParam)
{
	// Local Variable Declartions

	HMODULE hDll = NULL;
	typedef int (*MakeSquareFunctionPointer)(int);
	MakeSquareFunctionPointer makeSquareFunctionPointer = NULL;

	int i = 5;
	int j;
	TCHAR str[255];

	
	// Code

	switch (uiMessage)
	{
	case WM_CREATE:

		// LoadLibrary(); returns Virtual address where dll is loaded.
		// HMODULE LoadLibrary(LPCWSTR);

		hDll = LoadLibrary(TEXT("MyMath.dll"));

		if (NULL == hDll)
		{
			MessageBox(hwnd, TEXT("LoadLibrary Failed"), TEXT("Error"), MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd);
		}

		// farproc GetProcAddress(HMODULE, LPCSTR);

		makeSquareFunctionPointer = (MakeSquareFunctionPointer)GetProcAddress(hDll, "MakeSquare");

		if (NULL == makeSquareFunctionPointer)
		{
			// BOOL FreeLibrary(HMODULE);

			FreeLibrary(hDll);
			MessageBox(hwnd, TEXT("GetProcAddress Failed"), TEXT("Error"), MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd);
		}

		j = makeSquareFunctionPointer(i);

		wsprintf(str, TEXT("Sqare Of %d Is %d"), i, j);
		MessageBox(hwnd, str, TEXT("Square"), MB_OK | MB_ICONINFORMATION);

		FreeLibrary(hDll);

		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(hwnd, uiMessage, wParam, lParam));
}
