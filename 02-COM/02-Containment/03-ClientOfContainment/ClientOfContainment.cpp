#include <Windows.h>
#include <stdio.h>
#include "ClientOfContainment.h"
#include "ComboInnerOuter.h"

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ComErrorDescriptionString(HWND, HRESULT);

// global variable declarations
ISum* pISum = NULL;
ISubtract* pISubtract = NULL;
IMultiplication* pIMultiplication = NULL;
IDivision* pIDivision = NULL;

// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	// local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("ClientOfContainment");
	HRESULT hr;
	
	// COM initialization
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM library cannot be initialized.\nProgram will now exit."), TEXT("Error"), MB_OK);
		exit(0);
	}

	// WNDCLASSEX initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	// register window class
	RegisterClassEx(&wndclass);

	// create window
	hwnd = CreateWindow(szAppName,
		TEXT("Client of Containment DLL Server"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);

	UpdateWindow(hwnd);

	// message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// COM Uninitialization
	CoUninitialize();

	return ((int)msg.wParam);
}

// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// function declarations
	void SafeInterfaceRelease(void);

	// variable declarations
	HRESULT hr;
	int iNum1, iNum2, iSum, iSubtract, iMultiplication, iDivision;
	TCHAR str[255];

	// code
	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
        ComErrorDescriptionString(NULL, hr);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISum interface cannot be obtained."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		// initialize arguments hardcoded
		iNum1 = 65;
		iNum2 = 45;

		// call SumOfTwoIntegers() of ISum to get the sum
		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);

		// display the result
		wsprintf(str, TEXT("Sum of %d and %d is %d."), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		// call QueryInterface() on ISum, to get ISubtract's pointer
		hr = pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISubtract interface cannot be obtained."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		// as ISum is now not needed onwards, release it
		pISum->Release();
		pISum = NULL; // make released interface null

		// again initialize arguments hardcoded
		iNum1 = 155;
		iNum2 = 55;
		// call SubtractionOfTwoIntegers() of ISubtract to get the subtraction
		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSubtract);
		
		// display the result
		wsprintf(str, TEXT("Subtraction of %d and %d is %d."), iNum1, iNum2, iSubtract);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		// call QueryInterface() on ISubtract to get IMultiplication's pointer
        wsprintf(str, TEXT("pIMultiplication = %lu."), pIMultiplication);
		MessageBox(hwnd, str, TEXT("Error"), MB_OK);
		hr = pISubtract->QueryInterface(IID_IMultiplication, (void**)&pIMultiplication);
        ComErrorDescriptionString(hwnd, hr);
        wsprintf(str, TEXT("IMultiplication interface cannot be obtained. pIMultiplication = %lu."), pIMultiplication);
		if (FAILED(hr))
		{
			MessageBox(hwnd, str, TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		// as ISubtract now not needed, release it
		pISubtract->Release();
		pISubtract = NULL; // make released interface null

		// again initialize arguments hardcoded
		iNum1 = 30;
		iNum2 = 25;
		// call MultiplicationOfTwoIntegers() of IMultiplication to get multiplication
		pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, &iMultiplication);

		// display the result
		wsprintf(str, TEXT("Multiplication of %d and %d is %d."), iNum1, iNum2, iMultiplication); 
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		// call QueryInterface on IMultiplication to get IDivision's pointer
		hr = pIMultiplication->QueryInterface(IID_IDivision, (void**)&pIDivision);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IDivision interface cannot be obtained."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		// as IMultiplication now not needed onwards, release it
		pIMultiplication->Release();
		pIMultiplication = NULL; // make released interface null

		// again initialize arguments hardcoded
		iNum1 = 200;
		iNum2 = 25;

		// call DivisionOfTwoIntegers() on IDivision to get division
		pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iDivision);

		// display the result
		wsprintf(str, TEXT("Division of %d and %d is %d."), iNum1, iNum2, iDivision);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		// finally release IDivision
		pIDivision->Release();
		pIDivision = NULL; // make released pointer null


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

void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
    // variable declarations
    TCHAR* szErrorMessage = NULL;
    TCHAR str[255];

    if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
        hr = HRESULT_CODE(hr);

    // LPTSTR - Long Pointer Terminated STRing
    if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szErrorMessage, 0, NULL) != 0)
    {
        swprintf_s(str, TEXT("%#x : %s"), hr, szErrorMessage);
        LocalFree(szErrorMessage);
    }
    else
        swprintf_s(str, TEXT("[Could not find description for error # %#x.]\n"), hr);

    MessageBox(hwnd, str, TEXT("COM Error"), MB_OK);
}

