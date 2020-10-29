
// Header Files

#include<Windows.h>
#include<stdio.h>
#include<tchar.h>
#include"Containment.h"

// Function Declaration

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global Variable Declarations

ISum* pISum = NULL;
ISubtract* pISubtract = NULL;
IMultiplication* pIMultiplication = NULL;
IDivision* pIDivision = NULL;

// WinMain()

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
	// Local Variable Declarations

	MSG msg;
	BOOL bRet;
	HWND hwnd;
	HRESULT hr;
	WNDCLASSEX WndClass;
	TCHAR szAppName[] = TEXT("Class Factory");

	// Code

	hr = CoInitialize(NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("FAILUER"), TEXT("COM Library Cannot be Initialized"), MB_OKCANCEL | MB_ICONASTERISK);
		exit(0);
	}

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpszClassName = szAppName;
	WndClass.lpszMenuName = NULL;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.lpfnWndProc = WndProc;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;

	if (!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("FAILUER"), TEXT("RegisterClassEx FAILED"), MB_OKCANCEL | MB_ICONASTERISK);
		exit(0);
	}


	hwnd = CreateWindow(szAppName,
		TEXT("Abhishek Gawali."),
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

	CoUninitialize();
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uiMessage, WPARAM wParam, LPARAM lParam)
{
	// Local Variable Declaration

	HRESULT hr;
	int iNum1, iNum2, iResult;
	TCHAR szStr[255];
	// Code

	switch (uiMessage)
	{
	case WM_CREATE:

		hr = CoCreateInstance(CLSID_CSumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);

		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("ISum Interface Cannot be Obtained"), TEXT("FAILUER"), MB_OKCANCEL | MB_ICONASTERISK);
			DestroyWindow(hwnd);
		}

		iNum1 = 75;
		iNum2 = 25;

		pISum->SumOfTwoIntegers(iNum1, iNum2, &iResult);

		wsprintf(szStr, TEXT("Sum Of %d And %d Is %d"), iNum1, iNum2, iResult);

		MessageBox(NULL, szStr, TEXT("Answer"), MB_OKCANCEL | MB_ICONINFORMATION);

		hr = pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);

		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("ISubtract Interface Cannot be Obtained"), TEXT("FAILUER"), MB_OKCANCEL | MB_ICONASTERISK);
			DestroyWindow(hwnd);
		}

		pISum->Release();
		pISum = NULL;

		iNum1 = 100;
		iNum2 = 50;

		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iResult);

		wsprintf(szStr, TEXT("Subtraction Of %d And %d Is %d"), iNum1, iNum2, iResult);

		MessageBox(NULL, szStr, TEXT("Answer"), MB_OKCANCEL | MB_ICONINFORMATION);

		pISubtract->QueryInterface(IID_IMultiplication, (void**)&pIMultiplication);
		pISubtract->Release();
		pISubtract = NULL;

		iNum1 = 21;
		iNum2 = 52;

		pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, &iResult);
		
		wsprintf(szStr, TEXT("Multiplication Of %d And %d Is %d"), iNum1, iNum2, iResult);

		MessageBox(NULL, szStr, TEXT("Answer"), MB_OKCANCEL | MB_ICONINFORMATION);
		
		pIMultiplication->QueryInterface(IID_IDivision, (void**)&pIDivision);
		pIMultiplication->Release();

		iNum1 = 200;
		iNum2 = 25;

		pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iResult);
		
		wsprintf(szStr, TEXT("Division Of %d And %d Is %d"), iNum1, iNum2, iResult);

		MessageBox(NULL, szStr, TEXT("Answer"), MB_OKCANCEL | MB_ICONINFORMATION);
		
		pIDivision->Release();

		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, uiMessage, wParam, lParam);
}
