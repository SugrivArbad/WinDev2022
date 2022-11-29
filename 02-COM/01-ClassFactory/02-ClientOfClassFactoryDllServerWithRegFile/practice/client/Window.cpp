// header files
#include <windows.h>
#include "Window.h"
#include "ClassFactoryDllServerWithRegFile.h"
#include <stdio.h>

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// global variable declarations
FILE* fp1;

// entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	fopen("C:\\Sugriv\\WinDev2022\\02-COM\\01-ClassFactory\\02-ClientOfClassFactoryDllServerWithRegFile\\practice\\client\\ClientLogs.txt", "a");
	fprintf(fp1, "Inside WinMain()\n");
	// local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("WINDEV");
	HRESULT hr;

	fprintf(fp1, "Before CoInitialize()\n");
	MessageBox(NULL, TEXT("WMCREATE"), TEXT("MESSAGE"), MB_OK);
	// COM Initialization - ole32.dll and oleaut32.dll
	hr = CoInitialize(NULL);	// parameter LPVOID is reserved, hence NULL
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Initialization Failed"), TEXT("ERROR"), MB_OK);
		exit(0);
	}
	fprintf(fp1, "After CoInitialize()\n");

	// WNDCLASSEX - WNDCLASS EXTRA - from 10 members to 12 members
	// code
	// WNDCLASSEX Initialization
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
	fprintf(fp1, "Before CreateWindow()\n");
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
	fprintf(fp1, "After CreateWindow()\n");

	// show the window
	fprintf(fp1, "Before ShowWindow()\n");
	ShowWindow(hwnd, iCmdShow);
	fprintf(fp1, "After ShowWindow()\n");

	// update window
	fprintf(fp1, "Before UpdateWindow()\n");
	UpdateWindow(hwnd);
	fprintf(fp1, "After UpdateWindow()\n");

	// message loop
	fprintf(fp1, "Before GetMessage()\n");
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		fprintf(fp1, "Inside GetMessage() Message loop\n");
	}
	fprintf(fp1, "After GetMessage()\n");

	// COM Uninitialization
	fprintf(fp1, "Before CoUninitialize()\n");
	CoUninitialize();	// then DllCanUnloadNow(), CoFreeLibrary(), FreeLibrary(), Free()
	fprintf(fp1, "After CoUninitialize()\n");

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	fprintf(fp1, "Start WndProc()\n");
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
		MessageBox(NULL, TEXT("WMCREATE"), TEXT("MESSAGE"), MB_OK);
		fprintf(fp1, "WM_CREATE\n");
		fprintf(fp1, "Before CoCreateInstance()\n");
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)pISum);
		fprintf(fp1, "After CoCreateInstance()\n");
		if (FAILED(hr))
		{
			fprintf(fp1, "Failed CoCreateInstance()\n");
			MessageBox(hwnd, TEXT("ISum cannot be obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		n1 = 55;
		n2 = 45;
		fprintf(fp1, "Before SumOfTwoIntegers()\n");
		pISum->SumOfTwoIntegers(n1, n2, &sum);
		fprintf(fp1, "After SumOfTwoIntegers()\n");
		wsprintf(str, TEXT("Sum of %d and %d is %d."), n1, n2, sum);
		MessageBox(hwnd, str, TEXT("SUM"), MB_OK);

		pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
		pISubtract->SubtractionOfTwoIntegers(n1, n2, &subtract);
		wsprintf(str, TEXT("Subtraction of %d and %d is %d."), n1, n2, subtract);
		MessageBox(hwnd, str, TEXT("ERROR"), MB_OK);

		// safe release
		if (pISum)
		{
			pISum->Release();
			pISum = 0;
		}
		if (pISubtract)
		{
			pISubtract->Release();
			pISubtract = 0;
		}

		DestroyWindow(hwnd);	// WM_DESTROY la jato
		break;

	case WM_DESTROY:
		fprintf(fp1, "WM_DESTROY\n");
		PostQuitMessage(0);		// after this CoUninitialize()
		break;

	default:
		break;
	}

	fprintf(fp1, "End WndProc()\n");
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

