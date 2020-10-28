#include <windows.h>
#include "MyMath.h"

// Entry Point Function

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
	// Code

	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		break;

	default:
		break;
	}

	return(TRUE);
}

// Exported Function Defination

__declspec(dllexport) int MakeSquare(int iNumber)
{
	// Code

	return(iNumber * iNumber);
}
