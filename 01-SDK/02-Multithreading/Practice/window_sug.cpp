// header files
#include <windows.h>
#include "window_sug.h"

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

// global variable declarations

// entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("WinDev");

	// code
	// WNDCLASSEX initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(SUG_ICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(SUG_ICON));

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
	HANDLE hThread1 = NULL;
	HANDLE hThread2 = NULL;

	// code
	switch (iMsg)
	{
	case WM_CREATE:
		hThread1 = CreateThread(
			NULL,
			0,
			(LPTHREAD_START_ROUTINE)ThreadProcOne,
			(LPVOID)hwnd,
			0,
			NULL);

		hThread2 = CreateThread(
			NULL,
			0,
			(LPTHREAD_START_ROUTINE)ThreadProcTwo,
			(LPVOID)hwnd,
			0,
			NULL);
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("This is my text"), TEXT("Message"), MB_OK);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD ThreadProcOne(LPVOID param)
{
	// local variable declarations
	HDC hdc;
	TCHAR str[255];
	long i;

	// code
	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 255, 0));
	for (i = 0; i < LONG_MAX; i++)
	{
		if (i == 10000)
			ExitThread(0);
		wsprintf(str, TEXT("Number in increamenting order: %d"), i);
		TextOut(hdc, 5, 5, str, wcslen(str));
	}
	ReleaseDC((HWND)param, hdc);

	return 0;
}

DWORD ThreadProcTwo(LPVOID param)
{
	// local variable declarations
	HDC hdc;
	TCHAR str[255];
	long i;

	// code
	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 255));
	for (i = LONG_MAX; i >= 0; i--)
	{
		wsprintf(str, TEXT("Number in decreamenting order: %d"), i);
		TextOut(hdc, 5, 20, str, lstrlen(str));
	}
	ReleaseDC((HWND)param, hdc);

	return 0;
}

