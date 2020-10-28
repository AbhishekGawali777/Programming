#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <windows.h>

#define MAX 30

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

INT WINAPI WinMain(
				HINSTANCE hInstance,
				HINSTANCE hPrevInstance,
				LPSTR iCmdLine,
				INT iCmdShow
				)
{
	MSG msg;
	BOOL bRet;
	HWND hwnd;
	WNDCLASSEX WndClass;
	
	TCHAR szWndName[MAX]=TEXT("Window");

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW|CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbWndExtra = 0;
	WndClass.cbClsExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL,IDI_APPLICATION);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = szWndName;
	WndClass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);

	if(!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL,TEXT("RegisterClassEx FAILED"),TEXT("Window"),MB_ICONERROR);
		exit(0);
	}

	hwnd=CreateWindow(
					szWndName,
					TEXT("Columnwise Printing"),
					WS_OVERLAPPEDWINDOW,// | WS_VSCROLL | WS_HSCROLL,
					CW_USEDEFAULT,
					CW_USEDEFAULT,
					CW_USEDEFAULT,
					CW_USEDEFAULT,
					NULL,
					NULL,
					hInstance,
					NULL
					);

	if(NULL ==  hwnd)
	{
		MessageBox(NULL,TEXT("CrateWindow FAILED"),TEXT("Rowwise Printing"),MB_ICONERROR);
		exit(0);
	}

	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);

	while(0 != (bRet=GetMessage(&msg,NULL,0,0)))
	{
		if(-1 == bRet)
		{
			MessageBox(NULL,TEXT("GetMessage FAILED"),szWndName,MB_ICONERROR);
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
	static RECT rcRect;
	static TEXTMETRIC tm;

	INT iWidth;
	INT iCounter;
	static INT cxChar;
	static INT cyChar;
	static INT cxCaps;
	static INT cxClient;

	

	TCHAR *szText[]={TEXT("Talk"),TEXT("Is"),TEXT("Cheap"),
					TEXT("Show"),TEXT("Me"),TEXT("The"),
					TEXT("Code..."),TEXT("-Linus Torvalds")};

	switch(iMessage)
	{
	case WM_CREATE:
		hdc=GetDC(hwnd);
		GetTextMetrics(hdc,&tm);
		ReleaseDC(hwnd,hdc);
		
		cxChar = tm.tmAveCharWidth;

		if((tm.tmPitchAndFamily & 1) != 0)
			cxCaps = 3*(cxChar/2);
		// cxCaps for width of uppercase letters
		else
			cxCaps = cxChar;

		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		
		iWidth = 0;
		iCounter = 0;
	
		while(iCounter < 8)
		{
			TextOut(hdc, iWidth ,0 ,szText[iCounter], (int)_tcslen(szText[iCounter]));
			iWidth = iWidth + cxChar + (cxCaps * (int)_tcslen(szText[iCounter]));

			iCounter++;
		}

		EndPaint(hwnd,&ps);
		break;

	case WM_SIZE:
		GetClientRect(hwnd,&rcRect);
		cxClient = LOWORD(lParam);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	
	return DefWindowProc(hwnd,iMessage,wParam,lParam);
}

