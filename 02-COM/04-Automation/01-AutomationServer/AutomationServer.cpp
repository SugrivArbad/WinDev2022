//#define UNICODE

// Header Files
#include <Windows.h>
#include <stdio.h>		// for swprintf_s()
#include "AutomationServer.h"

// coclass class declaration
class CMyMath : public IMyMath
{
private:
	long m_cRef;
	ITypeInfo* m_pITypeInfo;

public:
	// constructor method declarations
	CMyMath(void);
	// destructor method declaration
	~CMyMath(void);

	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IDispatch specific method declarations (inherited)
	HRESULT __stdcall GetTypeInfoCount(UINT*);
	HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo**);
	HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*);
	HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);

	// ISum specific method declarations (inherited)
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

	// ISubtract specific method declarations (inherited)
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

	// custom methods
	HRESULT InitInstance(void);
};

// class factory declaration
class CMyMathClassFactory : public IClassFactory
{
private:
	long m_cRef;

public:
	// constructor method declarations
	CMyMathClassFactory(void);
	// destructor method declarations
	~CMyMathClassFactory(void);

	// IUnknown specific methods declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

// global DLL handle
HMODULE ghModule = NULL;

// global variable declarations
long glNumberOfActiveComponents = 0; // number of active components
long glNumberOfServerLocks = 0;		 // number of locks on this dll

// {08D922D6-91D2-45D1-A0A1-197ABA6BCA5B}
const GUID LIBID_AutomationServer = { 0x8d922d6, 0x91d2, 0x45d1, 0xa0, 0xa1, 0x19, 0x7a, 0xba, 0x6b, 0xca, 0x5b };

// DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		ghModule = hDll;
		break;

	case DLL_PROCESS_DETACH:
		break;
	}

	return (TRUE);
}

// Implementation of CMyMath's Constructor Method
CMyMath::CMyMath(void)
{
	m_cRef = 1; // hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents); // increment global counter
	m_pITypeInfo = NULL;
}

// Implemetation of CMyMath's Destructor Method
CMyMath::~CMyMath(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents); // decrement global counter
	if (m_pITypeInfo)
	{
		m_pITypeInfo->Release();
		m_pITypeInfo = NULL;
	}
}

// Implementation of CMyMath's IUnknown IUnknown's Methods
HRESULT CMyMath::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMyMath*>(this);
	else if (riid == IID_IDispatch)
		*ppv = static_cast<IMyMath*>(this);
	else if (riid == IID_IMyMath)
		*ppv = static_cast<IMyMath*>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CMyMath::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CMyMath::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete (this);
		return (0);
	}

	return (m_cRef);
}

// Implementation of IDispatch's methods
HRESULT CMyMath::GetTypeInfoCount(UINT* pCountTypeInfo)
{
	// as we have type library it is 1, else 0
	*pCountTypeInfo = 1;

	return (S_OK);
}

HRESULT CMyMath::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo** ppITypeInfo)
{
	*ppITypeInfo = NULL;

	if (iTypeInfo != 0)
		return (DISP_E_BADINDEX);

	m_pITypeInfo->AddRef();

	*ppITypeInfo = m_pITypeInfo;

	return (S_OK);
}

HRESULT CMyMath::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId)
{
	return (DispGetIDsOfNames(m_pITypeInfo, rgszNames, cNames, rgDispId));
}

HRESULT CMyMath::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr)
{
	// variable declarations
	HRESULT hr;

	hr = DispInvoke(this,
		m_pITypeInfo,
		dispIdMember,
		wFlags,
		pDispParams,
		pVarResult,
		pExcepInfo,
		puArgErr);

	return (hr);
}

// Implementation of IMyMath's Methods
HRESULT CMyMath::SumOfTwoIntegers(int num1, int num2, int* pSum)
{
	*pSum = num1 + num2;
	return (S_OK);
}

HRESULT CMyMath::SubtractionOfTwoIntegers(int num1, int num2, int* pSubtract)
{
	*pSubtract = num1 - num2;
	return (S_OK);
}

HRESULT CMyMath::InitInstance(void)
{
	// function declarations
	void ComErrorDescriptionString(HWND, HRESULT);

	// variable declarations
	HRESULT hr;
	ITypeLib* pITypeLib = NULL;

	// code
	if (m_pITypeInfo == NULL)
	{
		hr = LoadRegTypeLib(LIBID_AutomationServer,
			1, 0, // major/minor version numbers
			0x00, // LANG_NEUTRAL(EN, US)
			&pITypeLib);

		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			return (hr);
		}

		hr = pITypeLib->GetTypeInfoOfGuid(IID_IMyMath, &m_pITypeInfo);

		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			pITypeLib->Release();
			return (hr);
		}

		pITypeLib->Release();
	}

	return (S_OK);
}

// Implementation of CMyMathClassFactory's Constructor Method
CMyMathClassFactory::CMyMathClassFactory(void)
{
	m_cRef = 1; // hardcoded initialization to anticipate possible failure of QueryInterface()
}

// Implementation of CMyMathClassFactory's Destructor Method
CMyMathClassFactory::~CMyMathClassFactory(void)
{
	// no code (nothing for us)
}

// Implementation of CMyMathClassFactory's IClassFactory's IUnknown's Methods
HRESULT CMyMathClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory*>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();

	return (S_OK);
}

ULONG CMyMathClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CMyMathClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete (this);
		return (0);
	}

	return (m_cRef);
}

// Implementation of CMyMathClassFactory's IClassFactory's Methods
HRESULT CMyMathClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	// variable declarations
	CMyMath* pCMyMath = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return (CLASS_E_NOAGGREGATION);

	// create the instance of component i.e. of CMyMath class
	pCMyMath = new CMyMath;
	if (pCMyMath == NULL)
		return (E_OUTOFMEMORY);

	// call automation related init method
	pCMyMath->InitInstance();

	// get the requested interface
	hr = pCMyMath->QueryInterface(riid, ppv);

	pCMyMath->Release(); // anticipate possible failure of QueryInterface()

	return (hr);
}

HRESULT CMyMathClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);

	return (S_OK);
}

// Implementation of Exported Functions From This Dll
HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	// variable declarations
	CMyMathClassFactory* pCMyMathClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_MyMath)
		return (CLASS_E_NOAGGREGATION);

	// create class factory
	pCMyMathClassFactory = new CMyMathClassFactory;

	if (pCMyMathClassFactory == NULL)
		return (E_OUTOFMEMORY);

	hr = pCMyMathClassFactory->QueryInterface(riid, ppv);

	pCMyMathClassFactory->Release(); // anticipate possible failure of QueryInterface()

	return (hr);
}

HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return (S_OK);
	else
		return (S_FALSE);
}

void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	// varible declarations
	TCHAR* szErrorMessage = NULL;
	TCHAR str[255];

	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);

	// LPTSTR - Long Pointer Terminated String
	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szErrorMessage, 0, NULL) != 0)
	{
		swprintf_s(str, TEXT("%#x : %s"), hr, szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
		swprintf_s(str, TEXT("[Could not find a description for error # %#x.]\n"), hr);

	MessageBox(hwnd, str, TEXT("COM Error"), MB_OK);
}

