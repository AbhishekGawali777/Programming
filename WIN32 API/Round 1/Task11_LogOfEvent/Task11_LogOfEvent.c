#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include "LogOfEvent.h"

#define  MAX 100

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(
				HINSTANCE hInstance,
				HINSTANCE hPrevInstance,
				LPSTR szCmdLine,
				INT iCmdShow
				)

{
	MSG msg;
	HWND hwnd;
	BOOL bRet;
	WNDCLASSEX WndClass;

	TCHAR szAppName[] = TEXT("Window");

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.hInstance = hInstance;
	WndClass.lpszClassName = szAppName;
	WndClass.lpszMenuName = NULL;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	if(!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx FAILED"), TEXT("FAILUER"), MB_ICONERROR | MB_OKCANCEL);
		return -1;
	}

	hwnd = CreateWindow(
					szAppName,
					TEXT("Event Logs"),
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
		MessageBox(NULL, TEXT("CreateWindow FAILED"), TEXT("FAILUER"), MB_ICONERROR | MB_OKCANCEL);
		return -1;
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while(bRet = GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if(-1 == bRet)
		{
			MessageBox(NULL, TEXT("GetMessage FAILED"), TEXT("FAILUER"), MB_ICONERROR | MB_OKCANCEL);
			return -1;
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
	static int iCounter1;
	static int iCounter2;
	static int iCounter3;
	static int iCounter4;
	static int iCounter5;
	static int iCounter6;
	static int iCounter7;
	// if concerns with value 1 or 0
	// ifdef concerns with definition not value

#if LOG
	
	// static file pointer is very must in such cases.
	
	static FILE* fp = NULL;
	TCHAR szBuffer[MAX];

#endif
	switch(iMessage)
	{
	case WM_CREATE:
#if LOG
		fp = fopen("My Log.txt", "w");

		if(NULL == fp)
		{
			MessageBox(NULL, TEXT("My Log.txt Cannot Open"), TEXT("FAILUER"), MB_ICONERROR | MB_OKCANCEL);
			return -1;
		}

		_stprintf_s(szBuffer, MAX, TEXT("Creating Window %d Times\n"), ++iCounter1);
		_fputts(szBuffer, fp);
#endif
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
#if LOG
		_stprintf_s(szBuffer, MAX, TEXT("Painting Window %d Times\n"), ++iCounter2);
		_fputts(szBuffer, fp);
#endif
		EndPaint(hwnd, &ps);
		break;

	case WM_KEYDOWN:
#if LOG
		_stprintf_s(szBuffer, MAX, TEXT("You Pressed a Key %d Times\n"), ++iCounter3);
		_fputts(szBuffer, fp);
#endif
		break;

	case WM_KEYUP:
#if LOG
		_stprintf_s(szBuffer, MAX, TEXT("You Leave A Pressed Key %d Times\n"), ++iCounter4);
		_fputts(szBuffer, fp);
#endif
		break;

	case WM_LBUTTONDOWN:
#if LOG
		_stprintf_s(szBuffer, MAX, TEXT("You Pressed Left Mouse Button %d Times\n"), ++iCounter5);
		_fputts(szBuffer, fp);
#endif
		break;

	case WM_RBUTTONDOWN:
#if LOG
		_stprintf_s(szBuffer, MAX, TEXT("You Pressed Right Mouse Button %d Times\n"), ++iCounter6);
		_fputts(szBuffer, fp);
#endif
		break;

	case WM_DESTROY:
#if LOG
		_stprintf_s(szBuffer, MAX, TEXT("You Closed The File %d Time\n"), ++iCounter7);
		_fputts(szBuffer, fp);
		fclose(fp);
		fp = NULL;
#endif
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, iMessage, wParam, lParam);
}