#include "EDRLIB.h"

int WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, PVOID pvReserved)
{
	return TRUE;
}

EXPORT BOOL CALLBACK EdrCenterTextA(HDC hdc, PRECT prect, PCSTR pString)
{
	SIZE size;
	int iLength;

	iLength = lstrlenA (pString);

	GetTextExtentPoint32A(hdc , pString, iLength, &size);

	return TextOutA(hdc, (prect -> right - prect -> left - size.cx) / 2,(prect->bottom - prect->top - size.cy) / 2,
					pString, iLength);

}

EXPORT BOOL CALLBACK EdrCenterTextW(HDC hdc, PRECT prect, PCWSTR pString)
{
	SIZE size;
	int iLength;

	iLength = lstrlenW(pString);

	GetTextExtentPoint32W(hdc, pString, iLength, &size);

	return TextOutW(hdc, (prect->right - prect->left - size.cx) / 2,(prect->bottom - prect->top - size.cy) / 2,
					pString, iLength);

}
