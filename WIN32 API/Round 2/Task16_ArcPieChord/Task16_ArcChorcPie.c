#include <tchar.h>
#include <windows.h>

#define MAX 80

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

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.lpfnWndProc = WndProc;
	WndClass.hInstance = hInstance;
	WndClass.lpszClassName = szAppName;
	WndClass.lpszMenuName = NULL;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;

	if(!RegisterClassEx(&WndClass))
	{
		MessageBox(hwnd, TEXT("RegisterClassEx Failed"), TEXT("Failuer"), MB_ICONERROR | MB_OKCANCEL);
		return -1;
	}


	hwnd = CreateWindow(
					szAppName,
					TEXT("Arc Pie Chord"),
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
		MessageBox(hwnd, TEXT("CreateWindow Failed"), TEXT("Failuer"), MB_ICONERROR | MB_OKCANCEL);
		return -1;
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if(-1 == bRet)
		{
			MessageBox(hwnd, TEXT("GetMessage Failed"), TEXT("Failuer"), MB_ICONERROR | MB_OKCANCEL);
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
	PAINTSTRUCT ps;

	static int cxClient;
	static int cyClient;

	switch(iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		SetBkMode(hdc, TRANSPARENT);
		// Arc
		TextOut(hdc, cxClient / 11, cyClient / 16, TEXT("Arc"), _tcslen(TEXT("Arc")));

		Rectangle(hdc,cxClient / 7, cyClient / 12, cxClient / 5 * 2, cyClient / 3);

		Arc(hdc, cxClient / 6, cyClient / 12, cxClient / 5 * 2, cyClient / 3.5,
			cxClient / 7, cyClient / 14, cxClient / 7 * 2, cyClient / 3);

		// PIE

		TextOut(hdc, cxClient / 9 * 4, cyClient / 16, TEXT("Pie"), _tcslen(TEXT("Pie")));

		Rectangle(hdc,cxClient / 6 * 3, cyClient / 12, cxClient / 4 * 3, cyClient / 3);

		Pie(hdc,cxClient / 5 * 2.8, cyClient / 11, cxClient / 4 * 3, cyClient / 2.5,
			cxClient / 7 * 4, cyClient / 14, cxClient / 6 * 3, cyClient / 3);

		// Chord

		TextOut(hdc, cxClient / 9 * 4, cyClient / 11 * 5, TEXT("Chord"), _tcslen(TEXT("Chord")));

		Rectangle(hdc,cxClient / 4.6 * 2, cyClient / 13 * 7, cxClient / 8 * 5.4, cyClient / 12 * 9.8);

		Chord(hdc,cxClient / 5 * 2.8, cyClient / 14 * 7, cxClient / 8 * 5.4, cyClient / 12 * 9.8,
				cxClient / 5.3 * 2.8, cyClient / 17 * 7, cxClient / 9 * 5.4, cyClient  / 13 * 9.8);
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