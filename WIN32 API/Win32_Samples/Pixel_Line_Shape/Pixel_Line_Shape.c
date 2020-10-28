#include<windows.h>

//#define PAINTSIZE(X) sizeof(X)/sizeof(X)

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
	int iCounter;
	static int cxClient;
	static int cyClient;

	HDC hdc;
	PAINTSTRUCT ps;
	POINT apt[]={100,100,200,100,200,200,100,200,300,300,200,200,300,200,300,200,200,300,200,200};
	DWORD asz[2]={5, 5};

	switch(uiMessage)
	{
	case WM_PAINT:

		hdc = BeginPaint(hwnd, &ps);

	//	SetPixel(hdc, 100, 200, RGB(255, 0, 0));

	/*	for(iCounter = 0; iCounter < 200; iCounter++)
		{
			SetPixel(hdc, iCounter, 100,RGB(255, 0, 0));
		}*/

	/*	MoveToEx(hdc, 0, 100, NULL);
		LineTo(hdc, 200, 100);		*/

	/*	MoveToEx(hdc, 100, 100, NULL);
		LineTo(hdc, 200, 100);
		LineTo(hdc, 200, 200);
		LineTo(hdc, 100, 200);
		LineTo(hdc, 100, 100);
	*/
	
	//	Polyline(hdc, apt, 5);
		
		MoveToEx(hdc, 100, 100, NULL);
		PolylineTo(hdc, apt, 1);

	//	PolyPolyline(hdc, apt, asz, 2);

		EndPaint(hwnd, &ps);
		break;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd,uiMessage,wParam,lParam);
}