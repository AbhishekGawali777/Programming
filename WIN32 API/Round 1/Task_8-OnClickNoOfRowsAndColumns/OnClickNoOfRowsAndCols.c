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
	HWND hwnd;
	BOOL bRet;
	WNDCLASSEX WndClass;

	TCHAR szClassName[] = TEXT("Window");

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.hInstance = hInstance;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.lpszClassName = szClassName;
	WndClass.lpszMenuName = NULL;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx FAILED"), TEXT("FAILUER"), MB_OKCANCEL);
		exit(1);
	}

	hwnd = CreateWindow(
					szClassName,
					TEXT("On Click Events"),
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
		MessageBox(NULL, TEXT("CreateWindow FAILED"), TEXT("FAILUER"), MB_OKCANCEL);
		exit(2);
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while(bRet = GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if(-1 == bRet)
		{
			MessageBox(NULL, TEXT("GetMessage FAILED"), TEXT("FAILUER"), MB_OKCANCEL);
			exit(1);
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
	static int cxChar;
	static int cxCaps;
	static int cyChar;
	static int cyClient;
	static int cxClient;
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
		cxChar = tm.tmAveCharWidth + 3;

		if((tm.tmPitchAndFamily & 1) != 0)
			cxCaps = 3*cxChar/2;
		else
			cxCaps = cxChar;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		iWidth = 1;
		iHeight = 1;

		if(iNoOfRows > 0)
		{
			while(iHeight < cyClient)
			{
				_stprintf(szText,TEXT("%d"), iNoOfCols);
				TextOut(hdc, 0, iHeight, szText, (int)_tcslen(szText));
				iHeight = iHeight + cyChar;
			}
		
			while(iWidth < cxClient)
			{	
				_stprintf(szText,TEXT("%d"), iNoOfRows);
				TextOut(hdc, 0, iHeight, szText, (int)_tcslen(szText));
				iWidth = iWidth + cxChar;
			}
		}
		else
		{
			while(iHeight < cyClient)
			{
				TextOut(hdc, 0, iHeight, TEXT("R"), (int)_tcslen(TEXT("R")));
				iHeight = iHeight + cyChar;
			}
		
			while(iWidth < cxClient)
			{
				TextOut(hdc, iWidth, 0, TEXT("C"), (int)_tcslen(TEXT("C")));
				iWidth = iWidth + cxChar;
			}
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		iNoOfRows = 0;
		iNoOfCols = 0;
		break;

	case WM_LBUTTONDOWN:
		iNoOfRows++;
		
		if(10 == iNoOfCols)
			iNoOfCols = 0;
		else
			iNoOfCols++;

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, iMessage, wParam, lParam);
}