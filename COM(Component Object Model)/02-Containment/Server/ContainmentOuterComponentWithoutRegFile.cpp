
// Header Files

#include"ContainmentInnerComponentWithoutRegFile.h"
#include"ContainmentOuterComponentWithoutRegFile.h"

// Global Variable Declarations

HMODULE hModule = NULL;

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

// Co-Class Declaration

class CSumSubtract : public ISum, ISubtract, IMultiplication, IDivision
{
	long m_cRef;
	IMultiplication* m_pIMultiplication;
	IDivision* m_pIDivision;

public:

	// Constructor

	CSumSubtract();

	// Destructor

	~CSumSubtract();

	// IUnknown Method Declarations

	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// ISum Interface Method Declarations

	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

	// ISubtract Interface Method Declartions

	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

	// IMultiplication Interface Method Declarations

	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);

	// IDivision Interface Method Declarations

	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);

	// Method for Initializing Inner Component

	HRESULT __stdcall InitializeInnerComponent(void);
};


// IClassFactory Interface Implemented Class

class CSumSubtractClassFactory :public IClassFactory
{
	long m_cRef;

public:

	// Constructor

	CSumSubtractClassFactory();

	// Destructor

	~CSumSubtractClassFactory();

	// IUnknown Interface Methods Declarations

	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory Method Declarations

	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

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

// Co-Class Methods Implementation

CSumSubtract::CSumSubtract()
{
	// Code

	m_cRef = 1;
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;

	InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubtract::~CSumSubtract()
{
	// Code

	InterlockedDecrement(&glNumberOfActiveComponents);	

	if (m_pIMultiplication)
	{
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
	}

	if (m_pIDivision)
	{
		m_pIDivision->Release();
		m_pIDivision = NULL;
	}
}

HRESULT __stdcall CSumSubtract::QueryInterface(REFIID riid, void** ppv)
{
	// Code

	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract*>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication*>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG __stdcall CSumSubtract::AddRef()
{
	// Code

	InterlockedIncrement(&m_cRef);

	return(m_cRef);
}

ULONG __stdcall CSumSubtract::Release()
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

HRESULT __stdcall CSumSubtract::SumOfTwoIntegers(int iNum1, int iNum2, int* iResult)
{
	// Code

	*iResult = iNum1 + iNum2;
	return(S_OK);
}

HRESULT __stdcall CSumSubtract::SubtractionOfTwoIntegers(int iNum1, int iNum2, int* iResult)
{
	// Code
	
	*iResult = iNum1 + iNum2;
	return(S_OK);

}

HRESULT __stdcall CSumSubtract::MultiplicationOfTwoIntegers(int iNum1, int iNum2, int* iResult)
{
	// Code
	
	m_pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, iResult);
	return(S_OK);

}

HRESULT __stdcall CSumSubtract::DivisionOfTwoIntegers(int iNum1, int iNum2, int* iResult)
{
	// Code

	m_pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, iResult);
	return(S_OK);
}

HRESULT __stdcall CSumSubtract::InitializeInnerComponent() 
{
	// Local Variable Declarations

	HRESULT hr;

	// Code

	hr = CoCreateInstance(CLSID_CMultiplicationDivision, NULL, CLSCTX_INPROC_SERVER, IID_IMultiplication, (void**)&m_pIMultiplication);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IMultiplication Interface cannot obtained from Inner Component"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		return(E_FAIL);
	}

	hr = m_pIMultiplication->QueryInterface(IID_IDivision, (void**)&m_pIDivision);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IDivision Interface cannot obtained from Inner Component"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		return(E_FAIL);
	}

	return(S_OK);
}

CSumSubtractClassFactory::CSumSubtractClassFactory()
{
	// Code

	m_cRef = 1;
}

CSumSubtractClassFactory::~CSumSubtractClassFactory()
{
	// Code
}

HRESULT __stdcall CSumSubtractClassFactory::QueryInterface(REFIID riid, void** ppv)
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

ULONG __stdcall CSumSubtractClassFactory::AddRef(void)
{
	// Code

	InterlockedIncrement(&m_cRef);

	return(m_cRef);
}

ULONG __stdcall CSumSubtractClassFactory::Release(void)
{
	// Code

	InterlockedDecrement(&m_cRef);

	if (NULL == m_cRef)
	{
		delete(this);
		return(0);
	}

	return(m_cRef);
}

HRESULT __stdcall CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void** ppv)
{
	// Local Variable Declarations

	HRESULT hr;
	CSumSubtract* pCSumSubtract = NULL;

	// Code

	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	pCSumSubtract = new CSumSubtract;

	// Initializing Inner Component 

	hr = pCSumSubtract->InitializeInnerComponent();

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Failed To Initialize Inner Component"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		pCSumSubtract->Release();
		return(hr);
	}

	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release();
	return(hr);
}

HRESULT __stdcall CSumSubtractClassFactory::LockServer(BOOL fLock)
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
	CSumSubtractClassFactory* pCSumSubtractClassFactory = NULL;

	// Code

	if (rclsid != CLSID_CSumSubtract)
		return(CLASS_E_CLASSNOTAVAILABLE);

	pCSumSubtractClassFactory = new CSumSubtractClassFactory;

	if (NULL == pCSumSubtractClassFactory)
		return(E_OUTOFMEMORY);

	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();

	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((0 == glNumberOfActiveComponents) && (0 == glNumberOfServerLocks))
		return(S_OK);
	else
		return(S_FALSE);
}

// DllRegisterServer()

extern "C" STDAPI DllRegisterServer()
{
	// Local Variable Declarations

	LONG lRet;
	HKEY hCLSIDKey = NULL;
	HKEY hInProcSvrKey = NULL;
	TCHAR szModulePath[MAX_PATH];
	TCHAR szClassDescription[] = TEXT("Containment Outer Component Without Reg File");
	TCHAR szThreadingModel[] = TEXT("Apartment");

	// Code

	__try
	{
		lRet = RegCreateKeyEx(HKEY_CLASSES_ROOT, TEXT("CLSID\\{6DBE1E08-EAFA-4497-A724-8CDCE0BF5B6E}"), 0, NULL,
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

// DllUnregisterServer()

extern "C" STDAPI DllUnregisterServer()
{
	// Code

	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{6DBE1E08-EAFA-4497-A724-8CDCE0BF5B6E}\\InProcServer32"));
	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{6DBE1E08-EAFA-4497-A724-8CDCE0BF5B6E}"));

	return(S_OK);
}
