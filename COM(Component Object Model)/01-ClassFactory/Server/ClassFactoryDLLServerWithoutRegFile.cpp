
// Header Files

#include"ClassFactoryDLLServerWithRegFile.h"

// Global Variable Declaration

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;
HMODULE ghModule;

class CSumSubtract : ISum, ISubtract
{
	long m_cRef;

public:

	// Constructor
	CSumSubtract();
	
	// Destructor
	~CSumSubtract();

	// IUnknown Method Declarations

	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// ISum's Method Declarations

	HRESULT __stdcall SumOfTwoIntergers(int, int, int*);

	// Isubtract's Method Declarations

	HRESULT __stdcall SubtractionOfTwoIntergers(int, int, int*);
};


class CSumSubtractClassFactory : public IClassFactory
{

	long m_cRef;

public:

	// Constructor
	CSumSubtractClassFactory();
	
	// Destructor
	~CSumSubtractClassFactory();

	// IUnknown Methods Declarations

	HRESULT QueryInterface(REFIID, void**);
	ULONG AddRef(void);
	ULONG Release(void);

	// IClassFactory Method Declarations

	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

// DllMain()

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		ghModule = hInstance;
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		break;
	}

	return(TRUE);
}

CSumSubtract::CSumSubtract()
{
	// Code

	m_cRef = 1;

	InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubtract::~CSumSubtract()
{
	// Code

	InterlockedDecrement(&glNumberOfActiveComponents);
}


// QueryInterface()

HRESULT CSumSubtract::QueryInterface(REFIID riid, void** ppv)
{
	// Code

	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}


// AddRef()

ULONG CSumSubtract::AddRef(void)
{
	// Code

	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

// Release()

ULONG CSumSubtract::Release(void)
{
	// Code
	
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}

	return(m_cRef);
}

// SumOfTwoIntegers()

HRESULT CSumSubtract::SumOfTwoIntergers(int iNum1, int iNum2, int* iResult)
{
	// Code
	
	*iResult = iNum1 + iNum2;
	return(S_OK);
}

// SubtractionOfTwoIntegers()

HRESULT CSumSubtract::SubtractionOfTwoIntergers(int iNum1, int iNum2, int* iResult)
{
	// Code+

	*iResult = iNum1 - iNum2;
	return(S_OK);
}


// CSumSubtractClassFactory()

CSumSubtractClassFactory::CSumSubtractClassFactory()
{
	// Code

	m_cRef = 1;
}

// ~CSumSubtractClassFactory()
CSumSubtractClassFactory::~CSumSubtractClassFactory()
{
	// Code

}

// QueryInterface()

HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	// Code

	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

// AddRef()

ULONG CSumSubtractClassFactory::AddRef(void)
{
	// Code

	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

// Release()

ULONG CSumSubtractClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}

	return(m_cRef);
}

// CreateInstance()

HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	// Local Variable Declarations

	CSumSubtract* pCSumSubtract = NULL;
	HRESULT hr;

	// Code

	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	pCSumSubtract = new CSumSubtract;

	if (NULL == pCSumSubtract)
		return(E_OUTOFMEMORY);

	hr = pCSumSubtract->QueryInterface(riid, ppv);

	pCSumSubtract->Release();
	return(hr);
}

// LockServer()

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	// Code

	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);

	return(S_OK);
}

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	// Local Variable Declaration

	HRESULT hr;
	CSumSubtractClassFactory* pCSumSubtractClassFactory = NULL;

	// Code

	if (rclsid != CLSID_CSumSubract)
		return(CLASS_E_CLASSNOTAVAILABLE);

	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	
	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();

	return(hr);
}

// DllCanUnloadNow()

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	// Code

	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);		// Status OK
	else
		return(S_FALSE);	// Status FALSE
}

// DllRegisterServer()

STDAPI DllRegisterServer()
{
	// Local Variable Declarations

	HKEY hCLSIDKey = NULL, hInProcSvrkey = NULL;
	LONG lRet;
	TCHAR szModulePath[MAX_PATH];
	TCHAR szClassDescription[] = TEXT("Simple COM Class");
	TCHAR szThreadingModel[] = TEXT("Apartment");

	// Code

	__try
	{
		lRet = RegCreateKeyEx(HKEY_CLASSES_ROOT, TEXT("CLSID\\{AB234DB4-9F1A-4007-9DD1-859B2EA335F1}"), 0, NULL,
			REG_OPTION_NON_VOLATILE, KEY_SET_VALUE | KEY_CREATE_SUB_KEY, NULL, &hCLSIDKey, NULL);

		if (ERROR_SUCCESS != lRet)
			return(HRESULT_FROM_WIN32(lRet));

		lRet = RegSetValueEx(hCLSIDKey, NULL, 0, REG_SZ, (const BYTE*)szClassDescription, sizeof(szClassDescription));

		if (ERROR_SUCCESS != lRet)
			return(HRESULT_FROM_WIN32(lRet));

		lRet = RegCreateKeyEx(hCLSIDKey, TEXT("InProcServer32"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE,
			NULL, &hInProcSvrkey, NULL);

		if (ERROR_SUCCESS != lRet)
			return(HRESULT_FROM_WIN32(lRet));


		GetModuleFileName(ghModule, szModulePath, MAX_PATH);

		lRet = RegSetValueEx(hInProcSvrkey, NULL, 0, REG_SZ, (const BYTE*)szModulePath, sizeof(TCHAR) * (lstrlen(szModulePath) + 1));

		if (ERROR_SUCCESS != lRet)
			return(HRESULT_FROM_WIN32(lRet));

		lRet = RegSetValueEx(hInProcSvrkey, TEXT("ThreadingModel"), 0, REG_SZ, (const BYTE*)szThreadingModel, sizeof(szThreadingModel));

		if (ERROR_SUCCESS != lRet)
			return(HRESULT_FROM_WIN32(lRet));
	}
	__finally
	{
		if (NULL != hCLSIDKey)
			RegCloseKey(hCLSIDKey);

		if (NULL != hInProcSvrkey)
			RegCloseKey(hInProcSvrkey);
	}

	return(S_OK);
}

STDAPI DllUnregisterServer()
{
	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{AB234DB4-9F1A-4007-9DD1-859B2EA335F1}\\InProcServer32"));
	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{AB234DB4-9F1A-4007-9DD1-859B2EA335F1}"));

	return(S_OK);  
}