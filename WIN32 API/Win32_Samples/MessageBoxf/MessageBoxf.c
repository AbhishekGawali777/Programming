#include<windows.h>
#include<stdio.h>
#include<tchar.h>
#include<stdarg.h>

#define MAX 50

int MessageBoxF(HWND,UINT,TCHAR*,TCHAR*,...);

INT WINAPI WinMain(
											HINSTANCE	hInstance,
											HINSTANCE hPrevInstance,
											PSTR iCmdLine,
											int iCmdShow
											)
{
	//TCHAR szStr[MAX];
	//_stprintf(szStr,"My name is %s and in %d","xyz",10);

	MessageBoxF(NULL,MB_ABORTRETRYIGNORE,TEXT("My window"),TEXT("My name is %s , I'm in %d th\n"),
			TEXT("Abhi"),10);

	return 0;
}

int MessageBoxF(HWND hWnd,UINT uType,TCHAR * szCaption,TCHAR * szFormat,...)
{
	TCHAR szBuffer[MAX];

	va_list pArgList;

	va_start(pArgList,szFormat);

	_vsntprintf(szBuffer,sizeof(szBuffer)/sizeof(TCHAR),szFormat,pArgList);

	va_end(pArgList);

	return MessageBox(hWnd,szBuffer,szCaption,uType);
}
//vsprintf
//sprintf
//_vsnprinf