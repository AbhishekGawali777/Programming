#include <conio.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include "Learning_Win32.h"

#define MAX 100

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

INT WINAPI WinMain(
				HINSTANCE hInstance,
				HINSTANCE hPrevInstance,
				LPSTR iCmdLine,
				INT iCmdShow
				)
{
	MSG msg;
	HWND hwnd;
	BOOL bRet;
	WNDCLASSEX WndClass;
	TCHAR szWindowName[MAX]=TEXT("RamRam");

	WndClass.cbSize=sizeof(WNDCLASSEX);
	WndClass.style=CS_HREDRAW|CS_VREDRAW;
	WndClass.lpfnWndProc=WndProc;
	WndClass.hInstance=hInstance;
	WndClass.cbWndExtra=0;
	WndClass.cbClsExtra=0;
	WndClass.lpszClassName=szWindowName;
	WndClass.lpszMenuName=NULL;
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hCursor=LoadCursor(NULL,IDI_APPLICATION);
	WndClass.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);

	if(!RegisterClassEx(&WndClass))
		//Register Class failed zala tr 0 return krto
		//if true vhava yasathi tya 0 cha ! kela i.e., 1.
	{
		
		MessageBox(NULL,TEXT("RegisterClassEx FAILED"),TEXT("RamRam"),MB_ICONERROR);
		exit(0);
	}

	hwnd=CreateWindow(
					szWindowName,
					TEXT("HELLO"),
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
		MessageBox(NULL,TEXT("CreateWindow FAILED"),TEXT("RamRam"),MB_ICONERROR);
		exit(0);
	}

	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);

	while(0 != (bRet=GetMessage(&msg,NULL,0,0)))
	{
		if(-1 == bRet)
		{
			MessageBox(NULL,TEXT("GetMessage FAILED"),TEXT("RamRam"),MB_ICONERROR);
			exit(0);
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
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
	static RECT rcRect;
	static TEXTMETRIC tm;
	
	int iHeight;
	int iCounter;
	TCHAR *szTemp[]={TEXT("Kay mg"),TEXT("Pahune")};
	TCHAR szTemp1[MAX];
	static int cyChar;
	static int cyClient;
	static int iNoOfRows;

#if LOG
	static FILE * fp;
	static int iCounter1;
#endif


	switch(iMessage)
	{
	case WM_CREATE:
#if LOG 
		fp=fopen("Log.txt","w");
		
		if(NULL == fp)
		{
			MessageBox(NULL,TEXT("FILE Opening FAILED"),TEXT("BYE...!!!"),MB_OK);
			return -1;
		}
		_stprintf_s(szTemp1,MAX,TEXT("In WM_CREATE()\n"));
		_fputts(szTemp1,fp);
#endif
		hdc=GetDC(hwnd);
		GetTextMetrics(hdc,&tm);
		ReleaseDC(hwnd,hdc);

		cyChar=tm.tmHeight + tm.tmExternalLeading;
		break;

	case WM_PAINT:
#if LOG
		_stprintf_s(szTemp1,MAX,TEXT("In WM_PAINT(%d)\n"),iCounter1++);
		_fputts(szTemp1,fp);
#endif
		iHeight = 0;
		iCounter = 0;	
		hdc = BeginPaint(hwnd,&ps);
		while(iHeight < iCounter)
		{
			TextOut(hdc,0,iHeight,szTemp[iCounter],(int)_tcslen(szTemp[iCounter]));
			
			iHeight=iHeight+cyChar;
			iCounter++;
		}
		EndPaint(hwnd,&ps);
		break;

	case WM_LBUTTONDOWN:
#if LOG
		_stprintf_s(szTemp1,MAX,TEXT("In WM_LBUTTONDOWN(%d)\n"),iCounter1);
		_fputts(szTemp1,fp);
#endif
		
		rcRect.bottom=200;
		rcRect.left=100;
		rcRect.right=200;
		rcRect.top=100;

	
		break;

	case WM_SIZE:
		GetClientRect(hwnd,&rcRect);
		// Client Area che co-ordinates deto
		cyClient=HIWORD(lParam);
		break;
			
	case WM_DESTROY:

#if LOG
		fclose(fp);
		fp=NULL;
#endif

//		MessageBox(NULL,TEXT("Closing Window"),TEXT("BYE...!!!"),MB_OK);
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd,iMessage,wParam,lParam);
}