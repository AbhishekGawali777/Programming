#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include "MyHeader.h"

#define MAX				128
#define INSTANCEFOUND	0x98FC
#define MYTIMER			100

// Global Function Declarations

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global Variable Declarations
DWORD dwIcon;
DWORD dwIconSm;
FILE* gpFile = NULL;
HWND gWindowHandle = NULL;
HWND gChildWindowHandle = NULL;
static bool gbInstance = FALSE;

// WinMain()

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, INT iCmdShow)
{
	// Local Variable Declarations
	MSG msg;
	HWND hwnd;
	BOOL bRet;
	RECT rcRect;
	WNDCLASSEX WndClass;

	TCHAR szAppName[] = { TEXT("MyWindow") };

	// Code

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = szAppName;
	WndClass.lpszMenuName = NULL;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	WndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcRect, 0);

	if (!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx Failed"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
		exit(0);
	}

	hwnd = CreateWindow(szAppName,
		TEXT("EnumWindows"),
		WS_MINIMIZE | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU,
		rcRect.right / 2,
		rcRect.top,
		rcRect.right / 22 * 11,
		rcRect.bottom,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (NULL == hwnd)
	{
		MessageBox(NULL, TEXT("CreateWindow Failed"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
		exit(0);
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			MessageBox(NULL, TEXT("GetMessage Failed"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
			exit(0);
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return((INT)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uiMessage, WPARAM wParam, LPARAM lParam)
{
	// Function Declarations
	
	void Uninitialize(void);
	BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

	// Variable Declarations
	static HICON ghIcon = NULL;
	static FILE* pFile = NULL;
	MENUBARINFO mbi;
	mbi.cbSize = { sizeof(MENUBARINFO) };
	TCHAR wCharacter;
	HMENU hmenu, hSubMenu;
	MENUITEMINFO mii;
	TCHAR szBuffer[20];
	mii.cbSize = { sizeof(MENUITEMINFO) };
	mii.dwTypeData = NULL;
	mii.cch = 0;
	HFONT hfont;
	int Item_ID;
	// Code

	switch (uiMessage)
	{
	case WM_CREATE:

		if (fopen_s(&gpFile, "Log.txt", "w"))
		{
			MessageBox(hwnd, TEXT("Log File Creation Failed"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
			DestroyWindow(hwnd);
		}
		else
		{
			fprintf(gpFile, "Log File Created Successfully.\n\n");
		}
		
		if (fopen_s(&pFile, "Hello.txt", "r"))
		{
			MessageBox(hwnd, TEXT("File Opening Failed"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
			DestroyWindow(hwnd);
		}
		else
		{
			fprintf(gpFile, "File For Reading Opened Successfully.\n\n");
		}

	
		ghIcon = LoadIcon(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(MYICON));

		break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case 0x53:
		case 0x73:
			EnumWindows(EnumWindowsProc, 0);

			if (gbInstance == FALSE)
			{
				MessageBox(hwnd, TEXT("Notepad not Found"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
				exit(0);
			}
			gbInstance = FALSE;

			EnumChildWindows(gWindowHandle, EnumWindowsProc, 0);

			if (gbInstance == FALSE)
			{
				MessageBox(hwnd, TEXT("Child Window not Found"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
				exit(0);
			}

			hmenu = GetMenu(gWindowHandle);
			
			if(NULL == hmenu)
			{
				MessageBox(hwnd, TEXT("GetMenu Failed"), TEXT("ERROR"), MB_ICONERROR | MB_OK);
				exit(0);
			}
			mii.dwTypeData = szBuffer;
		//	GetMenuItemInfo(hmenu, 2, 2, &mii);
			GetMenuString(hmenu, 2, szBuffer, 20, MF_BYPOSITION);
			
			hSubMenu = GetSubMenu(hmenu, 2);
			SendMessage(gWindowHandle, WM_SETFONT, , (LPARAM)hmenu);
	//		hSubMenu = GetSubMenu(hSubMenu, 0);
	//		GetMenuBarInfo(gWindowHandle, OBJID_MENU, 2, &mbi);

			
		
			SetWindowPos(gWindowHandle, hwnd, 250, 250, 800, 400, SWP_FRAMECHANGED | SWP_SHOWWINDOW);

			SetActiveWindow(gWindowHandle);
			SetForegroundWindow(gWindowHandle);
			SetFocus(gWindowHandle);


			dwIcon = GetClassLong(gWindowHandle, GCL_HICON);
			dwIconSm = GetClassLong(gWindowHandle, GCLP_HICONSM);

			Sleep(3000);
			SendMessage(gWindowHandle, WM_SETICON, ICON_SMALL, (LPARAM)ghIcon);


			while ((wCharacter = fgetwc(pFile)) != WEOF)
			{

				Sleep(300);
				PostMessage(gChildWindowHandle, WM_CHAR, wCharacter, 0);
			}
		
			SetForegroundWindow(hwnd);
			SetFocus(hwnd);

		}

		break;
	case WM_DESTROY:
		
		if (pFile)
		{
			fprintf(gpFile, "\n\nFile Opened For Reading Is Closed Successfully\n");
			fclose(pFile);
			pFile = NULL;
		}
		
		Uninitialize();
		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(hwnd, uiMessage, wParam, lParam));
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	TCHAR szString[MAX] = { NULL };
	
	GetClassName(hwnd, szString, MAX);

	if (lstrcmp(szString, TEXT("Notepad")) == 0)
	{
		gWindowHandle = hwnd;
		gbInstance = TRUE;

		return FALSE;
	}
	else if (lstrcmp(szString, TEXT("Edit")) == 0)
	{
		gChildWindowHandle = hwnd;
		gbInstance = TRUE;

		return INSTANCEFOUND;
	}

	return TRUE;
}

void Uninitialize(void)
{

	SendMessage(gWindowHandle, WM_SETICON, ICON_SMALL, dwIconSm);
	SendMessage(gWindowHandle, WM_SETICON, ICON_BIG, dwIcon);

	if (gpFile)
	{
		fprintf(gpFile ,"\n\n Log File Closed SuccessFully.\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}

