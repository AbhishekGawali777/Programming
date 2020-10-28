#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

INT WINAPI WinMain(
				HINSTANCE hInstance,
				HINSTANCE hPrevInstance,
				LPSTR iCmdLine,
				INT  iCmdShow
				)
{
	MSG msg;
	HWND hwnd;
	BOOL bRet;
	WNDCLASSEX WndClass;

	TCHAR szAppName[]=TEXT("Window");

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW|CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.lpszClassName = szAppName;
	WndClass.lpszMenuName = NULL;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL,TEXT("RegisterClassEx FAILED"),TEXT("Window"),MB_ICONERROR);
		exit(0);
	}

	hwnd = CreateWindow(
					szAppName,
					TEXT("Desided Cordinates"),
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
	
	if(NULL == hwnd)
	{
		MessageBox(NULL,TEXT("CreateWindow FAILED"),TEXT("Window"),MB_ICONERROR);
		exit(0);
	}

	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);

	while(0 != (bRet=GetMessage(&msg,NULL,0,0)))
	{
		if(-1 == bRet)
		{
			MessageBox(NULL,TEXT("GetMessage FAILED"),TEXT("Window"),MB_ICONERROR);
			exit(0);
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(
					HWND hwnd,
					UINT iMessage,
					WPARAM wParam,
					LPARAM lParam
					)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rcClient;
	
	switch(iMessage)
	{
	case WM_PAINT:
		hdc=BeginPaint(hwnd, &ps);

		TextOut(hdc, rcClient.left, rcClient.top, TEXT("Hello Win32 Developers...!!!"),(int)_tcslen(TEXT("Hello Win32 Developers...!!!")));

		EndPaint(hwnd, &ps);
		break;
		 
	case WM_LBUTTONDOWN:

		rcClient.left = 100;
		rcClient.top = 100;
		rcClient.bottom = 300;
		rcClient.right = 300;

		InvalidateRect(hwnd, &rcClient, TRUE);

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd,iMessage,wParam,lParam);
}