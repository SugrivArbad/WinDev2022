/*
	fout << "Outer: " << std::endl;
*/

#include <windows.h>
#include "OuterDllServer.h"
#include "InnerDllServer.h"
#include <iostream>
#include <fstream>

// class declarations
class CSumSubtract : public ISum, ISubtract, IMultiplication, IDivision
{
private:
	long m_cRef;
	IMultiplication* m_pIMultiplication;
	IDivision* m_pIDivision;

public:
	// constructor method declarations
	CSumSubtract(void);
	// destructor method declarations
	~CSumSubtract(void);

	// IUnknown specific methods declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// ISum specific method declarations (inherited)
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

	// ISubtract specific method declarations (inherited)
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

	// IMultiplication specific method declarations (inherited)
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);

	// IDivision specific method declarations (inherited)
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);

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

	// CSumSubtractClassFactory's IClassFactory's IUnknown's specific methods declarations
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// CSumSubtract's IClassFactory's specific methods declarations
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
	fout << "Start DllMain() Outer" << std::endl;

	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;

	case DLL_PROCESS_DETACH:
		break;
	}

	fout << "End DllMain() Outer" << std::endl;
	return (TRUE);
}

// Implementation of CSumSubtract's constructor method
CSumSubtract::CSumSubtract(void)
{
	fout << "Outer: Start CSumSubtract::CSumSubtract() --> m_cRef = " << m_cRef << ", glNumberOfActiveComponents = "<< glNumberOfActiveComponents << std::endl;
	// initialization of private data members
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	m_cRef = 1; // hardcoded initialization to anticipate possible failure of QueryInterface()

	InterlockedIncrement(&glNumberOfActiveComponents); // increment global counter
	fout << "Outer: End CSumSubtract::CSumSubtract() --> m_cRef = " << m_cRef << ", glNumberOfActiveComponents = "<< glNumberOfActiveComponents << std::endl;
}

// Implementation of CSumSubtract's destructor method
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
}

// Implementation of CSumSubtract's IUnknown's specific methods
HRESULT CSumSubtract::QueryInterface(REFIID riid, void** ppv)
{
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
		*ppv = 0;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();

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

// Implementation of CSumSubtract's ISum's specific method
HRESULT CSumSubtract::SumOfTwoIntegers(int n1, int n2, int* pSum)
{
	*pSum = n1 + n2;
	return (S_OK);
}

// Implementation of CSumSubtract's ISubtract's specific method
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int n1, int n2, int* pSubtraction)
{
	*pSubtraction = n1 - n2;
	return (S_OK);
}

// Implementation of CSumSubtract's IMultiplication's specific method
HRESULT CSumSubtract::MultiplicationOfTwoIntegers(int n1, int n2, int* pMultiplication)
{
	// delegate to inner component
	m_pIMultiplication->MultiplicationOfTwoIntegers(n1, n2, pMultiplication);
	return (S_OK);
}

// Implementation of CSumSubtract's IDivision's specific method
HRESULT CSumSubtract::DivisionOfTwoIntegers(int n1, int n2, int* pDivision)
{
	// delegate to inner component
	m_pIDivision->DivisionOfTwoIntegers(n1, n2, pDivision);
	return (S_OK);
}

// Implementation of CSumSubtract's InitializeInnerComponent method
HRESULT CSumSubtract::InitializeInnerComponent(void)
{
	fout << "Start InitializeInnerComponent() Outer" << std::endl;
	// variable declarations
	HRESULT hr;

	hr = CoCreateInstance(CLSID_MultiplicationDivision, NULL, CLSCTX_INPROC_SERVER, IID_IMultiplication, (void**)&m_pIMultiplication);
	if (FAILED(hr))
	{
		fout << "IMultiplication Interface Cannot Be Obtained : InitializeInnerComponent() Outer" << std::endl;
		MessageBox(NULL, TEXT("IMultiplication Interface Cannot Be Obtained From Inner Component."), TEXT("ERROR"), MB_OK);
		return (E_FAIL);
	}

	hr = m_pIMultiplication->QueryInterface(IID_IDivision, (void**)&m_pIDivision);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IDivision Interface Cannot Be Obtained From Inner Component."), TEXT("ERROR"), MB_OK);
		fout << "IDivision Interface Can Not Be Obtained From Inner Component : InitializeInnerComponent() Outer" << std::endl;
		return (E_FAIL);
	}

	fout << "End InitializeInnerComponent() Outer" << std::endl;
	return (S_OK);
}

// Implementation of CSumSubtractClassFactory's constructor method
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	fout << "Outer: Start CSumSubtractClassFactory()" << std::endl;
	m_cRef = 1; // hardcoded initialization to anticipate possible failure of QueryInterface()
	fout << "Outer: End CSumSubtractClassFactory()" << std::endl;
}

// Implementation of CSumSubtractClassFactory's destructor method
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
	// no code
}

// Implementation of CSumSubtractClassFactory's IClassFactory's IUnknown's methods
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	fout << "Outer: Start CSumSubtractClassFactory::QueryInterface()" << std::endl;
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory*>(this);
	else
	{
		*ppv = NULL;
		fout << "Outer: E_NOINTERFACE: CSumSubtractClassFactory::QueryInterface() --> REFIID riid = " << std::endl;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();

	fout << "Outer: End CSumSubtractClassFactory::QueryInterface()" << std::endl;
	return (S_OK);
}

ULONG CSumSubtractClassFactory::AddRef(void)
{
	fout << "Outer: Start CSumSubtractClassFactory::AddRef() -> m_cRef = " << m_cRef << std::endl;
	InterlockedIncrement(&m_cRef);
	fout << "Outer: End CSumSubtractClassFactory::AddRef() -> m_cRef = " << m_cRef << std::endl;
	return (m_cRef);
}

ULONG CSumSubtractClassFactory::Release(void)
{
	fout << "Outer: Start CSumSubtractClassFactory::Release() -> m_cRef = " << m_cRef << std::endl;
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete (this);
		fout << "Outer: End CSumSubtractClassFactory::Release() -> m_cRef = " << 0 << std::endl;
		return (0);
	}

	fout << "Outer: End CSumSubtractClassFactory::Release() -> m_cRef = " << m_cRef << std::endl;
	return (m_cRef);
}

// Implementation of CSumSubtractClassFactory's IClassFactory's methods
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	fout << "Outer: Start CSumSubtractClassFactory::CreateInstance()" << std::endl;
	// variable declarations
	CSumSubtract* pCSumSubtract = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
	{
		fout << "Outer: CLASS_E_NOAGGREGATION CSumSubtractClassFactory::CreateInstance() --> pUnkOuter != NULL" << std::endl;
		return (CLASS_E_NOAGGREGATION);
	}

	// create the instance of component i.e. of CSumSubtract class
	pCSumSubtract = new CSumSubtract;

	if (pCSumSubtract == NULL)
	{
		fout << "Outer: E_OUTOFMEMORY: CSumSubtractClassFactory::CreateInstance() --> pCSumSubtract == NULL" << std::endl;
		return (E_OUTOFMEMORY);
	}

	// initialize inner component
	hr = pCSumSubtract->InitializeInnerComponent();
	if (FAILED(hr))
	{
		fout << "Outer: Failed To Initialize Inner Component.: CSumSubtractClassFactory::CreateInstance() --> hr = " << hr << std::endl;
		MessageBox(NULL, TEXT("Failed To Initialize Inner Component."), TEXT("ERROR"), MB_OK);
		pCSumSubtract->Release();
		return (hr);
	}

	// get the requested interface
	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release(); // anticipate possible failure of QueryInterface()
	fout << "Outer: End CSumSubtractClassFactory::CreateInstance()" << std::endl;
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
	fout.open("C:\\Sugriv\\WinDev2022\\02-COM\\02-Containment\\03-ClientDeveloperUser\\ClientLogs.txt", std::ios::app);
	fout << "Outer: Start DllGetClassObject()" << std::endl;

	// variable declarations
	CSumSubtractClassFactory* pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_SumSubtract)
	{
		fout << "Outer: CLASS_E_CLASSNOTAVAILABLE: rclsid != CLSID_SumSubtract" << std::endl;
		return (CLASS_E_CLASSNOTAVAILABLE);
	}

	// create class factory
	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	if (pCSumSubtractClassFactory == NULL)
	{
		fout << "Outer: E_OUTOFMEMORY: pCSumSubtractClassFactory == NULL" << std::endl;
		return (E_OUTOFMEMORY);
	}

	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release(); // anticipate possible failure of QueryInterface()

	fout << "Outer: End DllGetClassObject()" << std::endl;
	return (hr);
}

HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return (S_OK);
	else
		return (S_FALSE);
}

