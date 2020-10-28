#include <windows.h>
#include <tchar.h>

#define NUMLINES ((int) (sizeof devcaps / sizeof devcaps[0]))

struct 
{
	int iIndex;
	TCHAR* szLable;
	TCHAR* szDesc;
}

devcaps[] =
{
	HORZSIZE, TEXT("HORZSIZE"), TEXT("Width in Millimeters"),
	VERTSIZE, TEXT("VERTSIZE"), TEXT("Height in Millimeters"),
	HORZRES, TEXT ("HORZRES"), TEXT ("Width in pixels:"),
	VERTRES, TEXT ("VERTRES"), TEXT ("Height in raster lines:"),
	BITSPIXEL, TEXT ("BITSPIXEL"), TEXT ("Color bits per pixel:"),
	PLANES, TEXT ("PLANES"), TEXT ("Number of color planes:"),
	NUMBRUSHES, TEXT ("NUMBRUSHES"), TEXT ("Number of device brushes:"),
	NUMPENS, TEXT ("NUMPENS"), TEXT ("Number of device pens:"),
	NUMMARKERS, TEXT ("NUMMARKERS"), TEXT ("Number of device markers:"),
	NUMFONTS, TEXT ("NUMFONTS"), TEXT ("Number of device fonts:"),
	NUMCOLORS, TEXT ("NUMCOLORS"), TEXT ("Number of device colors:"),
	PDEVICESIZE, TEXT ("PDEVICESIZE"), TEXT ("Size of device structure:"),
	ASPECTX, TEXT ("ASPECTX"), TEXT ("Relative width of pixel:"),
	ASPECTY, TEXT ("ASPECTY"), TEXT ("Relative height of pixel:"),
	ASPECTXY, TEXT ("ASPECTXY"), TEXT ("Relative diagonal of pixel:"),
	LOGPIXELSX, TEXT ("LOGPIXELSX"), TEXT ("Horizontal dots per inch:"),
	LOGPIXELSY, TEXT ("LOGPIXELSY"), TEXT ("Vertical dots per inch:"),
	SIZEPALETTE, TEXT ("SIZEPALETTE"), TEXT ("Number of palette entries:"),
	NUMRESERVED, TEXT ("NUMRESERVED"), TEXT ("Reserved palette entries:"),
	COLORRES, TEXT ("COLORRES"), TEXT ("Actual color resolution:")
};

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR szCmdLine,
				   INT iCmdShow
				   )
{
	MSG msg;
	BOOL bRet;
	HWND hwnd;
	WNDCLASSEX WndClass;

	TCHAR szAppName[]=TEXT("My Window");


	WndClass.cbSize=sizeof(WNDCLASSEX);
	WndClass.style=CS_HREDRAW|CS_VREDRAW;
	WndClass.lpfnWndProc=WndProc;
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hInstance=hInstance;
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hCursor=LoadCursor(NULL,IDI_APPLICATION);
	WndClass.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName=NULL;
	WndClass.lpszClassName=szAppName;
	WndClass.hIconSm=LoadIcon(NULL,IDI_APPLICATION);

	if(!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL,TEXT("RegisterClassEx FAILED"),szAppName,MB_ICONERROR);
		exit(0);
	}
	

	hwnd=CreateWindow(				 
					szAppName,
					TEXT("My First Window"),
					WS_OVERLAPPEDWINDOW,	
					CW_USEDEFAULT,			
					CW_USEDEFAULT,			
					CW_USEDEFAULT,			
					CW_USEDEFAULT,			
					NULL,					
					NULL,					
					hInstance,
					NULL,
					);

	if(NULL == hwnd)
	{
		MessageBox(NULL,TEXT("CreateWindow FAILED"),szAppName,MB_ICONERROR);
		exit(0);
	}

	ShowWindow(hwnd,iCmdShow);	
	UpdateWindow(hwnd);			

	while(bRet=GetMessage(&msg,NULL,0,0)!=0)
	{
		if(bRet == -1)
		{
			MessageBox(NULL,TEXT("GetMessage FAILED"),szAppName,MB_ICONERROR);
			exit(0);
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
						UINT uiMessage,
						WPARAM wParam,
						LPARAM lParam
						 )
{
	int iCounter;
	static int cxChar;
	static int cyChar;
	static int cxCaps;

	TCHAR  szBuffer[10];

	HDC hdc;
	TEXTMETRIC tm;
	PAINTSTRUCT ps;

	switch(uiMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);
		GetTextMetrics(hdc, &tm);

		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmHeight + tm.tmExternalLeading;

		if(tm.tmPitchAndFamily & 1)
			cxCaps = 3 * cxChar / 2;
		else
			cxCaps = cxChar;

		ReleaseDC(hwnd, hdc);

		break;

	case WM_PAINT:

		hdc = BeginPaint(hwnd, &ps);

		//SetBkColor(hdc, RGB(0, 255, 0));
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 0, 0));

		for(iCounter = 0; iCounter < NUMLINES; iCounter++)
		{
			TextOut(hdc, 0, cyChar * iCounter, devcaps[iCounter].szLable, (int)_tcslen(devcaps[iCounter].szLable));

			TextOut(hdc, 14 * cxCaps, cyChar * iCounter, devcaps[iCounter].szDesc, (int)_tcslen(devcaps[iCounter].szDesc));

			SetTextAlign(hdc, TA_RIGHT | TA_TOP);

			TextOut(hdc, 28 * cxCaps + 35 * cxChar, cyChar * iCounter, szBuffer,
					_stprintf(szBuffer, TEXT("%5d"), GetDeviceCaps(hdc, devcaps[iCounter].iIndex)));

			SetTextAlign(hdc, TA_LEFT | TA_TOP);
		}

		EndPaint(hwnd, &ps);
		break;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd,uiMessage,wParam,lParam);
}