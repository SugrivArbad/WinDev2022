#include <Windows.h>
#include "ContainmentInnerServer.h"


// class declarations
class CMultiplicationDivision : public IMultiplication, IDivision
{
private:
	long m_cRef;

public:
	// constructor method declarations
	CMultiplicationDivision(void);
	// destructor method declarations
	~CMultiplicationDivision(void);

	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IMultiplication specific method declarations (inherited)
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);

	// IDivison specific method declarations (inherited)
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
};

class CMultiplicationDivisionClassFactory : IClassFactory
{
private:
	long m_cRef;

public:
	// constructor method declarations
	CMultiplicationDivisionClassFactory(void);
	// destructor method declarations
	~CMultiplicationDivisionClassFactory(void);

	// IUnknown specific methods declarations
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory specific methods declarations
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

// global variable declarations
long glNumberOfActiveComponents = 0; // number of active components
long glNumberOfServerLocks = 0; // number of locks on this dll

// DllMain
BOOL WINAPI DllMain(HINSTANCE hdll, DWORD dwReason, LPVOID lpReserved)
{
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

// Implementation of CMultiplicationDivision's Constructor Method
CMultiplicationDivision::CMultiplicationDivision(void)
{
	m_cRef = 1; // hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents); // increment global counter
}

// Implementation of CMultiplicationDivision's destructor method
CMultiplicationDivision::~CMultiplicationDivision(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents); // decrement global counter
}

// Implementation of CMultiplicationDivision's IUnknown's Methods
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void** ppv)
{
    MessageBox(NULL, TEXT("CMultiplicationDivision::QueryInterface() start"), TEXT("Error"), MB_OK);
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMultiplication*>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication*>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision*>(this);
	else
	{
		*ppv = NULL;
        MessageBox(NULL, TEXT("E_NOINTERFACE : CMultiplicationDivision::QueryInterface() end"), TEXT("Error"), MB_OK);
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
    MessageBox(NULL, TEXT("CMultiplicationDivision::QueryInterface() end"), TEXT("Error"), MB_OK);

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

// Implementation of CMultiplicationDivision's IMultiplication's method
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int* pMultiplication)
{
    MessageBox(NULL, TEXT("Inner CMultiplicationDivision::MultiplicationOfTwoIntegers() start"), TEXT("Error"), MB_OK);
	*pMultiplication = num1 * num2;
	return (S_OK);
}

// Implementation of CMultiplicationDivision's IDivision's method
HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int* pDivision)
{
    MessageBox(NULL, TEXT("Inner CMultiplicationDivision::DivisionOfTwoIntegers() start"), TEXT("Error"), MB_OK);
	*pDivision = num1 / num2;
	return (S_OK);
}

// Implementation of CMultiplicationDivisionClassFactory's Constructor Method
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
	m_cRef = 1; // hardcoded initialization to anticipate possible failure of QueryInterface()
}

CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
{
	// no code
}

HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void** ppv)
{
    MessageBox(NULL, TEXT("CMultiplicationDivisionClassFactory::QueryInterface() start"), TEXT("Error"), MB_OK);
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

    MessageBox(NULL, TEXT("CMultiplicationDivisionClassFactory::QueryInterface() end"), TEXT("Error"), MB_OK);
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

HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
    MessageBox(NULL, TEXT("CMultiplicationDivisionClassFactory::CreateInstance() start"), TEXT("Error"), MB_OK);
	// local variable declarations
	CMultiplicationDivision* pCMultiplicationDivision = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return (CLASS_E_NOAGGREGATION);

	// create the instance of component i.e. of CMultiplicationDivision class
	pCMultiplicationDivision = new CMultiplicationDivision;
	if (pCMultiplicationDivision == NULL)
		return (E_OUTOFMEMORY);

	// get the requested interface
	hr = pCMultiplicationDivision->QueryInterface(riid, ppv);

	pCMultiplicationDivision->Release(); // anticipate possible failure of QueryInterface()
    MessageBox(NULL, TEXT("CMultiplicationDivisionClassFactory::CreateInstance() end"), TEXT("Error"), MB_OK);
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

// Implementation of Exported From This Dll
HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
    MessageBox(NULL, TEXT("Inner DllGetClassObject() start"), TEXT("Error"), MB_OK);
	// variable declarations
	CMultiplicationDivisionClassFactory* pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_MultiplicationDivision)
		return (CLASS_E_CLASSNOTAVAILABLE);

	// create instance of CMultiplicatonDivisionClassFactory
	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;
	if (pCMultiplicationDivisionClassFactory == NULL)
		return (E_OUTOFMEMORY);

	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);

	// anticipate possible failure of QueryInterface()
	pCMultiplicationDivisionClassFactory->Release();
    MessageBox(NULL, TEXT("Inner DllGetClassObject() end"), TEXT("Error"), MB_OK);

	return(hr);
}

HRESULT __stdcall DllCanUnloadNow(void)
{
    MessageBox(NULL, TEXT("DllCanUnloadNow() start"), TEXT("Error"), MB_OK);
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return (S_OK);
	else
		return (S_FALSE);
}

