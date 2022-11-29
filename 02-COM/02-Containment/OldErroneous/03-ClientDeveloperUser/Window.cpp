// header Files
#include <windows.h>
#include "Window.h"
#include "ComboInnerOuter.h"
#include <iostream>
#include <fstream>

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// global variable declarations
ISum* pISum = NULL;
ISubtract* pISubtract = NULL;
IMultiplication* pIMultiplication = NULL;
IDivision* pIDivision = NULL;
std::ofstream fout;

// entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	fout.open("C:\\Sugriv\\WinDev2022\\02-COM\\02-Containment\\03-ClientDeveloperUser\\ClientLogs.txt", std::ios::out);
	fout << "Client: Start WinMain()" << std::endl;
	// local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("ContainmentClient");
	HRESULT hr;

	// COM Initialization - ole32.dll oleaut32.dll
	hr = CoInitialize(NULL);  // parameter LPVOID is reserved, hence NULL
	fout << "Clinet: after CoInitialize()" << std::endl;
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Library Cannot Be Initialized.\nProgram Will Now Exit."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	//WNDCLASSEX - WNDCLASS EXTRA - from 10 members to 12 members
	// code
	// WNDCLASSEX initialization
	wndclass.cbSize = sizeof(wndclass);
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
		TEXT("Client of COM Dll Server"),
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

	fout << "Client: Before MessageLoop" << std::endl;
	// message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	// COM Uninitialization
	fout << "Client: before CoUninitialize() end" << std::endl;
	CoUninitialize();		// then DllCanUnloadNow(), CoFreeLibrary(), FreeLibrary(), Free()

	fout << "Client: End WinMain()" << std::endl;
	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	fout << "Client: Start WndProc() hwnd: " << hwnd << ", iMsg: " << iMsg << ", wParam: " << wParam << ", lParam: " << lParam << std::endl;

	// function declarations
	void SafeInterfaceRelease(void);

	// local variable declarations
	HRESULT hr;
	int n1, n2, iSum, iSubtract, iMultiplication, iDivision;
	TCHAR str[255];

	// code
	switch (iMsg)
	{
	case WM_CREATE:
		fout << "Client: Before CoCreateInstance()" << std::endl;
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
		fout << "Client: After CoCreateInstance()" << std::endl;
		fout << "Client: CLSID_SumSubtract: , IID_ISum:" << std::endl;
		if (FAILED(hr))
		{
			fout << "Client: ISum interface Cannot Be Obtained." << std::endl;
			MessageBox(hwnd, TEXT("ISum Interface Cannot Be Obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}

		// initialize arguments hardcoded
		n1 = 55;
		n2 = 45;
		pISum->SumOfTwoIntegers(n1, n2, &iSum);
		wsprintf(str, TEXT("Sum of %d and %d is %d"), n1, n2, iSum);
		MessageBox(hwnd, str, TEXT("SUM"), MB_OK);

		// call QueryInterface() on ISum, to get ISubtract's pointer
		hr = pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
		if (FAILED(hr))
		{
			fout << "Client: ISubtract interface Cannot Be Obtained." << std::endl;
			MessageBox(hwnd, TEXT("ISubtract Interface Cannot Be Obtained."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		// as ISum is now not needed onwards, release it
		pISum->Release();
		pISum = NULL; // make released interface NULL

		// again intialize arguments hardcoded
		n1 = 155;
		n2 = 55;

		// call SubtractionOfTwoIntegers() of ISubtract to get the subtraction
		pISubtract->SubtractionOfTwoIntegers(n1, n2, &iSubtract);

		// display the result
		wsprintf(str, TEXT("Subtraction of %d and %d is %d"), n1, n2, iSubtract);
		MessageBox(hwnd, str, TEXT("SUBRACTION"), MB_OK);

		// call QueryInterface() on ISubtract, to get IMultiplication's pointer
		hr = pISubtract->QueryInterface(IID_IMultiplication, (void**)&pIMultiplication);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IMultiplication Interface Cannot Be Obtained."), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}

		// as ISubtract is now not needed onwards, release it
		pISubtract->Release();
		pISubtract = NULL; // make released interface NULL

		// again initialize arguments hardcoded
		n1 = 30;
		n2 = 25;

		// call MultiplicationOfTwoIntegers() of IMultiplication to get the Multiplication
		pIMultiplication->MultiplicationOfTwoIntegers(n1, n2, &iMultiplication);

		// display the result
		wsprintf(str, TEXT("Multiplication of %d and %d is %d."), n1, n2, iMultiplication);
		MessageBox(hwnd, str, TEXT("MULTIPLICATION"), MB_OK);

		// call QueryInterface() on IMultiplication to get IDivision's pointer
		hr = pIMultiplication->QueryInterface(IID_IDivision, (void**)&pIDivision);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IDivision Interface Cannot Be Obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}

		// as IMultiplication is now not needed onwards, release it
		pIMultiplication->Release();
		pIMultiplication = NULL; // make released interface NULL

		// again initialize arguments hardcoded
		n1 = 200;
		n2 = 25;

		// call DivisionOfTwoIntegers() of IDivision to get the Division
		pIDivision->DivisionOfTwoIntegers(n1, n2, &iDivision);

		// display the result
		wsprintf(str, TEXT("Division of %d and %d is %d"), n1, n2, iDivision);
		MessageBox(hwnd, str, TEXT("DIVISION"), MB_OK);

		// finally release IDivision
		pIDivision->Release();
		pIDivision = NULL; // make released interface NULL;

		// exit the application
		DestroyWindow(hwnd);

		break;

	case WM_DESTROY:
		SafeInterfaceRelease();
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void SafeInterfaceRelease(void)
{
	if (pISum)
	{
		pISum->Release();
		pISum = NULL;
	}

	if (pISubtract)
	{
		pISubtract->Release();
		pISubtract = NULL;
	}

	if (pIMultiplication)
	{
		pIMultiplication->Release();
		pIMultiplication = NULL;
	}

	if (pIDivision)
	{
		pIDivision->Release();
		pIDivision = NULL;
	}
}

