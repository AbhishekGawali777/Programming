#include <windows.h>
#include <tchar.h>

#define MAX 50

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(
				HINSTANCE hInstance,
				HINSTANCE hPrevInstance,
				LPSTR szCmdLine,
				INT iCmdShow
				)
{
	MSG msg;
	BOOL bRet;
	HWND hwnd;

	WNDCLASSEX WndClass;

	TCHAR szAppName[] = TEXT("Window");

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = szAppName;
	WndClass.lpszMenuName = NULL;
	WndClass.hInstance = hInstance;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx FAILED"), TEXT("FAILUER"), MB_OKCANCEL | MB_ICONERROR);
		return -1;
	}

	hwnd = CreateWindow(
					szAppName,
					TEXT("Gap Color Change"),
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
		MessageBox(NULL, TEXT("CreateWindow FAILED"), TEXT("FAILUER"), MB_OKCANCEL | MB_ICONERROR);
		return -1;
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if(-1 == bRet)
		{
			MessageBox(NULL, TEXT("GetMessage FAILED"), TEXT("FAILUER"), MB_OKCANCEL | MB_ICONERROR);
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
	HPEN hPen;
	HBRUSH hBrush;
	PAINTSTRUCT ps;

	static int cxClient;
	static int cyClient;

	switch(iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		hBrush = (HBRUSH)SelectObject(hdc, GetStockObject(BLACK_BRUSH));

		hPen = (HPEN)SelectObject(hdc, CreatePen(PS_DASHDOT, 1, RGB(186, 45, 189)));

		SetBkColor(hdc, RGB(249, 195, 19));

		Rectangle(hdc, cxClient / 8, cyClient / 8, cxClient / 8 * 7, cyClient / 8 * 7);
		
		hPen = (HPEN)SelectObject(hdc, CreatePen(PS_DASH, 1, RGB(59, 189, 45)));
		
		SetBkColor(hdc, RGB(255, 0,255));
		
		LineTo(hdc, cxClient, cyClient);
		MoveToEx(hdc, cxClient , 0, NULL);
		LineTo(hdc, 0, cyClient);
		
		hPen = (HPEN)SelectObject(hdc, CreatePen(PS_DASHDOTDOT, 1, RGB(45, 189, 170)));
		
		SetBkColor(hdc, RGB(190, 0, 190));

		Ellipse(hdc, cxClient / 8, cyClient / 8, 7 * cxClient / 8, 7 * cyClient / 8);

		hPen = (HPEN)SelectObject(hdc, CreatePen(PS_DOT, 1, RGB(64, 45, 189)));
		
		SetBkColor(hdc, RGB(249, 19, 19));

		RoundRect(hdc, cxClient / 4, cyClient / 4, 3 * cxClient /4, 3 * cyClient / 4,
				cxClient / 4, cyClient / 4);
		
		DeleteObject(hPen);
		DeleteObject(hBrush);

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