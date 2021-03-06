	//		UP, Down, Left, Right Without Text 

#include <windows.h>
#include <tchar.h>

#define BUFSIZE 65535
#define SHIFTED 0x8000

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(
				HINSTANCE hInstance,
				HINSTANCE hPrevInsatnce,
				LPSTR szCmdLine,
				INT iCmdShow
				)
{
	MSG msg;
	HWND hwnd;
	BOOL bRet;
	WNDCLASSEX WndClass;

	TCHAR szClassName[] = TEXT("Window");

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszClassName = szClassName;
	WndClass.lpszMenuName = NULL;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("RegisterClassEx FAILED"), TEXT("FAILUER"), MB_OK | MB_ICONERROR);
		return -1;
	}

	hwnd = CreateWindow(
				szClassName,
				TEXT("Editor Version : 1"),
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
		MessageBox(NULL, TEXT("CreateWindow FAILED"), TEXT("FAILUER"), MB_OK | MB_ICONERROR);
		return -1;
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while(bRet = GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if(-1 == bRet)
		{
			MessageBox(NULL, TEXT("GetMessage FAILED"), TEXT("FAILUER"), MB_OK | MB_ICONERROR);
			return -1;
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
					UINT iMessage,
					WPARAM wParam,
					LPARAM lParam
					)
{
	HDC hdc;
	TEXTMETRIC tm;
	PAINTSTRUCT ps;

	static int cxChar;
	static int cyChar;
	static int cxClient;
	static int cyClient;

	static int iLines;
	static int iLineLength;

	static int iCaretPosX;
	static int iCaretPosY;
	static int iCharWidth;

	static int cCh;
	static int iCurChar;

	TCHAR ch;
	size_t uiLength;
	TCHAR szBuf[128];

	RECT rc;
	SIZE sz;
	COLORREF crPrevBk;
	COLORREF crPrevText;

	int iCounter1, iCounter2;
	int iVirtKey;
	HRESULT hResult;

	int iCR = 0;
	int iCRIndex = 0;

	static TCHAR *pchInputBuf;

	switch(iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);
		GetTextMetrics(hdc, &tm);
		ReleaseDC(hwnd, hdc);

		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmHeight + tm.tmExternalLeading;

		pchInputBuf = (LPSTR)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, BUFSIZE* sizeof(TCHAR));
		break;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		iLines = cyClient / cyChar;
		iLineLength = cxClient - cxChar;

		break;

	case WM_SETFOCUS:
		CreateCaret(hwnd, NULL, 0, cyChar);
		SetCaretPos(iCaretPosX, iCaretPosY * cyChar);
		ShowCaret(hwnd);
		break;
		
	case WM_KILLFOCUS:
		HideCaret(hwnd);
		DestroyCaret();
		break;
	/*
	case WM_CHAR:
		if(cCh > BUFSIZE - 5)
		{
			pchInputBuf[cCh] = 0x00;
			SendMessage(hwnd, WM_PAINT, 0, 0);
		}

		switch(wParam)
		{
		case 0x0A:
		case VK_ESCAPE:
			MessageBeep((UINT) -1);
			break;
			
		case VK_TAB:
			
			for(iCounter1 = 0; iCounter1 < 4; iCounter1++)
				SendMessage(hwnd, WM_CHAR, VK_SPACE, 0);
			break;

		case VK_RETURN:
			pchInputBuf[cCh++] =VK_RETURN;
			iCaretPosX = 0;
			++iCaretPosY;
			break;

		default:
			ch = (TCHAR)wParam;
			HideCaret(hwnd);

			hdc = GetDC(hwnd);
			GetCharWidth32(hdc, (UINT)wParam, (UINT)wParam, &iCharWidth);
			TextOut(hdc, iCaretPosX, iCaretPosY * cyChar, &ch, 1);
			ReleaseDC(hwnd, hdc);

			pchInputBuf[cCh++] = ch;

			iCaretPosX = iCaretPosX + iCharWidth;

			if((int)iCaretPosX > iLineLength)
			{
				iCaretPosX = 0;
				pchInputBuf[cCh++] = VK_RETURN;
				++iCaretPosY;
			}
			iCurChar = cCh;
			break;
		}
		ShowCaret(hwnd);
		SetCaretPos(iCaretPosX, iCaretPosY * cyChar);

		break;
		*/
	case WM_KEYDOWN:

		switch(wParam)
		{
		case VK_LEFT:

			if(iCaretPosX > 0)
			{
				HideCaret(hwnd);

				ch = pchInputBuf[--iCurChar];
				hdc = GetDC(hwnd);
				GetCharWidth32(hdc, ch, ch, &iCharWidth);
				ReleaseDC(hwnd, hdc);

				iCaretPosX = max(iCaretPosX - iCharWidth, 0);
				ShowCaret(hwnd);
			}

			break;

		case VK_RIGHT:
			HideCaret(hwnd);

			if(iCurChar < cCh)
			{
				ch = pchInputBuf[iCurChar];

				if(ch == VK_RETURN)
				{
					iCaretPosX = 0;
					iCaretPosY++; 
				}
				else
				{
					hdc  = GetDC(hwnd);
					iVirtKey = GetKeyState(VK_SHIFT);

					if(VK_SHIFT & SHIFTED)
					{
						crPrevText = SetTextColor(hdc, RGB(255, 255, 255));
						crPrevBk = SetBkColor(hdc, RGB(0, 0, 0));
						TextOut(hdc, iCaretPosX, iCaretPosY * cyChar, &ch, 1);
				
						SetTextColor(hdc, crPrevText);
						SetBkColor(hdc, crPrevBk);
					}
					GetCharWidth32(hdc, ch, ch, &iCharWidth);
					ReleaseDC(hwnd, hdc);
					iCaretPosX = iCaretPosX + iCharWidth;
				}
					iCurChar++;
			}
			ShowCaret(hwnd);
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, iMessage, wParam, lParam);
}