#ifndef _CONTAINMENT_H__
#define _CONTAINMENT_H__
// Header Files

#include<Windows.h>
#include<stdio.h>
#include<tchar.h>
#include<Unknwnbase.h>

// Interface Declarations

class ISum : public IUnknown
{
public:

	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubtract : public IUnknown
{
public:

	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

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

// CLSID_CSumSubtract = {6DBE1E08-EAFA-4497-A724-8CDCE0BF5B6E}

static const CLSID CLSID_CSumSubtract = { 0x6dbe1e08, 0xeafa, 0x4497, 0xa7, 0x24, 0x8c, 0xdc, 0xe0, 0xbf, 0x5b, 0x6e };

// IID_ISum = {0094B8D6-D281-47A3-8701-34679A409598}

static const IID IID_ISum = { 0x94b8d6, 0xd281, 0x47a3, 0x87, 0x1, 0x34, 0x67, 0x9a, 0x40, 0x95, 0x98 };

// IID_ISubtract = {49FB9156-6B44-414F-9D65-6F0B86D43175}

static const IID IID_ISubtract = { 0x49fb9156, 0x6b44, 0x414f, 0x9d, 0x65, 0x6f, 0xb, 0x86, 0xd4, 0x31, 0x75 };

// IID_IMultiplication = {F9A8A95D-E129-4E89-BBDC-4E9581587618}

const IID IID_IMultiplication = { 0xf9a8a95d, 0xe129, 0x4e89, 0xbb, 0xdc, 0x4e, 0x95, 0x81, 0x58, 0x76, 0x18 };

// IID_IDivision = {7D69AF72-9B22-44B3-B1C0-7364DE617DAF}
 
const IID IID_IDivision = { 0x7d69af72, 0x9b22, 0x44b3, 0xb1, 0xc0, 0x73, 0x64, 0xde, 0x61, 0x7d, 0xaf };

#endif	// _CONTAINMENT_H__
