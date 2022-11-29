// header Files
#include <windows.h>
#include <stdio.h>
#include "Window.h"
#include "ClassFactoryDllServerWithRegFile.h"

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
	HRESULT hr;

	// COM Initialization - ole32.dll oleaut32.dll
	hr = CoInitialize(NULL);  // parameter LPVOID is reserved, hence NULL
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Intialization failed"), TEXT("ERROR"), MB_OK);
		exit(0);
	}

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
	UpdateWindow(hwnd);	// Paint()

	// message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	// COM Uninitialization
	CoUninitialize();		// then DllCanUnloadNow(), CoFreeLibrary(), FreeLibrary(), Free()

	return ((int)msg.wParam);	// wParam = 0 which is PostQuitMessage(0)
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// function declarations
	void ComErrorDescriptionString(HWND, HRESULT);

	// local variable declarations
	ISum* pISum = NULL;
	ISubtract* pISubtract = NULL;
	HRESULT hr;
	int n1, n2, sum, subtract;
	TCHAR str[255];

	// code
	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
		ComErrorDescriptionString(hwnd, hr);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISum cannot be obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		n1 = 55;
		n2 = 45;
		pISum->SumOfTwoIntegers(n1, n2, &sum);
		wsprintf(str, TEXT("Sum of %d and %d is %d"), n1, n2, sum);
		MessageBox(hwnd, str, TEXT("SUM"), MB_OK);

		pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
		pISubtract->SubtractTwoIntegers(n1, n2, &subtract);
		wsprintf(str, TEXT("Subtraction of %d and %d is %d"), n1, n2, subtract);
		MessageBox(hwnd, str, TEXT("SUBRACTION"), MB_OK);

		// safe release
		if (pISubtract)
		{
			pISubtract->Release();
			pISubtract = NULL;
		}
		if (pISum)
		{
			pISum->Release();
			pISum = NULL;
		}

		DestroyWindow(hwnd);	// WndProc() WM_DESTROY la jato
		break;

	case WM_DESTROY:
		PostQuitMessage(0);			// after this CoUnintialize(), 0 means WM_QUIT
		break;

	default:
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	// variable declarations
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
		swprintf_s(str, TEXT("[Could not find description for error # %#x.]\n"), hr);

	MessageBox(hwnd, str, TEXT("COM Error"), MB_OK);
}

