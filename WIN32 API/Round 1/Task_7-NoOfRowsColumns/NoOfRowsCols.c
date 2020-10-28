#include <windows.h>
#include <tchar.h>

#define MAX 30

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

	TCHAR szWindowName[] = TEXT("Window");

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.hInstance = hInstance;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	WndClass.lpszClassName = szWindowName;
	WndClass.lpszMenuName = NULL;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx FAILED"),TEXT("ERROR"), MB_ICONERROR);
		exit(1);
	}

	hwnd = CreateWindow(
					szWindowName,
					TEXT("No Of Rows And Columns"),
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
		MessageBox(NULL, TEXT("CreateWindow FAILED"),TEXT("ERROR"), MB_ICONERROR);
		exit(2);
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while(bRet = GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if(-1 == bRet)
		{
			MessageBox(NULL, TEXT("GetMessage FAILED"),TEXT("ERROR"), MB_ICONERROR);
			exit(3);
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

	int iWidth;
	int iHeight;	
	static int cxCaps;
	static int cxChar;
	static int cyChar;	
	static int cxClient;
	static int cyClient;
	static int iNoOfRows;
	static int iNoOfCols;

	TCHAR szText[MAX];

	switch(iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);
		GetTextMetrics(hdc, &tm);
		ReleaseDC(hwnd, hdc);
		
		cyChar = tm.tmHeight + tm.tmExternalLeading;

		cxChar = tm.tmAveCharWidth + 4;
		cyChar = tm.tmHeight + tm.tmExternalLeading;

		if((tm.tmPitchAndFamily & 1) != 0)
			cxCaps = 3*cxChar/2;
		else
			cxCaps = cxChar;

		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		SetBkMode(hdc, TRANSPARENT);

		iWidth = 1;
		iHeight = 1;

		_stprintf(szText,TEXT("No. Of Rows = %d"),iNoOfRows);
		TextOut(hdc, 50, 15, szText, (int)_tcslen(szText));

		while(iHeight < cyClient)
		{
			TextOut(hdc, 0, iHeight, TEXT("A"), (int)_tcslen(TEXT("A")));
			iHeight = iHeight + cyChar;
		}
		
		_stprintf(szText,TEXT("No. Of Cols = %d"),iNoOfCols);
		TextOut(hdc, 50, 30, szText, (int)_tcslen(szText));
		
		while(iWidth < cxClient)
		{
			TextOut(hdc, iWidth, 0, TEXT("A"), (int)_tcslen(TEXT("A")));
			iWidth = iWidth + cxChar;
		}

		EndPaint(hwnd, &ps);
		break;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		iNoOfRows = (cyClient/ cyChar);
		iNoOfCols = (cxClient/ cxChar);

		break;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, iMessage, wParam, lParam);
}