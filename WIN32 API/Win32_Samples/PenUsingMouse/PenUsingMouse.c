#include <windows.h>
#include <windowsx.h>

#define MAX 1000

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
	PAINTSTRUCT ps;
	static POINT apt[MAX];

	static int iCount;

	switch(uiMessage)
	{
	case WM_PAINT :
		hdc = BeginPaint(hwnd, &ps);

		Polyline(hdc, apt, iCount);

		EndPaint(hwnd, &ps);
		break;

	case WM_MOUSEMOVE:

		if(wParam & MK_LBUTTON && iCount < 1000)
		{
			if(GET_X_LPARAM(lParam) >= 0 && GET_Y_LPARAM(lParam) >= 0)
			{
				SetCapture(hwnd);
				
				apt[iCount].x = LOWORD(lParam);
				apt[iCount].y = HIWORD(lParam);
				iCount++;
				
				hdc = GetDC(hwnd);
				SetPixel(hdc, LOWORD(lParam), HIWORD(lParam), 0);
				ReleaseDC(hwnd, hdc);
			}
		}

		break;
	case WM_LBUTTONDOWN:
		iCount = 0;
		InvalidateRect(hwnd, NULL, TRUE);
		
	case WM_RBUTTONDOWN:
		/*to do*/
		break;

	case WM_LBUTTONUP:
		ReleaseCapture();
		InvalidateRect(hwnd, NULL, FALSE);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd,uiMessage,wParam,lParam);
}

/*

LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int iPts;
	static POINT apt[3000];

	switch(iMsg)
	{
		case WM_LBUTTONDOWN:
			iPts = 0;
			InvalidateRect(hwnd,NULL,TRUE);

			break;
		case WM_MOUSEMOVE:
			hdc = GetDC(hwnd);

			if(wParam & MK_LBUTTON && iPts < 3000)
			{
				apt[iPts].x = LOWORD(lParam);
				apt[iPts].y = HIWORD(lParam);

				SetPixel (hdc, apt[iPts].x, apt[iPts].y, RGB(255, 0, 0));
				iPts++;

			}

			ReleaseDC(hwnd,hdc);
			break;

		case WM_LBUTTONUP:
			InvalidateRect(hwnd,NULL,FALSE);
			break;
		case WM_PAINT :
			hdc = BeginPaint(hwnd,&ps);

			Polyline(hdc,apt,iPts);

			EndPaint(hwnd,&ps);
			break;
		case WM_DESTROY :
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd,iMsg,wParam,lParam);
}
*/