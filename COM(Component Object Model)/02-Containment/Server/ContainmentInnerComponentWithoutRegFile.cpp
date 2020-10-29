// Header Files

#include"ContainmentInnerComponentWithoutRegFile.h"

// Global Variables

HMODULE hModule;
long glNumberOfActiveComponents;
long glNumberOfServerLocks;

class CMultiplicationDivision : public IMultiplication, IDivision
{
	long m_cRef;

public:

	// Constructor

	CMultiplicationDivision();

	// Destructor

	~CMultiplicationDivision();

	// IUnknown Method Declarations

	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IMultiplication Methods Declaration

	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);

	// IDivision Methods Declaration

	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
};

class CMultiplicationDivisionClassFactory : public IClassFactory
{
	long m_cRef;

public:

	// Constructor

	CMultiplicationDivisionClassFactory();

	// Destructor

	~CMultiplicationDivisionClassFactory();

	// IUnknown Method Declarations

	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory Method Declarations

	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

// DllMain()

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Code

	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		hModule = hInstance;
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

CMultiplicationDivision::CMultiplicationDivision()
{
	// Code

	m_cRef = 1;

	InterlockedIncrement(&glNumberOfActiveComponents);
}

CMultiplicationDivision::~CMultiplicationDivision()
{
	// Code

	InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT __stdcall CMultiplicationDivision::QueryInterface(REFIID riid, void** ppv)
{
	// Code

	if (riid == IID_IUnknown)
		*ppv = static_cast<IMultiplication*>(this);
	else if(riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication*>(this);
	else if(riid == IID_IDivision)
		*ppv = static_cast<IDivision*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG __stdcall CMultiplicationDivision::AddRef(void)
{
	// Code

	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG __stdcall CMultiplicationDivision::Release(void)
{
	// Code

	InterlockedDecrement(&m_cRef);

	if (0 == m_cRef)
	{
		delete(this);
		return(0);
	}

	return(m_cRef);
}

HRESULT __stdcall CMultiplicationDivision::MultiplicationOfTwoIntegers(int iNum1, int iNum2, int* iResult)
{
	// Code

	*iResult = iNum1 * iNum2;
	
	return(S_OK);
}

HRESULT __stdcall CMultiplicationDivision::DivisionOfTwoIntegers(int iNum1, int iNum2, int* iResult)
{
	// Code

	*iResult = iNum1 / iNum2;

	return(S_OK);
}

// CMultiplicationDivisionClassFactory

CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory()
{
	// Code

	m_cRef = 1;
}

CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory()
{
	// Code
}

HRESULT __stdcall CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void** ppv)
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

ULONG __stdcall CMultiplicationDivisionClassFactory::AddRef(void)
{
	// Code

	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG __stdcall CMultiplicationDivisionClassFactory::Release(void)
{
	// Code

	InterlockedDecrement(&m_cRef);

	if (0 == m_cRef)
	{
		delete(this);
		return(0);
	}

	return(m_cRef);
}

HRESULT __stdcall CMultiplicationDivisionClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	// Local Variable Declarations

	HRESULT hr;
	CMultiplicationDivision* pIMultiplicationDivision = NULL;

	// Code

	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	pIMultiplicationDivision = new CMultiplicationDivision;
	hr = pIMultiplicationDivision->QueryInterface(riid, ppv);

	pIMultiplicationDivision->Release();
	
	return(hr);
}

HRESULT __stdcall CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
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
	// Local Variable Declarations

	HRESULT hr;
	CMultiplicationDivisionClassFactory* pIMultiplicationDivisionClassFactory = NULL;

	// Code

	if (rclsid != CLSID_CMultiplicationDivision)
		return(CLASS_E_CLASSNOTAVAILABLE);

	pIMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;

	if (NULL == pIMultiplicationDivisionClassFactory)
		return(E_OUTOFMEMORY);

	hr = pIMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);
	pIMultiplicationDivisionClassFactory->Release();

	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	// code

	if ((0 == glNumberOfActiveComponents) && (0 == glNumberOfServerLocks))
		return(S_OK);
	else
		return(S_FALSE);
}

STDAPI DllRegisterServer()
{
	// Local Variable Declarations

	LONG lRet;
	HKEY hCLSIDKey = NULL;
	HKEY hInProcSvrKey = NULL;
	TCHAR szModulePath[MAX_PATH];
	TCHAR szClassDescription[] = TEXT("IMultiplicationDivision (Inner) Class");
	TCHAR szThreadingModel[] = TEXT("Apartment");

	// Code
	__try
	{
		lRet = RegCreateKeyEx(HKEY_CLASSES_ROOT, TEXT("CLSID\\{803939B1-CEDD-420C-9697-9E999E5D5345}"), 0, NULL,
			REG_OPTION_NON_VOLATILE, KEY_SET_VALUE | KEY_CREATE_SUB_KEY, NULL, &hCLSIDKey, NULL);

		if (ERROR_SUCCESS != lRet)
			return(HRESULT_FROM_WIN32(lRet));

		lRet = RegSetValueEx(hCLSIDKey, NULL, 0, REG_SZ, (const BYTE*)szClassDescription, sizeof(szClassDescription));

		if (ERROR_SUCCESS != lRet)
			return(HRESULT_FROM_WIN32(lRet));

		lRet = RegCreateKeyEx(hCLSIDKey, TEXT("InProcServer32"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL,
			&hInProcSvrKey, NULL);

		if (ERROR_SUCCESS != lRet)
			return(HRESULT_FROM_WIN32(lRet));

		GetModuleFileName(hModule, szModulePath, MAX_PATH);

		lRet = RegSetValueEx(hInProcSvrKey, NULL, 0, REG_SZ, (const BYTE*)szModulePath, sizeof(TCHAR) * (lstrlen(szModulePath)));

		if (ERROR_SUCCESS != lRet)
			return(HRESULT_FROM_WIN32(lRet));

		lRet = RegSetValueEx(hInProcSvrKey, TEXT("ThreadingModel"), 0, REG_SZ, (const BYTE*)szThreadingModel, sizeof(szThreadingModel));

		if (ERROR_SUCCESS != lRet)
			return(HRESULT_FROM_WIN32(lRet));
	}
	__finally
	{
		if (NULL != hCLSIDKey)
			RegCloseKey(hCLSIDKey);

		if (NULL != hInProcSvrKey)
			RegCloseKey(hInProcSvrKey);
	}

	return(S_OK);
}

STDAPI DllUnregisterServer()
{
	// Code

	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{803939B1-CEDD-420C-9697-9E999E5D5345}\\InProcServer32"));
	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{803939B1-CEDD-420C-9697-9E999E5D5345}"));

	return(S_OK);
}
