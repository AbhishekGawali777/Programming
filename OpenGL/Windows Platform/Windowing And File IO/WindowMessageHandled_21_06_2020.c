#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, INT iCmdShow)
{
	MSG msg;
	HWND hwnd;
	BOOL bRet;
	WNDCLASSEX WndClass;

	TCHAR szAppName[] = TEXT("MyWindow");

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.hInstance = hInstance;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszClassName = szAppName;
	WndClass.lpszMenuName = NULL;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("CreateWindow Failed"), TEXT("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		exit(-1);
	}

	hwnd = CreateWindow(szAppName, TEXT("Abhishek Gawali"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	if (NULL == hwnd)
	{
		MessageBox(hwnd, TEXT("CreateWindow Failed"), TEXT("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		exit(-1);
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (-1 == bRet)
		{
			MessageBox(hwnd, TEXT("GetMessage Failed"), TEXT("ERROR"), MB_OK | MB_ICONEXCLAMATION);
			exit(-1);
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uiMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uiMessage)
	{
	case WM_CREATE:
		MessageBox(hwnd, TEXT("WM_CREATE Is Recieved"), TEXT("MyMessage"), MB_OK | MB_ICONEXCLAMATION);
		break;

	case WM_KEYDOWN:
		MessageBox(hwnd, TEXT("WM_KEYDOWN Is Recieved"), TEXT("MyMessage"), MB_OK | MB_ICONEXCLAMATION);
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("WM_LBUTTONDOWS Is Recieved"), TEXT("MyMessage"), MB_OK | MB_ICONEXCLAMATION);
		break;

	case WM_RBUTTONDOWN:
		MessageBox(hwnd, TEXT("WM_RBUTTONDOWN Is Recieved"), TEXT("MyMessage"), MB_OK | MB_ICONEXCLAMATION);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(hwnd, uiMessage, wParam, lParam));
}