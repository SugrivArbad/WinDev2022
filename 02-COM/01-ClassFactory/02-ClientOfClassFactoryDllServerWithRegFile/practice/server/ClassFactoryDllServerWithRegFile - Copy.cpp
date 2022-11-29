// this code represents binary encapsulation
// CSumSubtract and CSumSubtractClassFactory are hidden from client
#include <windows.h>
#include "ClassFactoryDllServerWithRegFile.h"

// CoClass means COM cha class kinva Concrete class
// Concrete class cannot be base class i.e. no virtual functions

class CSumSubtract : public ISum, ISubtract
{
private:
	long m_cRef;

public:
	// constructor
	CSumSubtract(void);

	// destructor
	~CSumSubtract(void);

	// IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// ISum method
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

	// ISubtract method
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
};

// class FactoryClass
class CSumSubtractClassFactory : public IClassFactory
{
private:
	long m_cRef;

public:
	// constructor
	CSumSubtractClassFactory(void);

	// destructor
	~CSumSubtractClassFactory(void);

	// IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory methods
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

// global variables
long glNumberOfActiveComponents;
long glNumberOfServerLocks;
FILE *fp;
char buffer[255];

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	// code
	fopen("log.txt", "w");
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

// CSumSubtract implementation
// constructor
CSumSubtract::CSumSubtract(void)
{
	// code
	fprintf(fp, "CSumSubtract::CSumSubtract(void)\n");
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
	fprintf(fp, "CSumSubtract::CSumSubtract(void)\n");
}

CSumSubtract::~CSumSubtract(void)
{
	// code
	fprintf(fp, "CSumSubtract::~CSumSubtract(void)\n");
	InterlockedDecrement(&glNumberOfActiveComponents);
	fprintf(fp, "CSumSubtract::~CSumSubtract(void)\n");
}

HRESULT CSumSubtract::QueryInterface(REFIID riid, void** ppv)
{
	// code
	fprintf(fp, "CSumSubtract::QueryInterface(REFIID riid, void** ppv)\n");
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract*>(this);
	else
	{
		*ppv = NULL;
		fprintf(fp, "CSumSubtract::QueryInterface(REFIID riid, void** ppv)\n");
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv) -> AddRef();
	fprintf(fp, "CSumSubtract::QueryInterface(REFIID riid, void** ppv)\n");
	return (S_OK);
}

ULONG CSumSubtract::AddRef()
{
	// code
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubtract::Release()
{
	// code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return (0);
	}
	return (m_cRef);
}

// ISum method implementation
HRESULT CSumSubtract::SumOfTwoIntegers(int n1, int n2, int* pSum)
{
	// code
	*pSum = n1 + n2;
	return (S_OK);
}

// ISubtract method implementation
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int n1, int n2, int* pSubtract)
{
	// code
	*pSubtract = n1 + n2;
	return (S_OK);
}

// CSumSubtractClassFactory implementation
// constructor
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	// code
	m_cRef = 1;
}

// destructor
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
	// code
}

// IUnknown method implementation
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void** ppv)
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

ULONG CSumSubtractClassFactory::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubtractClassFactory::Release(void)
{
	// code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete (this);
		return (0);
	}
	return (m_cRef);
}

// IClassFactory methods implementation
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown* pIUnkOuter, REFIID riid, void** ppv)
{
	// local variables declaration
	CSumSubtract* pCSumSubtract = NULL;
	HRESULT hr;

	// code
	if (pIUnkOuter != NULL)
		return (CLASS_E_NOAGGREGATION);
	pCSumSubtract = new CSumSubtract;
	if (pCSumSubtract == NULL)
		return (E_OUTOFMEMORY);
	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release();
	return (hr);
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
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
	CSumSubtractClassFactory* pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	// code
	if (rclsid == CLSID_SumSubtract)
		return (CLASS_E_CLASSNOTAVAILABLE);
	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	if (pCSumSubtractClassFactory == NULL)
		return (E_OUTOFMEMORY);
	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();
	return (hr);
}

extern "C" HRESULT DllCanUnloadNow(void)
{
	// code
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
		return (S_OK);
	else
		return (S_FALSE);
}

