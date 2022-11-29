// call
hr = CoCreateInstance(CLSID_SumSubtract,					// 1
					  NULL,									// 2
					  CLSCTX_INPROC_SERVER,					// 3
					  IID_ISum,								// 4
					  (void**)&pISum);						// 5

// definition
HRESULT __stdcall CoCreateInstance(REFCLSID rclsid,			// 1 CLSID_SumSubtract
            					   LPUNKNOWN pUnkOuter,     // 2 NULL
								   DWORD dwClsContext,		// 3 CLSCTX_INPROC_SERVER
								   REFIID riid,				// 4 IID_ISum
								   void** ppv)				// 5 (void**)&pISum
{
	// variable declarations
	IClassFactory* pIClassFactory = NULL; // loc_1
	HRESULT hr;

	// code
	hr = CoGetClassObject(rclsid,		  // 1 CLSID_SumSubtract
		dwClsContext,					  // 3 CLSCTX_INPROC_SERVER
		NULL,							  // COM+ related
		IID_IClassFactory,				  // {00000001-0000-0000-C0000-000000000046}
		(void**)&pIClassFactory);		  // loc_1 NULL

	if (SUCCEDED(hr))
	{
		pIClassFactory->CreateInstance(pUnkOuter,	// 2 NULL - In Aggregation pIUnknownOuter i.e. IUnknown*
									   riid,		// 4 IID_ISum
									   ppv);		// 5 (void**)&pISum
		pIClassFactory->Release();
	}

	return (hr);
}

// MessageBox(NULL, TEXT("CMyMathClassFactory::CreateInstance() start"), TEXT("ERROR"), MB_OK | MB_TASKMODAL | MB_TOPMOST);

/*
	CLSCTX_INPROC_SERVER
	-->	1> this is dll server
		2> path is registered in the registry
		3> dll is present inside particular registered path - confirmation

	CoGetClassObject()
		`--> CoLoadLibrary()
				`--> LoadLibrary()
				 -->GetProcAddress()
		--> DllGetClassObject()
							   /`\
								|____pfn1()
									
								____pfn2()
								|
							   \./
							DllCanUnloadNow()
*/


/*
	typedef struct UUID
	{											   _
		DWORD Data1;		// 32 bits = 4 Bytes	|
		WORD Data2;			// 16 bits = 2 Bytes	|___ 128 bits
		WORD Data3;			// 16 bits = 2 Bytes	|	 or 16 Bytes
		Byte Data4[8];		// 64 bits = 8 Bytes   _|
	}												

	340,282,366,920,900,000,000,000,000,000,000,000,000 these many GUID we can create.
	If we create 1 Trillion GUID/sec, it will take 10,782,897,524,560,000,000 years to run out of unique GUID

	IUnknown GUID
	{ 00000000-0000-0000-C000-000000000046 }

	IClassFactory GUID
	{ 00000001-0000-0000-C000-000000000046 }

	IDispatch GUID
	{ 00020400-0000-0000-C000-000000000046 }

	Two ways to represent GUID							________ ____ ____ _ _  _ _ _ _ _ _
		1] Stringized GUID (used in registry entry) = { 00000001-0000-0000-C000-000000000046 } 
		2] Programatic GUID (used in program) = { 0x1,0x0,0x0,0xC0,0x0,0x0,0x0,0x0,0x0,0x0,0x46 }

	overhead members in size of class	// hidden datatypes
		1] this
		2] typeinfo
		3] vptr
*/




// LoadLibrary() Explicitly
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// local variable declarations
	HMODULE hDLL = NULL;
	typedef int (*MakeCubeFunctionPointer)(int);
	MakeCubeFunctionPointer pfnMakeCube = NULL;
	int iNum = 5;
	int iCube;
	TCHAR str[255];

	// code
	switch (iMsg)
	{
	case WM_CREATE:
		hDLL = LoadLibrary(TEXT("MyMathTwo.dll"));
		if (hDLL == NULL)
		{
			MessageBox(hwnd, TEXT("LoadLiabrary() failed"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		pfnMakeCube = (MakeCubeFunctionPointer)GetProcAddress(hDLL, "MakeCube"); //far proc returns
		if (pfnMakeCube == NULL)
		{
			MessageBox(hwnd, TEXT("GetProcAddress() failed"), TEXT("ERROR"), MB_OK);
			FreeLibrary(hDLL);
			DestroyWindow(hwnd);
		}
		iCube = pfnMakeCube(iNum);
		wsprintf(str, TEXT("Cube of %d is %d"), iNum, iCube);
		MessageBox(hwnd, str, TEXT("Cube"), MB_OK);
		FreeLibrary(hDLL);
		hDLL = NULL;
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}


// Com Error Description String
void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	// varible declarations
	TCHAR* szErrorMessage = NULL;
	TCHAR str[255];

	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);

	// LPTSTR - Long Pointer Terminated String
	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szErrorMessage, 0, NULL) != 0)
	{
		swprintf_s(str, TEXT("%#x : %s"), hr, szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
		swprintf_s(str, TEXT("[Could not find a description for error # %#x.]\n"), hr);

	MessageBox(hwnd, str, TEXT("COM Error"), MB_OK);
}


