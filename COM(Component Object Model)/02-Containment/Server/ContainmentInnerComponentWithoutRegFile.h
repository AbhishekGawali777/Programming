#ifndef __CONTAINMENTINNERCOMPONENTWIHTOUTREGFILE_H__
#define __CONTAINMENTINNERCOMPONENTWIHTOUTREGFILE_H__

#include<Windows.h>
#include<stdio.h>
#include<tchar.h>
#include<Unknwnbase.h>

// Interface

class IMultiplication : public IUnknown
{
public:

	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};

class IDivision : public IUnknown
{
public:

	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};

// CLSID_CMultiplicationDivision =  {803939B1-CEDD-420C-9697-9E999E5D5345}

const CLSID CLSID_CMultiplicationDivision = { 0x803939b1, 0xcedd, 0x420c, 0x96, 0x97, 0x9e, 0x99, 0x9e, 0x5d, 0x53, 0x45 };

// IID_IMultiplication = {F9A8A95D-E129-4E89-BBDC-4E9581587618}

const IID IID_IMultiplication = { 0xf9a8a95d, 0xe129, 0x4e89, 0xbb, 0xdc, 0x4e, 0x95, 0x81, 0x58, 0x76, 0x18 };

// IID_IDivision = {7D69AF72-9B22-44B3-B1C0-7364DE617DAF}
 
const IID IID_IDivision = { 0x7d69af72, 0x9b22, 0x44b3, 0xb1, 0xc0, 0x73, 0x64, 0xde, 0x61, 0x7d, 0xaf };

#endif // __CONTAINMENTINNERCOMPONENTWIHTOUTREGFILE_H__
