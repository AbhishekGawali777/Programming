#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, INT iCmdShow)
{
	MSG msg;
	BOOL bRet;
	HWND hwnd;
	WNDCLASSEX WndClass;
	TCHAR szAppName[] = TEXT("Window");

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpszClassName = szAppName;
	WndClass.lpszMenuName = NULL;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.lpfnWndProc = WndProc;
	WndClass.hbrBackground = GetStockObject(BLACK_BRUSH);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;

	if (!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("FAILUER"), TEXT("RegisterClassEx FAILED"), MB_OKCANCEL | MB_ICONASTERISK);
		exit(1);
	}

	hwnd = CreateWindow(szAppName,
		TEXT("WM_PAINT"),
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

	if (NULL == hwnd)
	{
		MessageBox(NULL, TEXT("FAILUER"), TEXT("CreateWindow FAILED"), MB_OKCANCEL | MB_ICONASTERISK);
		exit(1);
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			MessageBox(NULL, TEXT("FAILUER"), TEXT("GetMessage FAILED"), MB_OKCANCEL | MB_ICONASTERISK);
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT uiMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;

	TCHAR szText[] = TEXT("Hello World..!!!");

	switch (uiMessage)
	{
	case WM_PAINT:
		
		GetClientRect(hwnd, &rc);

		hdc = BeginPaint(hwnd, &ps);

		SetBkColor(hdc, RGB(0, 0, 0));
		SetTextColor(hdc, RGB(0, 255, 0));

		DrawText(hdc, szText, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, uiMessage, wParam, lParam);
}