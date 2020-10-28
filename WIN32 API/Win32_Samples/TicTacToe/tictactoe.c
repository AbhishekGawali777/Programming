#include<windows.h>
#define DIVISIONS 3

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(
		HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR szCmdLine,
		int iCmdShow)
{
	MSG msg;
	BOOL bRet;
	HWND hwnd;
	WNDCLASSEX WndClass;

	TCHAR szAppName[]=TEXT("MyWindow");

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_VREDRAW | CS_HREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL,IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = szAppName;
	WndClass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);

	if(!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL,TEXT("RegisterClassEx FAILED"),szAppName,MB_ICONERROR);
		exit(0);
	}

	hwnd=CreateWindow(
			szAppName,	
			TEXT("TicTacToeMouseInterface"),
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
		MessageBox(hwnd,TEXT("CreateWindow FAILED"),szAppName,MB_ICONERROR);
		exit(0);
	}

	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);


	while(bRet = GetMessage(&msg,NULL,0,0) != 0)
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
	int x,y;
	int i,j;
	BOOL bWin;
	PAINTSTRUCT ps;

	static int cxBlock,cyBlock;
	static int iState[DIVISIONS][DIVISIONS];

	static BOOL bLeftClick = FALSE;
	static BOOL bRightClick = TRUE;

	POINT point;

	switch(uiMessage)
	{
		case WM_SIZE :
			cxBlock = LOWORD(lParam) / DIVISIONS;
			cyBlock = HIWORD (lParam) / DIVISIONS;
			break;

		case WM_LBUTTONDOWN:
			x = LOWORD (lParam) / cxBlock;
			y = HIWORD (lParam) / cyBlock;

			if(x < DIVISIONS && y < DIVISIONS && bRightClick == TRUE)
			{
				if(iState[x][y] == 1 || iState[x][y] == 2)
					break;

				bLeftClick = TRUE;
				bRightClick = FALSE;
				iState[x][y] = 1;

				hdc = GetDC(hwnd);
				MoveToEx (hdc, x * cxBlock, y * cyBlock, NULL);
						LineTo (hdc, (x+1) * cxBlock, (y+1) * cyBlock);
						MoveToEx(hdc, x * cxBlock, (y+1) * cyBlock, NULL);
						LineTo (hdc, (x+1) * cxBlock, y * cyBlock);
				ReleaseDC(hwnd, hdc);

				bWin = FALSE;

				// Column check

				if(bWin == FALSE)
				{
					for(i = 0; i < DIVISIONS; i++)
					{
						if(i == x)
							continue;
						if(iState[i][y] == 0 || iState[i][y] == 2)
							break;
					}
					if(i == DIVISIONS)
					{
						bWin = TRUE;
					}
				}

				// Row check

				if(bWin == FALSE)
				{
					for(i = 0; i < DIVISIONS; i++)
					{
						if(i == y)
							continue;
						if(iState[x][i] == 0 || iState[x][i] == 2)
							break;
					}
					if(i == DIVISIONS)
					{
						bWin = TRUE;
					}
				}

				// Forward diagonal check

				if(bWin == FALSE)
				{
					if(x == y)
					{
						for(i = 0; i < DIVISIONS; i++)
						{
							if(i == x)
								continue;
							if(iState[i][i] == 0 || iState[i][i] == 2)
								break;
						}
						if(i == DIVISIONS)
						{
							bWin = TRUE;
						}
					}
				}

				//Backward diagonal check

				if(bWin == FALSE)
				{
					if(x == 0 && y == 2 || x == 2 && y == 0 || x == 1 && y == 1)
					{
						for(i = 0, j = DIVISIONS - 1; i < DIVISIONS; i++,j--)
						{
							if(i == x && j == y)
								continue;
							if(iState[i][j] == 0 || iState[i][j] == 2)
								break;
						}
						if(i == DIVISIONS)
						{
							bWin = TRUE;
						}
					}
				}
				if(bWin == TRUE)
				{
					MessageBox (NULL, TEXT("Winner"), TEXT("Congratulations"), 0);
					PostQuitMessage(0);
				}
			}
			else
				MessageBeep(0);
			break;

		case WM_RBUTTONDOWN :

			x = LOWORD (lParam) / cxBlock;
			y = HIWORD (lParam) / cyBlock;

			if(x < DIVISIONS && y < DIVISIONS && bLeftClick == TRUE)
			{

				if(iState[x][y] == 1 || iState[x][y] == 2)
					break;

				bRightClick = TRUE;
				bLeftClick = FALSE;
				iState[x][y] = 2;

				hdc = GetDC(hwnd);
				Ellipse (hdc , x * cxBlock, y * cyBlock,
							(x+1) * cxBlock, (y+1) * cyBlock);
				ReleaseDC(hwnd, hdc);

				bWin = FALSE;

				// Column check

				if(bWin == FALSE)
				{
					for(i = 0; i < DIVISIONS; i++)
					{
						if(i == x)
							continue;
						if(iState[i][y] == 0 || iState[i][y] == 1)
							break;
					}
					if(i == DIVISIONS)
					{
						bWin = TRUE;
					}
				}

				// Row check

				if(bWin ==  FALSE)
				{
					for(i = 0; i < DIVISIONS; i++)
					{
						if(i == y)
							continue;
						if(iState[x][i] == 0 || iState[x][i] == 1)
							break;
					}
					if(bWin == DIVISIONS)
					{
						bWin = TRUE;
					}
				}

				// Forward diagonal check

				if(bWin == FALSE)
				{
					if(x == y)
					{
						for(i = 0; i < DIVISIONS; i++)
						{
							if(i == x)
								continue;
							if(iState[i][i] == 0 || iState[i][i] == 1)
								break;
						}
						if(i == DIVISIONS)
						{
							bWin = TRUE;
						}
					}
				}

				// Backward diagonal check

				if(bWin == FALSE)
				{
					if(x == 0 && y == DIVISIONS - 1 ||
						x == DIVISIONS -1 && y ==  0 ||
						x == 1 && y == 1)
					{
						for(i = 0, j = DIVISIONS - 1; i < DIVISIONS; i++,j--)
						{
							if(i == x && j == y)
								continue;
							if(iState[i][j] == 0 || iState[i][j] == 1)
								break;
						}
						if(i == DIVISIONS)
						{
							bWin = TRUE;
						}
					}
				}

				if(bWin == TRUE)
				{
					MessageBox (NULL, TEXT("Winner"), TEXT("Congratulations"), 0);
					PostQuitMessage(0);
				}
			}
			else
				MessageBeep(0);
			break;

		case WM_PAINT :
			hdc = BeginPaint (hwnd , &ps);

			for(x = 0; x < DIVISIONS; x++)
				for(y = 0; y < DIVISIONS; y++)
				{
					Rectangle (hdc , x * cxBlock, y * cyBlock,
						(x+1) * cxBlock, (y+1) * cyBlock);
					if(iState[x][y] == 1)
					{
						MoveToEx (hdc, x * cxBlock, y * cyBlock, NULL);
						LineTo (hdc, (x+1) * cxBlock, (y+1) * cyBlock);

						MoveToEx (hdc, x * cxBlock, (y+1) * cyBlock, NULL);
						LineTo (hdc , (x+1) * cxBlock, y * cyBlock);
					}
					else if(iState[x][y] == 2)
					{
						Ellipse (hdc, x * cxBlock, y * cyBlock,
							(x+1) * cxBlock, (y+1) * cyBlock);
					}
				}

			EndPaint (hwnd, &ps);
			break;

		case WM_DESTROY :
				PostQuitMessage(0);
				return 0;
	}
	return DefWindowProc(hwnd,uiMessage,wParam,lParam);
}
