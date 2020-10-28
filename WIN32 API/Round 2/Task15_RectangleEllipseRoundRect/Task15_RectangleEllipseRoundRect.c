#include <windows.h>
#include <tchar.h>

#define MAX 150

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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
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
					TEXT("Change Text Color"),
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
	PAINTSTRUCT ps;

	static int cxClient;
	static int cyClient;

	TCHAR szBuffer[MAX] = TEXT("Be Someone, The Person with you will Proud to Have You");


	switch(iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		SetTextColor(hdc, RGB(255, 0, 0));

		// Rectangle

		Rectangle(hdc, cxClient / 8, cyClient / 7, cxClient / 3, cyClient / 3);

		TextOut(hdc, cxClient / 7, cyClient / 6, TEXT("Rectangle"),
				_tcslen(TEXT("Rectangle")));	
		
		//	Ellipse

		SetTextColor(hdc, RGB(180, 180, 0));

		Ellipse(hdc, cxClient / 4 * 2, cyClient / 5, cxClient / 3 * 3, cyClient / 2 );
		
		TextOut(hdc, cxClient / 4* 2.2, cyClient / 3, TEXT("Ellipse"),
				_tcslen(TEXT("Ellipse")));	
		
		// Rounded Rectangle

		SetTextColor(hdc, RGB(0, 0, 255));

		RoundRect(hdc, cxClient / 8, cyClient / 7 * 4, cxClient / 12 * 5, cyClient / 3 * 2.8, cxClient / 16, cyClient / 9);

		TextOut(hdc, cxClient / 7, cyClient / 7 * 5, TEXT("Rounded Rectangle"),
				_tcslen(TEXT("Rounded Rectangle")));	
	
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