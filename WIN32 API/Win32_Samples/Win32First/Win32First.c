#include<windows.h>

int WINAPI WinMain(
			HINSTANCE hInstance,
			HINSTANCE hPreInstance,
			PSTR pszCmdLine,
			int iCmdShow
					)
{
	MessageBox(NULL,L"My Win32",TEXT("MY WINDOW"),MB_ABORTRETRYIGNORE|MB_DEFBUTTON1|MB_ICONERROR);
	return 0;
}