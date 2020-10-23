#include <stdio.h>
#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global Variable Declaration

FILE* gpFile = NULL;

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, INT iCmdShow)
{
	// Variable Declaration
	MSG msg;
	HWND hwnd;
	
	WNDCLASSEX WndClass;
	TCHAR szAppName[] = TEXT("MyWindow");

	if (fopen_s(&gpFile, "LogFile.txt", "w"))
	{
		MessageBox(NULL, TEXT("Cannot Create Desired File"), TEXT("ERROR..!!!"), MB_OK | MB_ICONERROR);
		exit(0);
	}

	// Code

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = szAppName;
	WndClass.lpszMenuName = NULL;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClassEx(&WndClass);

	hwnd = CreateWindow(szAppName,
						TEXT("Centered Window"),
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						NULL,
						NULL,
						hInstance,
						NULL
					);


	if (NULL == hwnd)
	{
		MessageBox(hwnd, TEXT("CreateWindow Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	fclose(gpFile);
	gpFile = NULL;
	
	return((INT)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uiMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uiMessage)
	{
	case WM_CREATE:
		fprintf(gpFile, "India Is My Country.\n");
		break;
	case WM_DESTROY:
		fprintf(gpFile, "Jai Hind...!!!");
		PostQuitMessage(0);
		return(0);
	}

	return(DefWindowProc(hwnd, uiMessage, wParam, lParam));
}