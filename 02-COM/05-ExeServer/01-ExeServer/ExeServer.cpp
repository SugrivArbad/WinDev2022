/*
/out C:\Sugriv\WINDEV~1\02-COM\05-EXE~1\01-EXE~1\PROXYS~1
C:\Sugriv\WINDEV~1\02-COM\05-EXE~1\01-EXE~1\PROXYS~1\ProxyStub.idl
*/

#define UNICODE

#include <windows.h>
#include <TlHelp32.h> // for process snapshot related apis and structures
#include "ExeServer.h"

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// class declarations
class CSumSubtract : public ISum, ISubtract
{
private:
	long m_cRef;
	
public:
	// constructor method declarations
	CSumSubtract(void);
	// destructor method declarations
	~CSumSubtract(void);

	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// ISum specific method declarations (inherited)
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

	// ISubtract specific method declarations (inherited)
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
};

class CSumSubtractClassFactory : public IClassFactory
{
private:
	long m_cRef;

public:
	// constructor method declarations
	CSumSubtractClassFactory(void);
	// destructor method delclarations
	~CSumSubtractClassFactory(void);

	// IUnknown specific method declarations
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

// global variable declarations
long glNumberOfActiveComponents = 0; // number of actibe components
long glNumberOfServerLocks = 0; // number of locks on this dll
IClassFactory* gpIClassFactory = NULL;
HWND ghwnd = NULL;
DWORD dwRegister;

// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// function declarations
	HRESULT StartMyClassFactories(void);
	void StopMyClassFactories(void);
	DWORD GetParentProcessID(void);

	// variable declarations
	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	HRESULT hr;
	int iDontShowWindow = 0; // 0 means show the window
	TCHAR AppName[] = TEXT("ExeServer");
	TCHAR szTokens[] = TEXT("-/");
	TCHAR* pszTokens;
	TCHAR lpszCmdLine[255];
	wchar_t* next_token = NULL;

	// com library initialization
	GetParentProcessID();

	hr = CoInitialize(NULL);

	if (FAILED(hr))
		return (0);

	MultiByteToWideChar(CP_ACP, 0, lpCmdLine, 255, lpszCmdLine, 255);

	pszTokens = wcstok_s(lpszCmdLine, szTokens, &next_token);

	while (pszTokens != NULL)
	{
		if (_wcsicmp(pszTokens, TEXT("Embedding")) == 0) // i.e. COM is calling me
		{
			iDontShowWindow = 1; // dont show window but message loop must
			break;
		}
		else
		{
			MessageBox(NULL, TEXT("Bad Command Line Arguments.\nExiting The Application."), TEXT("Error"), MB_OK);
			exit(0);
		}

		pszTokens = wcstok_s(NULL, szTokens, &next_token);
	}

	// window code
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register window class
	RegisterClassEx(&wndclass);

	// create window
	hwnd = CreateWindow(AppName,
		TEXT("Exe Server With Reg File"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	// initialize gloabal window handle
	ghwnd = hwnd;

	if (iDontShowWindow != 1) // true if server is not called by COM engine
	{
		ShowWindow(hwnd, nCmdShow);
		UpdateWindow(hwnd);

		// increament server lock
		++glNumberOfServerLocks;
	}

	if (iDontShowWindow == 1) // only when COM calls this program
	{
		// start class factory
		hr = StartMyClassFactories();

		if (FAILED(hr))
		{
			DestroyWindow(hwnd);
			exit(0);
		}
	}

	// message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (iDontShowWindow == 1) // only when COM calls this program
	{
		// stop class factory
		StopMyClassFactories();
	}

	// com library un-initialization
	CoUninitialize();

	return ((int)msg.wParam);
}

// window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// variable declarations
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;

	switch (iMsg)
	{
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		SetBkColor(hdc, RGB(0, 0, 0));
		SetTextColor(hdc, RGB(0, 255, 0));
		DrawText(hdc, TEXT("This Is A COM Exe Server Program. Not For You!!!"), -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
			PostQuitMessage(0);
		break;

	case WM_CLOSE:
		--glNumberOfServerLocks;
		ShowWindow(hwnd, SW_HIDE);
		// fall through, hence no break;
	default:
		return (DefWindowProc(hwnd, iMsg, wParam, lParam));
	}

	return (0L);
}

// Implementation of CSumSubtract's Constructor method
CSumSubtract::CSumSubtract(void)
{
	m_cRef = 1; // hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents); // increment global counter
}

// Implementation of CSumSubtract's Destructor Methods
CSumSubtract::~CSumSubtract(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents); // decrement global counter
}

// Implementation of CSumSubtract's IUnknown's Methods
HRESULT CSumSubtract::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract*>(this);
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
		delete (this); // delete before posting WM_QUIT messge
		if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
			PostMessage(ghwnd, WM_QUIT, (WPARAM)0, (LPARAM)0L);

		return (0);
	}
	return (m_cRef);
}

// Implementation of ISum's Methods
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int* pSum)
{
	*pSum = num1 - num2; // done deliberately to identify the server is built for shantanu
	return (S_OK);
}

// Implementation of ISubtract's Methods
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int* pSubtract)
{
	*pSubtract = num1 + num2; // done deliberately to identify the server is built for shantanu
	return (S_OK);
}

// Implementation of CSumSubtractClassFactory's Constructor Method
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	m_cRef = 1; // hardcoded intialization to anticipate possible failure of QueryInterface()
}

// Implemetation of CSumSubtractClassFactory's Destructor Method
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
	// no code
}

// Implementation of CSumSubtractClassFactory's IClassFactory's IUnknown's Methods
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	if (riid == IID_IClassFactory)
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

// Implemetation of CSumSubtractClassFactory's IClassFactory's Methods
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	// variable declarations
	CSumSubtract* pCSumSubtract = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return (CLASS_E_NOAGGREGATION);

	// create the instance of component i.e. of CSumSubtract class
	pCSumSubtract = new CSumSubtract;
	if (pCSumSubtract == NULL)
		return (E_OUTOFMEMORY);

	// get the requested interface
	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release(); // anticipate possible failure of QueryInterface()

	return (hr);
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);

	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
		PostMessage(ghwnd, WM_QUIT, (WPARAM)0, (LPARAM)0L);

	return (S_OK);
}

HRESULT StartMyClassFactories(void)
{
	// variable declarations
	HRESULT hr;

	gpIClassFactory = new CSumSubtractClassFactory;
	if (gpIClassFactory == NULL)
		return (E_OUTOFMEMORY);

	gpIClassFactory->AddRef();

	// register the class factory in COM's private database
	hr = CoRegisterClassObject(CLSID_SumSubtract, static_cast<IUnknown*>(gpIClassFactory), CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &dwRegister);

	/* CoRegisterClassObject registers the CLSID for the server in what is called the class table (a different table than the running object table.) When a server is registered in the class table, it allows the service control manager (SCM) to determine that it is not necessary to launch the class again, because the server is already running. Only if the server is not listed in the class table will the SCM check the registry for appropriate values and launch the server associated with the given CLSID. */

	if (FAILED(hr))
	{
		gpIClassFactory->Release();
		return (E_FAIL);
	}

	return (S_OK);
}

void StopMyClassFactories(void)
{
	// un-register the class factory
	if (dwRegister != 0)
		CoRevokeClassObject(dwRegister);

	/* CoRevokeClassObject revokes the class object (remove its registration) when all of the following are true:
		* There are no existing instances of the object definition.
		* There are no locks on the class object.
		* The application providing services to the class object is not under user control (not visible to the user on the display).
	*/

	if (gpIClassFactory != NULL)
		gpIClassFactory->Release();
}

DWORD GetParentProcessID(void)
{
	// variable declarations
	HANDLE hProcessSnapshot = NULL;
	BOOL bRetCode = FALSE;
	PROCESSENTRY32 ProcessEntry = { 0 };
	DWORD dwPPID;
	TCHAR szNameOfThisProcess[_MAX_PATH], szNameOfParentProcess[_MAX_PATH];
	TCHAR szTemp[_MAX_PATH], /*szTemp2[_MAX_PATH],*/ str[_MAX_PATH], * ptr = NULL;

	// first take current system snapshot
	hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnapshot == INVALID_HANDLE_VALUE)
		return (-1);

	ProcessEntry.dwSize = sizeof(PROCESSENTRY32);

	// walk process hierarchy
	if (Process32First(hProcessSnapshot, &ProcessEntry))
	{
		GetModuleFileName(NULL, szTemp, _MAX_PATH);
		ptr = wcsrchr(szTemp, '\\');
		wcscpy_s(szNameOfThisProcess, ptr + 1);
		
		do
		{
			errno_t err;

			err = _wcslwr_s(szNameOfThisProcess, wcslen(szNameOfThisProcess) + 1);
			err = _wcsupr_s(ProcessEntry.szExeFile, wcslen(ProcessEntry.szExeFile) + 1);

			if (wcsstr(szNameOfThisProcess, ProcessEntry.szExeFile) != NULL)
			{
				wsprintf(str, TEXT("Current Process Name = %s\nCurrent Process ID = %ld\nParent Process ID = %ld\nParent Process Name = %s"), szNameOfThisProcess, ProcessEntry.th32ProcessID, ProcessEntry.th32ParentProcessID, ProcessEntry.szExeFile);
				MessageBox(NULL, str, TEXT("Parent Info"), MB_OK | MB_TOPMOST);

				dwPPID = ProcessEntry.th32ParentProcessID;
			}
		} while (Process32Next(hProcessSnapshot, &ProcessEntry));
	}

	CloseHandle(hProcessSnapshot);
	return (dwPPID);
}

