#include <Windows.h>
#include "ContainmentInnerServer.h"
#include "ContainmentOuterServer.h"

class CSumSubtract : public ISum, ISubtract, IMultiplication, IDivision
{
private:
	long m_cRef;
	IMultiplication* m_pIMultiplication;
	IDivision* m_pIDivision;

public:
	// CSumSubtract constructor declarations
	CSumSubtract(void);
	// CSumSubtract destructor declarations
	~CSumSubtract(void);

	// IUnknown specific methods declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// ISum specific method declarations (inherited)
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

	// ISubtract specific method declaration (inherited)
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

	// IMultiplication specific method declarations (inherited)
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);

	// IDivision specific method declarations (inherited)
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);

	// to initialize innner component method declarations
	HRESULT __stdcall InitializeInnerComponent(void);
};

class CSumSubtractClassFactory : public IClassFactory
{
private:
	long m_cRef;

public:
	// CSumSubtractClassFactory constructor declarations
	CSumSubtractClassFactory(void);
	// CSumSubtractClassFactory destructor declarations
	~CSumSubtractClassFactory(void);

	// IClassFactory's IUnknown's methods declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory's methods declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

// global variable declarations
long glNumberOfActiveComponents = 0; // number of active components
long glNumberOfServerLocks = 0; // number of locks on this DLL

// DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
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

// implementation of CSumSubtract's constructor method
CSumSubtract::CSumSubtract(void)
{
	// initialization of private data members 
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	m_cRef = 1; // hardcoded initialization to anticipate possible failure of QueryInterface()
}

// implementation of CSumSubtract's destructor method
CSumSubtract::~CSumSubtract(void)
{
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

// implementation of CSumSubtract's IUnknown's methods
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
		*ppv = NULL;
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

// implementation of ISum's method
HRESULT CSumSubtract::SumOfTwoIntegers(int iNum1, int iNum2, int* piSum)
{
	*piSum = iNum1 + iNum2;
	return (S_OK);
}

// implementation of ISubtract's method
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int iNum1, int iNum2, int* piSubtract)
{
	*piSubtract = iNum1 - iNum2;
	return (S_OK);
}

// implementation of IMultiplication's method
HRESULT CSumSubtract::MultiplicationOfTwoIntegers(int iNum1, int iNum2, int* piMultiplication)
{
	m_pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, piMultiplication);
	return (S_OK);
}

// implementation of IDivision's method
HRESULT CSumSubtract::DivisionOfTwoIntegers(int iNum1, int iNum2, int* piDivision)
{
	m_pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, piDivision);
	return (S_OK);
}

// implementation of initialization of inner component method
HRESULT CSumSubtract::InitializeInnerComponent(void)
{
    // local variable declarations
	HRESULT hr;
    TCHAR str[255];

    wsprintf(str, TEXT("CSumSubtract::InitializeInnerComponent() start : m_pIMultiplication = %lu"), (long long)m_pIMultiplication);
    MessageBox(NULL, str, TEXT("Error"), MB_OK);

	hr = CoCreateInstance(CLSID_MultiplicationDivision, NULL, CLSCTX_INPROC_SERVER, IID_IMultiplication, (void**)&m_pIMultiplication);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IMultiplication interface cannot be obtained from inner component"), TEXT("Error"), MB_OK);
		return (E_FAIL);
	}

    wsprintf(str, TEXT("CSumSubtract::InitializeInnerComponent() : m_pIMultiplication = %lu"), (long long)m_pIMultiplication);
    MessageBox(NULL, str, TEXT("Error"), MB_OK);

	hr = m_pIMultiplication->QueryInterface(IID_IDivision, (void**)&m_pIDivision);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IDivision interface cannot be obtained from inner component"), TEXT("Error"), MB_OK);
		return (E_FAIL);
	}

    MessageBox(NULL, TEXT("CSumSubtract::InitializeInnerComponent() end"), TEXT("Error"), MB_OK);
	return (S_OK);
}

// implementation of CSumSubtractClassFactory's constructor
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	m_cRef = 1; // hardcoded initialization to anticipate possible failure of QueryInterface()
}

// implementation of CSumSubtractClassFactory's destructor
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
	// no code
}

// implementation of CSumSubtract's ClassFactory's IUnknown's methods
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

// implementation of CSumSubtractClassFactory's IClassFactory's methods
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	// local variable declarations
	CSumSubtract* pCSumSubtract = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return (CLASS_E_NOAGGREGATION);

	pCSumSubtract = new CSumSubtract;
	if (pCSumSubtract == NULL)
		return (E_OUTOFMEMORY);

	hr = pCSumSubtract->InitializeInnerComponent();
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Failed to initialize inner component"), TEXT("Error"), MB_OK);
		return (E_FAIL);
	}

	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release(); // to anticipate possible failure of QueryInterface()

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

// implementation of exported functions from this dll
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	// local variable declarations
	CSumSubtractClassFactory* pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_SumSubtract)
		return (CLASS_E_CLASSNOTAVAILABLE);

	// create instance of class factory
	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	if (pCSumSubtractClassFactory == NULL)
		return (E_OUTOFMEMORY);

	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release(); // to anticipate possible failure of QueryInterface()

	return (S_OK);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return (S_OK);
	else
		return (S_FALSE);
}

