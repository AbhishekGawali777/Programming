#include <windows.h>

#ifdef __cpluscplus
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT __declspec(dllexport)
#endif

EXPORT BOOL CALLBACK EdrCenterTextA(HDC, PRECT, PCSTR);
EXPORT BOOL CALLBACK EdrCenterTextW(HDC, PRECT, PCWSTR);

#ifdef UNICODE
#define EdrCenterText EdrCenterTextW
#else
#define EdrCenterText EdrCenterTextA
#endif