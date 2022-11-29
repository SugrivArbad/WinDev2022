// this code represents binary encapsulation
// CSumSubtract and CSumSubtractClassFactory are hidden from client
#include <windows.h>
#include <cstdio>
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
	fopen("C:\\Sugriv\\WinDev2022\\02-COM\\01-ClassFactory\\02-ClientOfClassFactoryDllServerWithRegFile\\practice\\client\\ServerLogs.txt", "a");
	fprintf(fp, "Inside DllMain()\n");

	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		fprintf(fp, "DLL_PROCESS_ATTACH\n");
		break;

	case DLL_THREAD_ATTACH:
		fprintf(fp, "DLL_THREAD_ATTACH\n");
		break;

	case DLL_THREAD_DETACH:
		fprintf(fp, "DLL_THREAD_DETACH\n");
		break;

	case DLL_PROCESS_DETACH:
		fprintf(fp, "DLL_PROCESS_DETACH\n");
		break;

	default:
		fprintf(fp, "default\n");
		break;
	}

	return (TRUE);
}

// CSumSubtract implementation
// constructor
CSumSubtract::CSumSubtract(void)
{
	// code
	fprintf(fp, "CSumSubtract::CSumSubtract()\n");
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
	fprintf(fp, "CSumSubtract::CSumSubtract()\n");
}

CSumSubtract::~CSumSubtract(void)
{
	// code
	fprintf(fp, "CSumSubtract::~CSumSubtract()\n");
	InterlockedDecrement(&glNumberOfActiveComponents);
	fprintf(fp, "CSumSubtract::~CSumSubtract()\n");
}

HRESULT CSumSubtract::QueryInterface(REFIID riid, void** ppv)
{
	// code
	fprintf(fp, "CSumSubtract::QueryInterface()\n");
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract*>(this);
	else
	{
		*ppv = NULL;
		fprintf(fp, "CSumSubtract::QueryInterface()\n");
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv) -> AddRef();
	fprintf(fp, "CSumSubtract::QueryInterface()\n");
	return (S_OK);
}

ULONG CSumSubtract::AddRef()
{
	// code
	fprintf(fp, "CSumSubtract::AddRef()\n");
	InterlockedIncrement(&m_cRef);
	fprintf(fp, "CSumSubtract::AddRef()\n");
	return (m_cRef);
}

ULONG CSumSubtract::Release()
{
	// code
	fprintf(fp, "CSumSubtract::Release()\n");
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		fprintf(fp, "CSumSubtract::Release()\n");
		return (0);
	}
	fprintf(fp, "CSumSubtract::Release()\n");
	return (m_cRef);
}

// ISum method implementation
HRESULT CSumSubtract::SumOfTwoIntegers(int n1, int n2, int* pSum)
{
	// code
	fprintf(fp, "CSumSubtract::SumOfTwoIntegers()\n");
	*pSum = n1 + n2;
	fprintf(fp, "CSumSubtract::SumOfTwoIntegers()\n");
	return (S_OK);
}

// ISubtract method implementation
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int n1, int n2, int* pSubtract)
{
	// code
	fprintf(fp, "CSumSubtract::SubtractionOfTwoIntegers()\n");
	*pSubtract = n1 + n2;
	fprintf(fp, "CSumSubtract::SubtractionOfTwoIntegers()\n");
	return (S_OK);
}

// CSumSubtractClassFactory implementation
// constructor
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	// code
	fprintf(fp, "CSumSubtractClassFactory::CSumSubtractClassFactory()\n");
	m_cRef = 1;
	fprintf(fp, "CSumSubtractClassFactory::CSumSubtractClassFactory()\n");
}

// destructor
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
	// code
	fprintf(fp, "CSumSubtractClassFactory::~CSumSubtractClassFactory()\n");
	fprintf(fp, "CSumSubtractClassFactory::~CSumSubtractClassFactory()\n");
}

// IUnknown method implementation
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	// code
	fprintf(fp, "CSumSubtractClassFactory::QueryInterface()\n");
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory*>(this);
	else
	{
		*ppv = NULL;
		fprintf(fp, "CSumSubtractClassFactory::QueryInterface()\n");
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	fprintf(fp, "CSumSubtractClassFactory::QueryInterface()\n");
	return (S_OK);
}

ULONG CSumSubtractClassFactory::AddRef(void)
{
	// code
	fprintf(fp, "CSumSubtractClassFactory::AddRef()\n");
	InterlockedIncrement(&m_cRef);
	fprintf(fp, "CSumSubtractClassFactory::AddRef()\n");
	return (m_cRef);
}

ULONG CSumSubtractClassFactory::Release(void)
{
	// code
	fprintf(fp, "CSumSubtractClassFactory::Release()\n");
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete (this);
		fprintf(fp, "CSumSubtractClassFactory::Release()\n");
		return (0);
	}
	fprintf(fp, "CSumSubtractClassFactory::Release()\n");
	return (m_cRef);
}

// IClassFactory methods implementation
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown* pIUnkOuter, REFIID riid, void** ppv)
{
	// local variables declaration
	fprintf(fp, "CSumSubtractClassFactory::CreateInstance()\n");
	CSumSubtract* pCSumSubtract = NULL;
	HRESULT hr;

	// code
	if (pIUnkOuter != NULL)
	{
		fprintf(fp, "CSumSubtractClassFactory::CreateInstance()\n");
		return (CLASS_E_NOAGGREGATION);
	}
	pCSumSubtract = new CSumSubtract;
	if (pCSumSubtract == NULL)
	{
		fprintf(fp, "CSumSubtractClassFactory::CreateInstance()\n");
		return (E_OUTOFMEMORY);
	}
	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release();
	fprintf(fp, "CSumSubtractClassFactory::CreateInstance()\n");
	return (hr);
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	// code
	fprintf(fp, "CSumSubtractClassFactory::LockServer()\n");
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	fprintf(fp, "CSumSubtractClassFactory::LockServer()\n");
	return (S_OK);
}

// exportable COM DLL methods
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	// variable declarations
	fprintf(fp, "DllGetClassObject()\n");
	CSumSubtractClassFactory* pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	// code
	if (rclsid == CLSID_SumSubtract)
	{
		fprintf(fp, "DllGetClassObject()\n");
		return (CLASS_E_CLASSNOTAVAILABLE);
	}
	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	if (pCSumSubtractClassFactory == NULL)
	{
		fprintf(fp, "DllGetClassObject()\n");
		return (E_OUTOFMEMORY);
	}
	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();
	fprintf(fp, "DllGetClassObject()\n");
	return (hr);
}

extern "C" HRESULT DllCanUnloadNow(void)
{
	// code
	fprintf(fp, "DllCanUnloadNow()\n");
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
	{
		fprintf(fp, "DllCanUnloadNow()\n");
		return (S_OK);
	}
	else
	{
		fprintf(fp, "DllCanUnloadNow()\n");
		return (S_FALSE);
	}
}

