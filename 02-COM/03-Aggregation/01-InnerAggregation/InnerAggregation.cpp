#include <windows.h>
#include "InnerAggregation.h"
#include <iostream>
#include <fstream>

// interface declarations ( for internal use only. i.e. not to be declared in .h file )
interface INoAggregationIUnknown // new
{
	virtual HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**) = 0;
	virtual ULONG __stdcall AddRef_NoAggregation(void) = 0;
	virtual ULONG __stdcall Release_NoAggregation(void) = 0;
};

// class declarations
class CMultiplicationDivision : public INoAggregationIUnknown, IMultiplication, IDivision
{
private:
	long m_cRef;
	IUnknown* m_pIUnknownOuter;

public:
	CMultiplicationDivision(IUnknown*); // constructor method declarations

	~CMultiplicationDivision(void); // destructor method declarations

	// Aggregation Supported IUnknown speicific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// Aggregation NonSupported IUnknown specific method (inherited)
	HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**); // new
	ULONG __stdcall AddRef_NoAggregation(void); // new
	ULONG __stdcall Release_NoAggregation(void); // new

	// IMultiplication specific method declarations
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);

	// IDivision speicific method declarations
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
};

class CMultiplicationDivisionClassFactory : public IClassFactory
{
private:
	long m_cRef;

public:
	// constructor method declarations
	CMultiplicationDivisionClassFactory(void);
	// destructor method declarations
	~CMultiplicationDivisionClassFactory(void);

	// IUnknown specific method declarations
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory specific method declarations
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

// global variable declarations
long glNumberOfActiveComponents = 0; // number of active components
long glNumberOfServerLocks = 0; // number of locks on this dll
std::ofstream fout;

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
	// code
	fout.open("C:\\Sugriv\\WinDev2022\\02-COM\\03-Aggregation\\03-ClientAggregation\\ClientLogs.log", std::ios::out);
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}

	return (TRUE);
}

// Implementation of CMultiplicationDivision's constructor method
CMultiplicationDivision::CMultiplicationDivision(IUnknown* pIUnknownOuter)
{
	m_cRef = 1; // hardcoded initialization to anticipate possible failure of QueryInterface()

	InterlockedIncrement(&glNumberOfActiveComponents); // increment global counter

	if (pIUnknownOuter != NULL)
		m_pIUnknownOuter = pIUnknownOuter;
	else
		m_pIUnknownOuter = reinterpret_cast<IUnknown*>(static_cast<INoAggregationIUnknown*>(this));
}

// Implementation of CMultiplicationDivision's Destructor method
CMultiplicationDivision::~CMultiplicationDivision(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents); // decrement global counter
}

// Implementation of CMultiplicationDivision's Aggregation Supporting IUnknown's methods
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void** ppv)
{
	return (m_pIUnknownOuter->QueryInterface(riid, ppv));
}

ULONG CMultiplicationDivision::AddRef(void)
{
	return (m_pIUnknownOuter->AddRef());
}

ULONG CMultiplicationDivision::Release(void)
{
	return (m_pIUnknownOuter->Release());
}

// Implementation of CMultiplicationDivision's Aggregation NonSupporting IUnknown's methods
HRESULT CMultiplicationDivision::QueryInterface_NoAggregation(REFIID riid, void** ppv)
{
	fout << "Start QueryInterface_NoAggregation()" << std::endl;
	if (riid == IID_IUnknown)
		*ppv = static_cast<INoAggregationIUnknown*>(this); // method coloring
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication*>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision*>(this);
	else
	{
		*ppv = NULL;
		fout << "Error E_NOINTERFACE" << std::endl;
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	fout << "End QueryInterface_NoAggregation()" << std::endl;
	return (S_OK);
}

ULONG CMultiplicationDivision::AddRef_NoAggregation(void)
{
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CMultiplicationDivision::Release_NoAggregation(void)
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
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int* pMultiplication)
{
	*pMultiplication = num1 * num2;
	return (S_OK);
}

// Implementation of IDivision's method
HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int* pDivision)
{
	*pDivision = num1 / num2;
	return (S_OK);
}

// Implementation of CMultiplicationDivisionClassFactory's constructor method
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
	m_cRef = 1; // hardcoded initialization to anticipate possible failure of QueryInterface()
}

// Implementation of CSumSubtractClassFactory's destructor method
CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
{
	// no code
}

// Implementation of CMultiplicationDivisionClassFactory's IClassFactory's IUnknwon's methods
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

// Implemtation of CMultiplicationDivisionClassFactory's IClassFactory's methods
HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	fout << "start CreateInstance() Inner" << std::endl;
	// variable declarations
	CMultiplicationDivision* pCMultiplicationDivision = NULL;
	HRESULT hr;

	if ((pUnkOuter != NULL) && (riid != IID_IUnknown))
	{
		fout << "Error CLASS_E_CLASSNOTAVAILABLE" << std::endl;
		return (CLASS_E_NOAGGREGATION);
	}

	// create the instance of component i.e. of CMultiplicationDivision class
	pCMultiplicationDivision = new CMultiplicationDivision(pUnkOuter);
	if (pCMultiplicationDivision == NULL)
	{
		fout << "Error E_OUTOFMEMORY" << std::endl;
		return (E_OUTOFMEMORY);
	}

	// get the requested interface
	hr = pCMultiplicationDivision->QueryInterface_NoAggregation(riid, ppv);

	// anticipate possible failure of QueryInterface()
	pCMultiplicationDivision->Release_NoAggregation();

	fout << "end CreateInstance() Inner" << std::endl;
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
	if (pCMultiplicationDivisionClassFactory == NULL)
		return (E_OUTOFMEMORY);

	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);

	// anticipate possible faillure of QueryInterface()
	pCMultiplicationDivisionClassFactory->Release();

	return (hr);
}

HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return (S_OK);
	else
		return (S_FALSE);
}

