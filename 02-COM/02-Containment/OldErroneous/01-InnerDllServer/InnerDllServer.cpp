#include <windows.h>
#include "InnerDllServer.h"
#include <iostream>
#include <fstream>

class CMultiplicationDivision : public IMultiplication, IDivision
{
private:
	long m_cRef;

public:
	// constructor method declarations
	CMultiplicationDivision(void);
	// destructor method declarations
	~CMultiplicationDivision(void);

	// IUnknown specific methods declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IMultiplication specific method declarations (inherited)
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);

	// IDivision specific method declarations (inherited)
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
};

class CMultiplicationDivisionClassFactory : public IClassFactory
{
private:
	long m_cRef;
	
public:
	// constructor method declarations
	CMultiplicationDivisionClassFactory(void);
	// destrucot method declarations
	~CMultiplicationDivisionClassFactory(void);

	// IUnknown specific methods declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory specific methods declarations
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

// global variable declarations
long glNumberOfActiveComponents = 0; // number of active components
long glNumberOfServerLocks = 0; // number of server locks
std::ofstream fout;

// DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
	fout.open("C:\\Sugriv\\WinDev2022\\02-COM\\02-Containment\\03-ClientDeveloperUser\\ClientLogs.txt", std::ios::app);
	fout << "DllMain()" << std::endl;

	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	
	case DLL_PROCESS_DETACH:
		break;
	}

	fout << "DllMain()" << std::endl;
	return (TRUE);
}

// Implementation of CMultiplicationDivision's Constructor method
CMultiplicationDivision::CMultiplicationDivision(void)
{
	m_cRef = 1;	// hardcore initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents); // Increment global counter
}

// Implementation of CMultiplicationDivision's Destructor method
CMultiplicationDivision::~CMultiplicationDivision(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents); // Decrement global counter
}

// Implementation of CMultiplicationDivision's IUnknown's methods
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMultiplication*>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication*>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision*>(this);
	else
	{
		ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();

	return (S_OK);
}

ULONG CMultiplicationDivision::AddRef(void)
{
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

// Implementation of IMultiplication's method
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int n1, int n2, int* pMultiplication)
{
	*pMultiplication = n1 * n2;
	return (S_OK);
}

// Implementation of IDivision's method
HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int n1, int n2, int* pDivision)
{
	*pDivision = n1 / n2;
	return (S_OK);
}

// Implementation of CMultiplicationDivisionClassFactory's constructor method
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
	m_cRef = 1; // hardcore initialization to anticipate possible failure of QueryInterface
}

// Implementation of CMultiplicationDivisionClassFactory's destructor method
CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
{
	// no code
}

// Implementation of CMultiplicationDivisionClassFactory's IClassFactory's IUnknown's method 
HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void** ppv)
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

ULONG CMultiplicationDivisionClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CMultiplicationDivisionClassFactory::Release()
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete (this);
		return (0);			// changed
	}

	return (m_cRef);
}

// Implementation of CMultiplicationDivisionClassFactory's IClassFactory's methods
HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	// variable declarations
	CMultiplicationDivision* pCMultiplicationDivision = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return (CLASS_E_NOAGGREGATION);

	// create instance of component i.e. of CMultiplicationDivision class
	pCMultiplicationDivision = new CMultiplicationDivision;
	if (pCMultiplicationDivision == NULL)
		return (E_OUTOFMEMORY);

	// get the requested interface
	hr = pCMultiplicationDivision->QueryInterface(riid, ppv);

	pCMultiplicationDivision->Release(); // anticipate possible failure of QueryInterface()
	return (hr);
}

HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);

	return (S_OK);
}

// Implementation of exported functions from this DLL
HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	// variable declarations
	CMultiplicationDivisionClassFactory* pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_MultiplicationDivision)
		return (CLASS_E_CLASSNOTAVAILABLE);

	// create class factory
	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;
	if (pCMultiplicationDivisionClassFactory != NULL)
		return (E_OUTOFMEMORY);

	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);
	pCMultiplicationDivisionClassFactory->Release(); // anticipate possible failure of QueryInterface()

	return (hr);
}

HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return (S_OK);
	else
		return (S_FALSE);
}

