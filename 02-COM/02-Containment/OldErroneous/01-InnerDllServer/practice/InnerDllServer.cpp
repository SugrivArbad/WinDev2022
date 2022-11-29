// this code represents Binary Encapsulation
// CMultiplicationDivision and CMultiplicationDivisionClassFactory hidden from client
#include <windows.h>
#include "InnerDllServer.h"

// CoClass
// Com cha class kinva 
// Concrete class - means cannot be base class i.e. no virtual functions 
class CMultiplicationDivision : public IMultiplication, IDivisionI
{
private:
	long m_cRef;

public:
	// constructor
	CMultiplicationDivision(void);		// void for backward compatibility

	// destructor
	~CMultiplicationDivision(void);

	// IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IMultiplication method
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);

	// ISubtract method
	HRESULT __stdcall DivisionTwoIntegers(int, int, int*);
};

// class FactoryClass
class CMultiplicationDivisionClassFactory : public IClassFactory
{
private:
	long m_cRef;

public:
	// constructor
	CMultiplicationDivisionClassFactory(void);

	// destructor
	~CMultiplicationDivisionClassFactory(void);

	// IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassFactory methods
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

// global variables
long glNumberOfActiveComponents;
long glNumberOfServerLocks;

// Hungarian Notation
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	//code
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

	return (TRUE);
}

// CMultiplicationDivision implementation
// constructor
CMultiplicationDivision::CMultiplicationDivision(void)
{
	// code
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

// destructor
CMultiplicationDivision::~CMultiplicationDivision(void)
{
	// code
	InterlockedDecrement(&glNumberOfActiveComponents);
}

// IUnknown Methods implementation
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void** ppv)
{
	// code
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMultiplication*>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication*>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision*>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return (S_OK);
}

ULONG CMultiplicationDivision::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CMultiplicationDivision::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete (this);
		return (0);
	}
	return (m_cRef);
}

// IMultiplication method implementation
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int* pMultiplication)
{
	// code
	*pMultiplication = num1 * num2;
	return (S_OK);
}

// ISubtract method implementation
HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int* pDivision)
{
	// code
	*pDivision = num1 / num2;
	return (S_OK);
}

// CMultiplicationDivisionClassFactory implementation
// condtructor
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
	// code
	m_cRef = 1;
}

// destructor
CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
{
	// code
}

// IUnknown methods implementation
HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	// code
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

ULONG CMultiplicationDivisionClassFactory::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CMultiplicationDivisionClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete (this);
		return (0);
	}
	return (m_cRef);
}

// IClassFactory methods implementation
HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	// variable declarations
	CMultiplicationDivision* pCMultiplicationDivision = NULL;
	HRESULT hr;

	// code
	if (pUnkOuter != NULL)
		return (CLASS_E_NOAGGREGATION);
	pCMultiplicationDivision = new CMultiplicationDivision;
	if (pCMultiplicationDivision == NULL)
		return (E_OUTOFMEMORY);
	hr = pCMultiplicationDivision->QueryInterface(riid, ppv);
	pCMultiplicationDivision->Release();
	return (hr);
}

HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
{
	// code
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return (S_OK);
}

// exportable COM DLL methods
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	// variable declarations
	CMultiplicationDivisionClassFactory* pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;
	if (rclsid != CLSID_MultiplicationDivision)
		return (CLASS_E_CLASSNOTAVAILABLE);
	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;
	if (pCMultiplicationDivisionClassFactory == NULL)
		return (E_OUTOFMEMORY);
	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid,ppv);
	pCMultiplicationDivisionClassFactory->Release();
	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	// code
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
		return (S_OK);
	else
		return (S_FALSE);
}
