#include <windows.h>
#include <mmsystem.h>



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
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName=NULL;
	WndClass.lpszClassName=szAppName;
	WndClass.hIconSm=LoadIcon(NULL,IDI_APPLICATION);

	if(!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL,TEXT("RegisterClassEx FAILED"),szAppName,MB_ICONERROR);
		exit(0);
	}
	

	hwnd=CreateWindow(				//Internally Calls WM_CREATE 
					szAppName,
					TEXT("My First Window"),
					WS_OVERLAPPEDWINDOW,	//Window Style
					CW_USEDEFAULT,			//starting 'x' co-ordinate of window
					CW_USEDEFAULT,			//starting 'y' co-ordinate of window
					CW_USEDEFAULT,			//width of window (x co-ordniate)
					CW_USEDEFAULT,			//height of window(y co-ordinate)
					NULL,					//Parent Window Handel
					NULL,					//Window Menu
					hInstance,
					NULL,
					//
					// Extra information About Window Creation(if You Wish)
					//
					);

	if(NULL == hwnd)
	{
		MessageBox(NULL,TEXT("CreateWindow FAILED"),szAppName,MB_ICONERROR);
		exit(0);
	}

	ShowWindow(hwnd,iCmdShow);	// Internally Calls WS_SHOW & WS_WM_SIZE
	UpdateWindow(hwnd);			// Internally Calls WS_PAINT

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
	HDC hdc;
	RECT rcRect;
	PAINTSTRUCT ps;

	switch(uiMessage)
	{
	/*case WM_CREATE:
		PlaySound(TEXT("HelloWin32.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return 0;*/

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		
		GetClientRect(hwnd, &rcRect);

		DrawText(hdc, TEXT("Hello Windows 10.!!!"), -1, &rcRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		EndPaint(hwnd, &ps);

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd,uiMessage,wParam,lParam);
}