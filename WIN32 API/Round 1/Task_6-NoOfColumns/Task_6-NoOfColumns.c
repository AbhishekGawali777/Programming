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

	int iWidth;
	static int cxChar;
	static int cxCaps;
	static int cxClient;
	static int iNoOfColumns;

	TCHAR szText[MAX];
	
	switch(iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);
		GetTextMetrics(hdc, &tm);
		ReleaseDC(hwnd, hdc);
		
		cxChar = tm.tmAveCharWidth ;

		if((tm.tmPitchAndFamily & 1) != 0)
			cxCaps = 3*cxChar/2 ;
		else
			cxCaps = cxChar;

		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		iWidth = 1;

		SetBkMode(hdc, TRANSPARENT);

		while(iWidth < cxClient)
		{
			TextOut(hdc, iWidth, 0, TEXT("A"), (int)_tcslen(TEXT("A")));
			iWidth = iWidth + cxChar;
		}

		_stprintf(szText, TEXT("No Of Columns= %d"), iNoOfColumns);
		TextOut(hdc, 0, 100, szText, (int)_tcslen(szText));

		EndPaint(hwnd, &ps);
		break;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		iNoOfColumns = (cxClient / cxChar);

		break;

	case WM_DESTROY:		
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, iMessage, wParam, lParam);
}