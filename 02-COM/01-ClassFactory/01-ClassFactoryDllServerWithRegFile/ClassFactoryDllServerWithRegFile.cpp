// this code represents Binary Encapsulation
// CSumSubtractMultiply and CSumSubtractMultiplyClassFactory hidden from client
#include <windows.h>
#include "ClassFactoryDllServerWithRegFile.h"

// CoClass
// Com cha class kinva 
// Concrete class - means cannot be base class i.e. no virtual functions 
class CSumSubtractMultiply : public ISum, ISubtract, IMultiply
{
private:
	long m_cRef;

public:
	// constructor
	CSumSubtractMultiply(void);		// void for backward compatibility

	// destructor
	~CSumSubtractMultiply(void);

	// IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// ISum method
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

	// ISubtract method
	HRESULT __stdcall SubtractTwoIntegers(int, int, int*);

	// IMutiply method
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);
};

// class FactoryClass
class CSumSubtractMultiplyClassFactory : public IClassFactory
{
private:
	long m_cRef;

public:
	// constructor
	CSumSubtractMultiplyClassFactory(void);

	// destructor
	~CSumSubtractMultiplyClassFactory(void);

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

// CSumSubtractMultiply implementation
// constructor
CSumSubtractMultiply::CSumSubtractMultiply(void)
{
	// code
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

// destructor
CSumSubtractMultiply::~CSumSubtractMultiply(void)
{
	// code
	InterlockedDecrement(&glNumberOfActiveComponents);	//
}

// IUnknown Methods implementation
HRESULT CSumSubtractMultiply::QueryInterface(REFIID riid, void** ppv)
{
	// code
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract*>(this);
	else if (riid == IID_IMultiply)
		*ppv = static_cast<IMultiply*>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return (S_OK);
}

ULONG CSumSubtractMultiply::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubtractMultiply::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete (this);
		return (0);
	}
	return (m_cRef);
}

// ISum method implementation
HRESULT CSumSubtractMultiply::SumOfTwoIntegers(int num1, int num2, int* pSum)
{
	// code
	*pSum = num1 + num2;
	return (S_OK);
}

// ISubtract method implementation
HRESULT CSumSubtractMultiply::SubtractTwoIntegers(int num1, int num2, int* pSubtract)
{
	// code
	*pSubtract = num1 - num2;
	return (S_OK);
}

// IMultiply method implementation
HRESULT CSumSubtractMultiply::MultiplicationOfTwoIntegers(int num1, int num2, int* pMultiply)
{
	// code
	*pMultiply = num1 * num2;
	return (S_OK);
}

// CSumSubtractMultiplyClassFactory implementation
// condtructor
CSumSubtractMultiplyClassFactory::CSumSubtractMultiplyClassFactory(void)
{
	// code
	m_cRef = 1;
}

// destructor
CSumSubtractMultiplyClassFactory::~CSumSubtractMultiplyClassFactory(void)
{
	// code
}

// IUnknown methods implementation
HRESULT CSumSubtractMultiplyClassFactory::QueryInterface(REFIID riid, void** ppv)
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

ULONG CSumSubtractMultiplyClassFactory::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubtractMultiplyClassFactory::Release(void)
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
HRESULT CSumSubtractMultiplyClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	// variable declarations
	CSumSubtractMultiply* pCSumSubtractMultiply = NULL;
	HRESULT hr;

	// code
	if (pUnkOuter != NULL)
		return (CLASS_E_NOAGGREGATION);
	pCSumSubtractMultiply = new CSumSubtractMultiply;
	if (pCSumSubtractMultiply == NULL)
		return (E_OUTOFMEMORY);
	hr = pCSumSubtractMultiply->QueryInterface(riid, ppv);
	pCSumSubtractMultiply->Release();
	return (hr);
}

HRESULT CSumSubtractMultiplyClassFactory::LockServer(BOOL fLock)
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
	CSumSubtractMultiplyClassFactory* pCSumSubtractMultiplyClassFactory = NULL;
	HRESULT hr;
	if (rclsid != CLSID_SumSubtractMultiply)
		return (CLASS_E_CLASSNOTAVAILABLE);
	pCSumSubtractMultiplyClassFactory = new CSumSubtractMultiplyClassFactory;
	if (pCSumSubtractMultiplyClassFactory == NULL)
		return (E_OUTOFMEMORY);
	hr = pCSumSubtractMultiplyClassFactory->QueryInterface(riid,ppv);
	pCSumSubtractMultiplyClassFactory->Release();
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
