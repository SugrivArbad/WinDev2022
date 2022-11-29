// header Files
#include <windows.h>
#include "Window.h"
#include "ClassFactoryDllServerWithRegFile.h"

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// properties global function declarations
void __stdcall Identity(ISum*, ISubtract*);
void __stdcall Predictability(ISum*, ISubtract*);
void __stdcall Reflexivity(ISum*);
void __stdcall Symmetry(ISum*, ISubtract*);
void __stdcall Transitivity(ISum*, ISubtract*);

// global variable declarations
int n1, n2, sum, subtract;
TCHAR str[255];

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
	UpdateWindow(hwnd);

	// message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	// COM Uninitialization
	CoUninitialize();		// then DllCanUnloadNow(), CoFreeLibrary(), FreeLibrary(), Free()

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
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
		hr = CoCreateInstance(CLSID_SumSubtractMultiply, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
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
		
		// check properties
		Identity(pISum, pISubtract);
		Predictability(pISum, pISubtract);
		Reflexivity(pISum);
		Symmetry(pISum, pISubtract);
		Transitivity(pISum, pISubtract);

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

		DestroyWindow(hwnd);	// WM_DESTROY la jato
		break;

	case WM_DESTROY:
		PostQuitMessage(0);			// after this CoUnintialize()
		break;

	default:
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

// Property 1 : Identity
void __stdcall Identity(ISum* pISum, ISubtract* pISubtract)
{
	// local variable declarations
	IUnknown* pIUnknownFromISum = NULL;
	IUnknown* pIUnknownFromISubtract = NULL;

	// code
	pISum->QueryInterface(IID_IUnknown, (void**)&pIUnknownFromISum);
	pISubtract->QueryInterface(IID_IUnknown, (void**)&pIUnknownFromISubtract);

	if (pIUnknownFromISum == pIUnknownFromISubtract)
		MessageBox(NULL, TEXT("Identity proven : pISum->pISubtract & pISum->pIUnknownFromISum & pISubtract->pIUnknownFromISubtract & pIUnkownFromISum == pIUnknownFromISubtract"), TEXT("1] Identity Property:"), MB_OK);
	else
		MessageBox(NULL, TEXT("Identity NOT proven : pIUnkownFromISum != pIUnknownFromISubtract"), TEXT("1] Identity Property:"), MB_OK);

	// safe release
	if (pIUnknownFromISubtract)
	{
		pIUnknownFromISubtract->Release();
		pIUnknownFromISubtract = 0;
	}
	if (pIUnknownFromISum)
	{
		pIUnknownFromISum->Release();
		pIUnknownFromISum = 0;
	}
}

// Property 2 : Predictability
void __stdcall Predictability(ISum* pISum, ISubtract* pISubtract)
{
	// code
	n1 = 60;
	n2 = 40;

	if (pISum)
	{
		pISum->Release();
		pISum = NULL;
	}

	Sleep(3000);

	pISubtract->QueryInterface(IID_ISum, (void**)&pISum);
	pISum->SumOfTwoIntegers(n1, n2, &sum);
	wsprintf(str, TEXT("Predictability proven : pISum->pISubtract->delete(pISum) & Sleep(3000) & pISubtract->pISum : %d + %d = %d."), n1, n2, sum);
	if (pISum)
		MessageBox(NULL, str, TEXT("2] Predictability Property:"), MB_OK);
	else
		MessageBox(NULL, TEXT("Predictability NOT proven."), TEXT("2] Predictability Property:"), MB_OK);
}

// Property 3 : Reflexivity
void __stdcall Reflexivity(ISum* pISum)
{
	// local variable declarations
	ISum* pISumAgain = NULL;

	// code
	n1 = 610;
	n2 = 40;

	pISum->QueryInterface(IID_ISum, (void**)&pISumAgain);
	pISumAgain->SumOfTwoIntegers(n1, n2, &sum);
	wsprintf(str, TEXT("Reflexivity proven : pISum->pISumAgain & pISum == pISumAgain : %d + %d = %d."), n1, n2, sum);
	if (pISum == pISumAgain)
		MessageBox(NULL, str, TEXT("3] Reflexivity Property:"), MB_OK);
	else
		MessageBox(NULL, TEXT("Reflexivity NOT Proven."), TEXT("3] Reflexivity Property:"), MB_OK);

	// safe release
	if (pISumAgain)
	{
		pISumAgain->Release();
		pISumAgain = 0;
	}
}

// Property 4 : Symmetry
void __stdcall Symmetry(ISum* pISum, ISubtract* pISubtract)
{
	// local variable declarations
	ISum* pISumAgain = NULL;

	// code
	pISubtract->QueryInterface(IID_ISum, (void**)&pISumAgain);
	pISumAgain->SumOfTwoIntegers(n1, n2, &sum);
	wsprintf(str, TEXT("Symmetry proven : pISum->pISubtract->pISumAgain & pISum == pISumAgain : %d + %d = %d."), n1, n2, sum);
	if (pISum == pISumAgain)
		MessageBox(NULL, str, TEXT("4] Symmetry Property:"), MB_OK);
	else
		MessageBox(NULL, TEXT("Symmetry NOT Proven."), TEXT("4] Symmetry Property:"), MB_OK);

	// safe release
	if (pISumAgain)
	{
		pISumAgain->Release();
		pISumAgain = 0;
	}
}

// Property 5 : Transityvity
void __stdcall Transitivity(ISum* pISum, ISubtract* pISubtract)
{
	// local variable declarations
	IMultiply* pIMultiply = NULL;
	ISum* pISumAgain = NULL;
	int n3, n4, multiplication;

	// code
	n1 = n3 = 700;
	n2 = n4 = 200;

	pISubtract->QueryInterface(IID_IMultiply, (void**)&pIMultiply);
	pIMultiply->MultiplicationOfTwoIntegers(n3, n4, &multiplication);
	pIMultiply->QueryInterface(IID_ISum, (void**)&pISumAgain);
	pISumAgain->SumOfTwoIntegers(n1, n2, &sum);
	wsprintf(str, TEXT("Transitivity proven : pISum->pISubtract->pIMultiply->pISumAgain & pISum == pISumAgain : %d + %d = %d and %d * %d = %d."), n1, n2, sum, n3, n4, multiplication);
	if (pISum == pISumAgain)
		MessageBox(NULL, str, TEXT("5] Transitivity Property:"), MB_OK);
	else
		MessageBox(NULL, TEXT("Transitivity NOT Proven."), TEXT("5] Transitivity Property:"), MB_OK);

	// safe release
	if (pISumAgain)
	{
		pISumAgain->Release();
		pISumAgain = 0;
	}
	if (pIMultiply)
	{
		pIMultiply->Release();
		pIMultiply = 0;
	}
}

