// header Files 
#include <windows.h>
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