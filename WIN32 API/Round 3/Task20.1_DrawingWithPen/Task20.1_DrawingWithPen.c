#include <tchar.h>
#include <windows.h>

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

	TCHAR szClassName[] = TEXT("Window");

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.lpszClassName = szClassName;
	WndClass.lpszMenuName = NULL;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


	if(!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx FAILED"),TEXT("FAILURE"), MB_ICONERROR);
		return -1;
	}

	hwnd = CreateWindow(
					szClassName,
					TEXT("Drawing With Pen"),
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
		MessageBox(NULL, TEXT("CreateWindow FAILED"),TEXT("FAILURE"), MB_ICONERROR);
		return -1;
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while(bRet = GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if(-1 == bRet)
		{
			MessageBox(NULL, TEXT("MessageBox FAILED"),TEXT("FAILURE"), MB_ICONERROR);
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

		hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

		hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);

		SelectObject(hdc, hBrush);
		SelectObject(hdc, hPen);

		Rectangle (hdc, cxClient / 8, cyClient / 8,7 * cxClient / 8, 7 * cyClient / 8) ;
		
		MoveToEx (hdc, 0, 0, NULL) ;
		LineTo (hdc, cxClient, cyClient) ;
		MoveToEx (hdc, 0, cyClient, NULL) ;
		LineTo (hdc, cxClient, 0) ;
		
		Ellipse (hdc, cxClient / 8, cyClient / 8, 7 * cxClient / 8, 7 * cyClient / 8) ;
	
		RoundRect (hdc, cxClient / 4, cyClient / 4, 3 * cxClient / 4, 
						3 * cyClient / 4, cxClient / 4, cyClient / 4);
	
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