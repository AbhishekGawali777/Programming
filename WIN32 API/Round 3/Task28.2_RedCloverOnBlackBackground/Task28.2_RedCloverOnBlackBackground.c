#include <math.h>
#include <tchar.h>
#include <windows.h>

#define TWO_PI (2.0 * 3.14159)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(
				HINSTANCE hInstance,
				HINSTANCE hPrevIndtance,
				LPSTR iCmdLine,
				INT iCmdShow
				)
{
	MSG msg;
	HWND hwnd;
	BOOL bRet;

	WNDCLASSEX WndClass;

	TCHAR szAppName[] = TEXT("Window");

	WndClass.style = CS_VREDRAW | CS_HREDRAW;
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = szAppName;
	WndClass.lpszMenuName = NULL;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx Failed"), TEXT("FAILUER"), MB_OKCANCEL | MB_ICONERROR);
		return -1;
	}

	hwnd = CreateWindow(
					szAppName,
					TEXT("Red Clover"),
					WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
					200,
					100,
					800,
					650,
				/*	WS_OVERLAPPEDWINDOW,
					CW_USEDEFAULT,
					CW_USEDEFAULT,
					CW_USEDEFAULT,
					CW_USEDEFAULT,*/
					NULL,
					NULL,
					hInstance,
					NULL
					);

	if(NULL == hwnd)
	{
		MessageBox(NULL, TEXT("CreateWindow Failed"), TEXT("FAILUER"), MB_OKCANCEL | MB_ICONERROR);
		return -1;
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while(bRet = GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if(-1 == bRet)
		{
			MessageBox(hwnd, TEXT("GetMessage Failed"), TEXT("FAILUER"), MB_ICONERROR | MB_OKCANCEL);
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	HPEN hPen;
	int iCounter;
	double fAngle;
	double fRadius;
	PAINTSTRUCT ps;
	HRGN hRgnTemp[6];
	static int cxClient;
	static int cyClient;
	static HRGN hRgnClip;

	switch(iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		SelectObject(hdc, hPen);

		SetViewportOrgEx(hdc, cxClient / 2, cyClient / 2, NULL);

		SelectClipRgn(hdc, hRgnClip);

		fRadius = _hypot(cxClient / 2.0, cyClient / 2.0);

		for(fAngle = 0.0; fAngle < TWO_PI; fAngle += TWO_PI / 360)
		{
			MoveToEx(hdc, 0, 0, NULL);
			LineTo(hdc, (int)fRadius * cos(fAngle) + 0.5, 
						(int)(-fRadius * sin(fAngle) + 0.5));
		}

		DeleteObject(hPen);
		EndPaint(hwnd, &ps);
		
		break;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		if(hRgnClip)
			DeleteObject(hRgnClip);

		hRgnTemp[0] = CreateEllipticRgn(0, cyClient / 3, cxClient / 2, 2 * cyClient / 3);

		hRgnTemp[1] = CreateEllipticRgn(cxClient / 2, cyClient / 3, cxClient, 2 * cyClient / 3);

		hRgnTemp[2] = CreateEllipticRgn(cxClient / 3, 0, 2 * cxClient / 3, cyClient / 2);

		hRgnTemp[3] = CreateEllipticRgn(cxClient / 3, cyClient / 2, 2 * cxClient / 3, cyClient);

		hRgnTemp[4] = CreateRectRgn(0, 0, 1, 1);

		hRgnTemp[5] = CreateRectRgn(0, 0, 1, 1);

		hRgnClip	= CreateRectRgn(0, 0, 1, 1);

		CombineRgn(hRgnTemp[4], hRgnTemp[0], hRgnTemp[1], RGN_OR);

		CombineRgn(hRgnTemp[5], hRgnTemp[2], hRgnTemp[3], RGN_OR);

		CombineRgn(hRgnClip,	hRgnTemp[4], hRgnTemp[5], RGN_XOR);

		for(iCounter = 0; iCounter < 6; iCounter++)
			DeleteObject(hRgnTemp[iCounter]);
			
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, iMessage, wParam, lParam);
}