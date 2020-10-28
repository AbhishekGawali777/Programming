#include <windows.h>
#include <tchar.h>

#define MAX 20

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

	TCHAR szWindowName[] = TEXT("Window");

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.lpszClassName = szWindowName;
	WndClass.lpszMenuName = NULL;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx FAILED"),TEXT("ERROR"),MB_ICONERROR);
		return -1;
	}

	hwnd = CreateWindow(
					szWindowName,
					TEXT("Row's Count"),
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
		MessageBox(NULL, TEXT("CreateWindow FAILED"),TEXT("ERROR"),MB_ICONERROR);
		return -1;
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if(-1 == bRet)
		{
			MessageBox(NULL, TEXT("GetMessage FAILED"),TEXT("ERROR"),MB_ICONERROR);
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
	static TEXTMETRIC tm;

	int iHeight;
	static int cyChar;
	static int cyClient;
	static int iNoOfRows;

	TCHAR szText[MAX];
	
	switch(iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);
		GetTextMetrics(hdc, &tm);
		ReleaseDC(hwnd, hdc);
		
		cyChar = tm.tmHeight + tm.tmExternalLeading;

		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		iHeight = 1;

		SetBkMode(hdc, TRANSPARENT);

		while(iHeight < cyClient)
		{
			TextOut(hdc, 0, iHeight, TEXT("A"), (int)_tcslen(TEXT("A")));
			iHeight = iHeight + cyChar;
		}

		_stprintf(szText, TEXT("No Of Rows= %d"), iNoOfRows);
		TextOut(hdc, 100, 0, szText, (int)_tcslen(szText));

		EndPaint(hwnd, &ps);
		break;
			
	case WM_SIZE:
		cyClient = HIWORD(lParam);
		iNoOfRows = (cyClient / cyChar);

		break;

	case WM_DESTROY:		
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, iMessage, wParam, lParam);
}