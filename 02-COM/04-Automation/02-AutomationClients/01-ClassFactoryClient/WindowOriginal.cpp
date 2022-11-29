// header Files 
#include <windows.h>
#include "AutomationServer.h"
#include "Window.h"

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
	IMyMath* pIMyMath = NULL;
	HRESULT hr;
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

		hr = CoCreateInstance(CLSID_MyMath, NULL, CLSCTX_INPROC_SERVER, IID_IMyMath, (void**)pIMyMath);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("CoCreateInstance failed to get IMyMath"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}

		num1 = 175;
		num2 = 125;

		pIMyMath->SumOfTwoIntegers(num1, num2, &sum);
		wsprintf(str, TEXT("Sum of %d and %d is %d."), num1, num2, sum);
		MessageBox(hwnd, str, TEXT("Sum"), MB_OK);

		pIMyMath->SubtractionOfTwoIntegers(num1, num2, &subtract);
		wsprintf(str, TEXT("Subtraction of %d and %d is %d."), num1, num2, subtract);
		MessageBox(hwnd, str, TEXT("Subtraction"), MB_OK);

		pIMyMath->Release();
		pIMyMath = NULL;

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
