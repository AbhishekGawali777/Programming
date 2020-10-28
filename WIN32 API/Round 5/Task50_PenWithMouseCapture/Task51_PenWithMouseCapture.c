#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

#define MAX 10000

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

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.lpszClassName = szAppName;
	WndClass.lpszMenuName = NULL;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx FAILED"), TEXT("FAILUER"), MB_OK | MB_ICONERROR);
		return -1;
	}

	hwnd = CreateWindow(
					szAppName,
					TEXT("Pen With Mouse Capture"),
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
	
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	if(NULL == hwnd)
	{
		MessageBox(NULL, TEXT("CreateWindow FAILED"), TEXT("FAILUER"), MB_OK | MB_ICONERROR);
		return -1;
	}

	while(bRet = GetMessage(&msg,NULL, 0, 0) != 0)
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

	static int cxClient;
	static int cyClient;
	static int iCount;
	static POINT pt;
	static POINT apt[MAX];

	switch(iMessage)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		break;

	case WM_MOUSEMOVE:

		hdc = GetDC(hwnd);
		
		if(GET_X_LPARAM(lParam) >= 0 && GET_Y_LPARAM(lParam) >= 0)
		{
			if(pt.x != 0 && pt.y != 0)
			{
				if(pt.x > cxClient)
				{
					apt[iCount].x = 0;
					apt[iCount].y = pt.y;
				}
				else if(pt.y > cyClient)
				{
					apt[iCount].x = pt.x;
					apt[iCount].y = 0;
				}

				pt.x = 0;
				pt.y = 0;
			}

			if(wParam & MK_LBUTTON && iCount < MAX)
			{
				
				MoveToEx(hdc, apt[iCount].x, apt[iCount].y, NULL);
				LineTo(hdc, LOWORD(lParam), HIWORD(lParam));
				
				iCount++;
				
				apt[iCount].x = LOWORD(lParam);
				apt[iCount].y = HIWORD(lParam);
				
			}
		}
		else
		{
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
		}
		
		ReleaseDC(hwnd, hdc);
		
		break;

	case WM_LBUTTONDOWN:

		SetCapture(hwnd);
		iCount = 0;
		InvalidateRect(hwnd, NULL, TRUE);
		apt[iCount].x = LOWORD(lParam);
		apt[iCount].y = HIWORD(lParam);
		break;

	case WM_LBUTTONUP:
		InvalidateRect(hwnd, NULL, FALSE);
		ReleaseCapture();
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, iMessage, wParam, lParam);
}