#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, INT iCmdShow)
{
	// Variable Declaration
	MSG msg;
	HWND hwnd;
	INT cxScreenMidpoint;
	INT cyScreenMidpoint;
	
	TCHAR szAppName[] = TEXT("MyWindow");
	WNDCLASSEX WndClass;


	// Code

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = szAppName;
	WndClass.lpszMenuName = NULL;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClassEx(&WndClass);

	cxScreenMidpoint = GetSystemMetrics(SM_CXSCREEN) / 2;
	cyScreenMidpoint = GetSystemMetrics(SM_CYSCREEN) / 2;
	
	hwnd = CreateWindow(szAppName,
						TEXT("Centered Window"),
						WS_OVERLAPPEDWINDOW,
						cxScreenMidpoint - (800 / 2),
						cyScreenMidpoint - (600 / 2),
						800,
						600,
						NULL,
						NULL,
						hInstance,
						NULL
					);


	if (NULL == hwnd)
	{
		MessageBox(hwnd, TEXT("CreateWindow Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((INT)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uiMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uiMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return(0);
	}

	return(DefWindowProc(hwnd, uiMessage, wParam, lParam));
}