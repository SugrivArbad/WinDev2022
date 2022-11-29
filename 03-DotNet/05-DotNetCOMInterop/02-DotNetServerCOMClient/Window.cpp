// header Files 
#include <windows.h>
#include "Window.h"

// typelib specification
// no_namespace --> COM to .Net "mla tuzya namespace nkot"
// named_guids --> address guids by its name
// raw_interfaces_only --> IUnknown madhun aalele interfaces
#import "DotNetServer.tlb" no_namespace named_guids raw_interfaces_only

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// global variable declarations

// entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("WINDEV");

	//WNDCLASSEX - WNDCLASS EXTRA - from 10 members to 12 members
	// code
	// WNDCLASSEX initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	// registration of WNDCLASSEX
	RegisterClassEx(&wndclass);

	// creating the window
	hwnd = CreateWindow(
		szAppName,
		TEXT("SVA:Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	// show the window
	ShowWindow(hwnd, iCmdShow);

	// update the window
	UpdateWindow(hwnd);

	// message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// local variable declarations
	IDispatch* pIDispatch = NULL;
	HRESULT hr;
	// OLECHAR* also known as BSTR - binary/basic string 
	OLECHAR* szFunctionName1 = L"SumOfTwoIntegers";	// L - Literal - OLE character compatible literal
	OLECHAR* szFunctionName2 = L"SubtractionTwoIntegers";	// L - Literal - OLE character compatible literal
	VARIANT vArg[2];
	VARIANT vResult;
	DISPID dispid;
	DISPPARAMS params;
	int num1, num2, sum, subtract;
	TCHAR str[255];

	// code
	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoInitialize(NULL);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("CoInitialize failed"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}

		hr = CoCreateInstance(CLSID_DotNetServer, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void**)&pIDispatch);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("CoCreateInstance failed to get IDispatch"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}

		num1 = 275;
		num2 = 225;

		// get ID of SumOfTwoIntegers()
		hr = pIDispatch->GetIDsOfNames(IID_NULL,
			&szFunctionName1,
			1, // count of elements in second parameters
			GetUserDefaultLCID(), // user default Locale ID
			&dispid);

		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("GetIDsOfNames failed to get SumOfTwoIntegers"), TEXT("ERROR"), MB_OK);
			pIDispatch = NULL;
			DestroyWindow(hwnd);
		}

		// call SumOfTwoIntegers by passing its to invoke()
		VariantInit(vArg); // param -> vArg
		vArg[0].vt = VT_INT; // variant type
		vArg[0].intVal = num2;
		vArg[1].vt = VT_INT;
		vArg[1].intVal = num1;

		VariantInit(&vResult); // vResult

		params.rgvarg = vArg; // registered variant args 
		params.cArgs = 2; // no of members in vArg
		params.rgdispidNamedArgs = NULL; // scripting languages madhe NamedArgs astat
		params.cNamedArgs = 0; // count of NamedArgs

		hr = pIDispatch->Invoke(dispid,
			IID_NULL,
			GetUserDefaultLCID(),
			DISPATCH_METHOD, // method class, property get, property put, property ref
			&params, // params = above 9 lines
			&vResult,
			NULL,
			NULL);

		sum = vResult.lVal;

		wsprintf(str, TEXT("Sum of %d and %d is %d."), num1, num2, sum);
		MessageBox(hwnd, str, TEXT("Sum"), MB_OK);

		// get ID of SubtractionOfTwoIntegers()
		hr = pIDispatch->GetIDsOfNames(IID_NULL,
			&szFunctionName2,
			1, // count of elements in second parameters
			GetUserDefaultLCID(), // user default Locale ID
			&dispid);

		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("GetIDsOfNames failed to get SubtractionOfTwoIntegers"), TEXT("ERROR"), MB_OK);
			pIDispatch = NULL;
			DestroyWindow(hwnd);
		}

		// call SubtractionOfTwoIntegers by passing its to invoke()
		VariantInit(vArg); // param -> vArg
		vArg[0].vt = VT_INT; // variant type
		vArg[0].intVal = num2;
		vArg[1].vt = VT_INT;
		vArg[1].intVal = num1;

		VariantInit(&vResult); // vResult

		params.rgvarg = vArg; // registered variant args 
		params.cArgs = 2; // no of members in vArg
		params.rgdispidNamedArgs = NULL; // scripting languages madhe NamedArgs astat
		params.cNamedArgs = 0; // count of NamedArgs

		hr = pIDispatch->Invoke(dispid,
			IID_NULL,
			GetUserDefaultLCID(),
			DISPATCH_METHOD, // method class, property get, property put, property ref
			&params, // params = above 9 lines
			&vResult,
			NULL,
			NULL);

		subtract = vResult.lVal;

		wsprintf(str, TEXT("Subtraction of %d and %d is %d."), num1, num2, subtract);
		MessageBox(hwnd, str, TEXT("Subtraction"), MB_OK);

		VariantClear(&vResult);
		VariantClear(vArg);

		pIDispatch->Release();
		pIDispatch = NULL;

		DestroyWindow(hwnd);

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		CoUninitialize();
		break;

	default:
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

