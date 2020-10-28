#include <windows.h>
#include <tchar.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(
				HINSTANCE hInstance,
				HINSTANCE hPrevInsatnce,
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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszClassName = szClassName;
	WndClass.lpszMenuName = NULL;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;

	if(!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx FAILED"), TEXT("FAILUER"), MB_OK | MB_ICONERROR);
		return -1;
	}

	hwnd = CreateWindow(
					szClassName,
					TEXT("Basic Editor"),
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
		MessageBox(NULL, TEXT("CreateWindow FAILED"), TEXT("FAILUER"), MB_OK | MB_ICONERROR);
		return -1;
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while(bRet = GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if(-1 == bRet)
		{
			MessageBox(NULL, TEXT("GetMessage FAILED"), TEXT("FAILUER"), MB_OK | MB_ICONERROR);
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
	TEXTMETRIC tm;
//	PAINTSTRUCT ps;

	static int cxChar;
	static int cyChar;
	static int cxClient;
	static int cyClient;
	
	static int iLines;
	static int iLineLength;

	static int iCaretPosX;
	static int iCaretPosY;
	static int iCharWidth;

	TCHAR ch = '\n';

	switch(iMessage)
	{
	case WM_CREATE:

		hdc = GetDC(hwnd);
		GetTextMetrics(hdc, &tm);
		ReleaseDC(hwnd, hdc);

		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmHeight + tm.tmExternalLeading;

		break;
	
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		iLines = cyClient / cyChar;
		iLineLength = cxClient - cxChar;
		break;

	case WM_SETFOCUS:

		CreateCaret(hwnd, NULL, 0, cyChar);
		SetCaretPos(iCaretPosX, iCaretPosY * cyChar);
		ShowCaret(hwnd);
		
		break;

	case WM_KILLFOCUS:

		HideCaret(hwnd);
		DestroyCaret();

		break;

	case WM_KEYDOWN:

		switch(wParam)
		{
		case VK_LEFT:

			if(iCaretPosX == 0)
			{
				MessageBeep((UINT) -1);
				break;
			}
			HideCaret(hwnd);
			hdc = GetDC(hwnd);
			GetCharWidth32(hdc, ch, ch, &iCharWidth);
			ReleaseDC(hwnd, hdc);

			iCaretPosX = max(iCaretPosX - iCharWidth, 0);

			ShowCaret(hwnd);

			break;

		case VK_RIGHT:

			if(iLineLength  == iCaretPosX)
			{
				iCaretPosY = iCaretPosY * cyChar;
				break;
			}

			HideCaret(hwnd);
			hdc = GetDC(hwnd);
			GetCharWidth32(hdc, ch, ch, &iCharWidth);
			ReleaseDC(hwnd, hdc);

			iCaretPosX = iCaretPosX + iCharWidth;
			ShowCaret(hwnd);
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, iMessage, wParam, lParam);
}