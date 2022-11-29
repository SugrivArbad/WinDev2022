#include <windows.h>
#include "ComboInnerOuter.h"

// global fuction declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// global variable declarations
ISum* pISum = NULL;
ISubtract* pISubtract = NULL;
IMultiplication* pIMultiplication = NULL;
IDivision* pIDivision = NULL;

// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	// variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("COM Client");
	HRESULT hr;

	// COM Initialization
	hr = CoInitialize(NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Library Cannot Be Initialized.\nProgram Will Now Exit."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	// WNDCLASSEX Initialization
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register window class
	RegisterClassEx(&wndclass);

	// create window
	hwnd = CreateWindow(szAppName,
		TEXT("Client of Dll Server"),
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

		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISum Interface Cannot Be Obtained."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		// Initialize arguments hardcoded
		iNum1 = 65;
		iNum2 = 45;

		// call SumOfTwoIntegers() of ISum to get the sum
		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);

		// display the result
		wsprintf(str, TEXT("Sum of %d and %d is %d."), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		// call QueryInterface() on ISum to ger ISubtract's pointer
		hr = pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);

		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISubtract Interface Cannot Be Obtained."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		// as ISum is now not needed onwards, release it
		if (pISum)
		{
			pISum->Release();
			pISum = 0; // make released interface NULL
		}
		
		// again initialize arguments hardcoded
		iNum1 = 155;
		iNum2 = 55;
		
		// call SubtractioOfTwoIntegers() of ISubtract to the subtraction
		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSubtract);
		
		//display the result
		wsprintf(str, TEXT("Subtraction of %d and %d is %d."), iNum1, iNum2, iSubtract);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		// call QueryInterface() on ISubtract to get IMultiplication's pointer
		hr = pISubtract->QueryInterface(IID_IMultiplication, (void**)&pIMultiplication);

		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IMultiplication Interface Cannot Be Obtained."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		// as ISubtract is not needed now onwards, release it
		pISubtract->Release();
		pISubtract = NULL; // make released interface NULL

		// again initialize arguments hardcoded
		iNum1 = 30;
		iNum2 = 25;

		// call MultiplicationOfTwoIntegers() of IMultiplication to get Multiplication
		pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, &iMultiplication);

		// display the result
		wsprintf(str, TEXT("Multiplication of %d and %d is %d."), iNum1, iNum2, iMultiplication);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		// call QueryInterface() on IMultiplication to get IDivison's pointer
		hr = pIMultiplication->QueryInterface(IID_IDivision, (void**)&pIDivision);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IDivision Interface Cannot Be Obtained."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		// as IMultiplication is not needed now onwards, release it
		if (pIMultiplication)
		{
			pIMultiplication->Release();
			pIMultiplication = NULL; // make released interface NULL
		}

		// again initialize arguments hardcoded
		iNum1 = 200;
		iNum2 = 25;

		// call DivisionOfTwoIntegers of IDivision to get the Division
		pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iDivision);

		// display the result
		wsprintf(str, TEXT("Division of %d and %d is %d."), iNum1, iNum2, iDivision);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		// finally release IDivision
		if (pIDivision)
		{
			pIDivision->Release();
			pIDivision = NULL; // make released interface NULL
		}

		// exit the application
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		SafeInterfaceRelease();
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void SafeInterfaceRelease(void)
{
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
	
	if (pIMultiplication)
	{
		pIMultiplication->Release();
		pIMultiplication = 0;
	}
	
	if (pIDivision)
	{
		pIDivision->Release();
		pIDivision = 0;
	}
}

