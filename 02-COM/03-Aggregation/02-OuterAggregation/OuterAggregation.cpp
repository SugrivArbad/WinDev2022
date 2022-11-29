#include <windows.h>
#include "InnerAggregation.h"
#include "OuterAggregation.h"
#include <iostream>
#include <fstream>

// class declarations
class CSumSubtract : public ISum, ISubtract
{
private:
	long m_cRef;
	IUnknown* m_pIUnknownInner;
	IUnknown* m_pIMultiplication;
	IUnknown* m_pIDivision;

public:
	CSumSubtract(void); // constructor method declarations

	~CSumSubtract(void); // destructor method declarations

	// IUnknown speicific methods declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// ISum specific method declarations (inherited)
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

	// ISubtract speicific method declarations (inherited)
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

	// custom method for inner component creation
	HRESULT __stdcall InitializeInnerComponent(void);
};

class CSumSubtractClassFactory : public IClassFactory
{
private:
	long m_cRef;

public:
	// constructor method declarations
	CSumSubtractClassFactory(void);
	// destructor method declarations
	~CSumSubtractClassFactory(void);

	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

// global variable declarations
long glNumberOfActiveComponents = 0; // number of active components
long glNumberOfServerLocks = 0; // number of locks on this dll
std::ofstream fout;

// DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
	fout.open("C:\\Sugriv\\WinDev2022\\02-COM\\03-Aggregation\\03-ClientAggregation\\ClientLogs.log", std::ios::app);
	// code
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}

	return (TRUE);
}

// Implementation of CSumSubtract's constructor method
CSumSubtract::CSumSubtract(void)
{
	// initialization of private data members
	m_pIUnknownInner = NULL;
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	m_cRef = 1; // hardcoded initialization to anticipate possible failure of QueryInterface()

	InterlockedIncrement(&glNumberOfActiveComponents); // increment global counter
}

// Implementation of CSumSubtract's Destructor method
CSumSubtract::~CSumSubtract(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents); // decrement global counter

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

	if (m_pIUnknownInner)
	{
		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;
	}
}

// Implementation of CSumSubtract's Aggregation Supporting IUnknown's methods
HRESULT CSumSubtract::QueryInterface(REFIID riid, void** ppv)
{
	fout << "Start QueryInterface() Outer" << std::endl;
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract*>(this);
	else if (riid == IID_IMultiplication)
		return (m_pIUnknownInner->QueryInterface(riid, ppv));
	else if (riid == IID_IDivision)
		return (m_pIUnknownInner->QueryInterface(riid, ppv));
	else
	{
		*ppv = NULL;
		fout << "Error : E_NOINTERFACE QueryInterface() Outer" << std::endl;
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	fout << "End QueryInterface() Outer" << std::endl;
	return (S_OK);
}

ULONG CSumSubtract::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubtract::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete (this);
		return (0);
	}

	return (m_cRef);
}

// Implementation of ISum's method
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int* pSum)
{
	*pSum = num1 + num2;
	return (S_OK);
}

// Implementation of ISubtract's method
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int* pSubtract)
{
	*pSubtract = num1 - num2;
	return (S_OK);
}

// Implementation of CSumSubtract's method
HRESULT CSumSubtract::InitializeInnerComponent(void)
{
	fout << "Start InitializeInnerComponent() outer" << std::endl;
	// variable declarations
	HRESULT hr;

	hr = CoCreateInstance(CLSID_MultiplicationDivision,
		reinterpret_cast<IUnknown*>(this),
		CLSCTX_INPROC_SERVER,
		IID_IUnknown,
		(void**)&m_pIUnknownInner);
	fout << "Before IUnknown error : outer" << std::endl;
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IUnknown Interface Cannot Be Obtained From Inner Component."), TEXT("Error"), MB_OK);
		return (E_FAIL);
	}

	hr = m_pIUnknownInner->QueryInterface(IID_IMultiplication, (void**)&m_pIMultiplication);
	fout << "Before IMultiplication error : outer" << std::endl;
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IMultiplication Interface Cannot Be Obtained From Inner Component."), TEXT("Error"), MB_OK);

		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;

		return (E_FAIL);
	}

	hr = m_pIUnknownInner->QueryInterface(IID_IDivision, (void**)&m_pIDivision);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IDivision Interface Cannot Be Obtained From Inner Component."), TEXT("Error"), MB_OK);

		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;

		return (E_FAIL);
	}

	fout << "End InitializeInnerComponent() outer" << std::endl;
	return (S_OK);
}

// Implementation of CSumSubtractClassFactory's constructor method
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	m_cRef = 1; // hardcoded initialization to anticipate possible failure of QueryInterface()
}

// Implementation of CSumSubtractClassFactory's destructor method
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
	// no code
}

// Implementation of CSumSubtractClassFactory's IClassFactory's IUnknwon's methods
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void** ppv)
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

ULONG CSumSubtractClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubtractClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete (this);
		return (0);
	}

	return (m_cRef);
}

// Implemtation of CSumSubtractClassFactory's IClassFactory's methods
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	fout << "Start CreateInstance()" << std::endl;
	// variable declarations
	CSumSubtract* pCSumSubtract = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return (CLASS_E_NOAGGREGATION);

	// create the instance of component i.e. of CSumSubtract class
	pCSumSubtract = new CSumSubtract;
	if (pCSumSubtract == NULL)
		return (E_OUTOFMEMORY);

	// initialize inner component
	hr = pCSumSubtract->InitializeInnerComponent();
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Failed To Initialize Inner Component."), TEXT("Error"), MB_OK);
		pCSumSubtract->Release();
		return (hr);
	}

	// get the requested interface
	hr = pCSumSubtract->QueryInterface(riid, ppv);

	// anticipate possible failure of QueryInterface()
	pCSumSubtract->Release();

	fout << "End CreateInstance() Outer" << std::endl;
	return (hr);
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
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
	CSumSubtractClassFactory* pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_SumSubtract)
		return (CLASS_E_CLASSNOTAVAILABLE);

	// create class factory
	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	if (pCSumSubtractClassFactory == NULL)
		return (E_OUTOFMEMORY);

	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);

	// anticipate possible faillure of QueryInterface()
	pCSumSubtractClassFactory->Release();

	return (hr);
}

HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return (S_OK);
	else
		return (S_FALSE);
}

