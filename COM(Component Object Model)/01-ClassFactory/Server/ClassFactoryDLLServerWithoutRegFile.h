#ifndef __CLASSFACTORYDLLSERVERWITHREGFILE_H__
#define __CLASSFACTORYDLLSERVERWITHREGFILE_H__

#include<Windows.h>
#include<Unknwnbase.h>

class ISum : public IUnknown
{
public:

	virtual HRESULT __stdcall SumOfTwoIntergers(int, int, int*) = 0;
};

class ISubtract : public IUnknown
{
public:

	virtual HRESULT __stdcall SubtractionOfTwoIntergers(int, int, int*) = 0;
};

// CLSID_CSumSubtract {AB234DB4-9F1A-4007-9DD1-859B2EA335F1}

static const CLSID CLSID_CSumSubract = { 0xab234db4, 0x9f1a, 0x4007, 0x9d, 0xd1, 0x85, 0x9b, 0x2e, 0xa3, 0x35, 0xf1 };

// IID_ISum {B5F7C25A-EA14-4E13-8FAE-D548327DEEBB}

static const IID IID_ISum = { 0xb5f7c25a, 0xea14, 0x4e13, 0x8f, 0xae, 0xd5, 0x48, 0x32, 0x7d, 0xee, 0xbb };

// IID_ISubtract {540703A2-3A78-4A99-93ED-76586267FDCC}

static const IID IID_ISubtract = { 0x540703a2, 0x3a78, 0x4a99, 0x93, 0xed, 0x76, 0x58, 0x62, 0x67, 0xfd, 0xcc};

#endif		//	__CLASSFACTORYDLLSERVERWITHREGFILE_H__
