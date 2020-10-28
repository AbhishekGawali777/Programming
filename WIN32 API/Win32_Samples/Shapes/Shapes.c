#include <tchar.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>

#define MAX		150
#define NUM		1000
#define TWOPI	(2 * 3.14)

	
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR szCmdLine,
				   int iCmdShow
					)
{
	MSG msg;
	BOOL bRet;
	HWND hwnd;
	WNDCLASSEX WndClass;

	TCHAR szAppName[]=TEXT("Window");

	WndClass.cbSize=sizeof(WNDCLASSEX);
	WndClass.style=CS_HREDRAW|CS_VREDRAW;
	WndClass.lpfnWndProc= WndProc;
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hInstance=hInstance;
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hCursor=LoadCursor(NULL,IDI_APPLICATION);
	WndClass.lpszMenuName=NULL;
	WndClass.lpszClassName=szAppName;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hIconSm=LoadIcon(NULL,IDI_APPLICATION);

	if(!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL,TEXT("Class Registration FAILED"),TEXT("MY WINDOW"),MB_OK);
		exit(0);
	}

	hwnd=CreateWindow(
					szAppName,
					TEXT("SHAPES"),
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
		MessageBox(NULL,TEXT("Create Window FAILED"),TEXT("Practice"),MB_OK);
		exit(0);
	}

	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);

	while(0 != (bRet=GetMessage(&msg,NULL,0,0)))
	{
		if(-1 == bRet)
		{
			MessageBox(NULL,TEXT("GetMessage FAILED"),TEXT("Practice"),MB_ICONERROR);
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
//	POINT pt;
//	RECT rcRect;
	TEXTMETRIC tm;
	PAINTSTRUCT ps;
	int iCounter;
	static int cxClient, cyClient;

	static int cxChar;
	static int cyChar;
	static int cxCaps;

//	POINT apt[5] = {100, 100, 300, 100, 300, 200, 100, 200, 100, 100};
	POINT apt[NUM];

	switch(iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);

		GetTextMetrics(hdc, &tm);
		
		cxChar = tm.tmAveCharWidth;

		if(tm.tmPitchAndFamily & 1)
		{
			cxCaps = 3 * (cxChar / 2);
		}
		else
			cxCaps = cxChar;

		cyChar = tm.tmHeight + tm.tmExternalLeading;

		ReleaseDC(hwnd, hdc);

		break;
	case WM_PAINT:

		hdc = BeginPaint(hwnd, &ps);
		
/*		GetClientRect(hwnd, &rcRect);

		for(x = 0; x < rcRect.right; x = x + 100)
		{
			MoveToEx(hdc, x, 0, NULL);
			LineTo(hdc, x, rcRect.bottom);
		}

		for(y = 0; y < rcRect.bottom; y = y + 100)
		{
			MoveToEx(hdc, 0, y, NULL);
			LineTo(hdc, rcRect.right, y);
		}
*/
		
		//
		// Tried With Different logic
		//

/*		
		for(iCounter = 0; iCounter < cxClient; iCounter = iCounter + 100)
		{
			MoveToEx(hdc, iCounter, 0, NULL);
			LineTo(hdc, iCounter, cyClient);
		}

		for(iCounter = 0; iCounter < cyClient; iCounter = iCounter + 100)
		{
			MoveToEx(hdc, 0, iCounter, NULL);
			// right to left drawing hotay 
			// From cxClient(i.e, x) to 
			LineTo(hdc, cxClient, iCounter);
		}
*/
		
		//
		//	Rectangle Using MoveToEx, LineTo
		//
		
/*		MoveToEx(hdc, apt[0].x, apt[0].y, NULL); 
		
		// Third Parameter can be last Co-ordinate if you want.
		// In Most Cases While Programming it's not required.

		for(iCounter = 1; iCounter < 5; iCounter++)
		{
			LineTo(hdc, apt[iCounter].x, apt[iCounter].y);
		}

*/

		//
		// Rectangle Using Polyline
		//

/*
		MoveToEx(hdc, apt[0].x, apt[0].y, NULL);
		Polyline(hdc, apt, sizeof(apt) / sizeof(POINT));
*/	

		//
		// Rectangle Using PolyLineTo
		//
/*
		MoveToEx(hdc, apt[0].x, apt[0].y, NULL);
		PolylineTo(hdc, apt + 1, 4);
*/
		//
		// SINWAVE Drawing.
		//
	
/*		MoveToEx(hdc, 0, cyClient / 2, NULL);
		LineTo(hdc, cxClient, cyClient / 2);
		
		for(iCounter = 0; iCounter < NUM; iCounter++)
		{
			apt[iCounter].x = iCounter * cxClient / NUM;
			apt[iCounter].y = (int) (cyClient / 2 * (1 - sin(TWOPI * iCounter / NUM)));
		}

		Polyline(hdc, apt, NUM);
*/

		// Rectangle

//		Rectangle(hdc, cxChar * 10, cyChar * 10, cxClient / 3, cyClient / 2);

		//Ellipse

//		Ellipse(hdc, cxChar * 10, cyChar * 10, cxClient / 3, cyClient / 2);

		// Rounded Rectangle

//		RoundRect(hdc, 100, 100, 300, 200, 100 - 10, 100 - 10);

/*		RoundRect(hdc, cxChar * 10, cyChar * 10, cxClient / 3, cyClient / 2,
			((cxChar * 10) - cxChar * 3), ((cyChar * 10) - (cyChar * 3)));
*/

		// Arc

//		Arc(hdc, 100, 100, 300, 400, 200, 100, 100, 200);

		// Chord

//		Chord(hdc, 100, 100, 300, 400, 200, 100, 100, 200);

		// Pie

//		Pie(hdc, 100, 100, 300, 400, 200, 100, 100, 200);
		
		EndPaint(hwnd, &ps);
		break;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		
		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, iMessage, wParam, lParam);
}