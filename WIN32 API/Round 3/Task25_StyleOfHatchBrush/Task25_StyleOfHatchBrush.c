#include <windows.h>
#include <tchar.h>

#define MAX 60

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

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
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
					TEXT("Style Of Hatch Brush"),
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
		MessageBox(NULL, TEXT("CreateWindow Failed"), TEXT("FAILUER"), MB_OKCANCEL | MB_ICONERROR);
		return -1;
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if(-1 == bRet)
		{
			MessageBox(NULL, TEXT("GetMessage Failed"), TEXT("FAILUER"), MB_OKCANCEL | MB_ICONERROR);
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
	HBRUSH hBrush;
	PAINTSTRUCT ps;

	static int cxClient;
	static int cyClient;

	switch(iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		
	/*	hPen = CreatePen(PS_DASHDOT, 1, RGB(255, 0, 0));
		SelectObject(hdc, hPen); */

		hBrush = (HBRUSH)SelectObject(hdc,CreateHatchBrush(BS_INDEXED, RGB(0, 0, 255)));

		Rectangle(hdc, cxClient / 8, cyClient / 8, cxClient / 8 * 7, cyClient / 8 * 7);
		
		MoveToEx(hdc, 0, 0, NULL);
		LineTo(hdc, cxClient, cyClient);

		MoveToEx(hdc, cxClient , 0, NULL);
		LineTo(hdc, 0, cyClient);
		
		hBrush = (HBRUSH)SelectObject(hdc,CreateHatchBrush(BS_SOLID, RGB(255, 0, 0)));
			
		Ellipse(hdc, cxClient / 8, cyClient / 8, 7 * cxClient / 8, 7 * cyClient / 8);
		
		hBrush = (HBRUSH)SelectObject(hdc,CreateHatchBrush(BS_DIBPATTERN, RGB(0, 255, 0)));

		RoundRect(hdc, cxClient / 4, cyClient / 4, 3 * cxClient /4, 3 * cyClient / 4,
				cxClient / 4, cyClient / 4);
		
		DeleteObject(hBrush);
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