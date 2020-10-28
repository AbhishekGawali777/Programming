#include <windows.h>
#include <tchar.h>

#define MAX 60

int g_cxClient;
int g_cyClient;

void DrawRectangle(HWND);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(
				HINSTANCE hInstance,
				HINSTANCE hPrevIndtance,
				LPSTR iCmdLine,
				INT iCmdShow
				)
{
	MSG msg;
	HWND hwnd;

	WNDCLASSEX WndClass;

	TCHAR szAppName[] = TEXT("Window");

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = szAppName;
	WndClass.lpszMenuName = NULL;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx Failed"), TEXT("FAILUER"), MB_OKCANCEL | MB_ICONERROR);
		return -1;
	}

	hwnd = CreateWindow(
					szAppName,
					TEXT("Transparent Pen Gap"),
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
		MessageBox(NULL, TEXT("CreateWindow Failed"), TEXT("FAILUER"), MB_OKCANCEL | MB_ICONERROR);
		return -1;
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			DrawRectangle(hwnd);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch(iMessage)
	{
	case WM_SIZE:
		g_cxClient = LOWORD(lParam);
		g_cyClient = HIWORD(lParam);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, iMessage, wParam, lParam);
}

void DrawRectangle(HWND hwnd)
{
	HDC hdc;
	RECT rcRect;
	HBRUSH hBrush;

	if(g_cxClient == 0 || g_cyClient == 0)
		return;

	SetRect(&rcRect, rand() % g_cxClient,
					 rand() % g_cyClient,
					 rand() % g_cxClient,
					 rand() % g_cyClient
					 );

	hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));

	hdc = GetDC(hwnd);

	FillRect(hdc, &rcRect, hBrush);

	ReleaseDC(hwnd, hdc);

	DeleteObject(hBrush);

	Sleep(500);
}