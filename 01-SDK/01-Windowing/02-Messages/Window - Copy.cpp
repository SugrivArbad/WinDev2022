// header Files 
//#define ANSI       // for making it ANSI character recognition
#include <windows.h>

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

	// code
	// WNDCLASSEX initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;		// CS - Class Style
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);		//unsigned int 32bit  -> HGDIOBJ return value of GetStockObject  -> WHITE_BRUSH
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// registration of WNDCLASSEX
	RegisterClassEx(&wndclass);			// return value = ATOM  i.e. Unmutable unique string

	// creating the window
	hwnd = CreateWindow(
		szAppName,
		TEXT("SVA:Window"),			// TEXT macro converts ANSI string to UNICODE compatible string
		WS_OVERLAPPEDWINDOW,		// WS - Window Style, WS_OVERLAPPEDWINDOW = 6 styles
		CW_USEDEFAULT,				// x - top left, CW - Create Window
		CW_USEDEFAULT,				// y - top left
		CW_USEDEFAULT,				// w - Width
		CW_USEDEFAULT,				// h - Height
		NULL,						// Handle of Parent Window of my Window
									// here it considers Desktop Window even it is NULL Or it can write HWND_DESKTOP
		NULL,						// Menu Handle 
		hInstance,
		NULL);						// LPVOID - if want ro give extra parameter

	// show the window
	ShowWindow(hwnd, iCmdShow); //SW_MAXIMIZE instead of iCmdShow

	// update the window
	UpdateWindow(hwnd);			// Window paint karanyasathi

	// message loop
	while (GetMessage(&msg, NULL, 0, 0))		//msg have 6 params out of 6, 4 members are similar to WndProc()
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// local variable declarations
	TCHAR str[255];

	// code
	switch (iMsg)
	{
	case WM_CREATE:			//WM - Window Message
		wsprintf(str, TEXT("WM_CREATE meassge is received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;
	case WM_KEYDOWN:
		wsprintf(str, TEXT("WM_KEYDOWN meassge is received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;
	case WM_LBUTTONDOWN:
		wsprintf(str, TEXT("WM_LBUTTONDOWN meassge is received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;
	case WM_RBUTTONDOWN:
		wsprintf(str, TEXT("WM_RBUTTONDOWN meassge is received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;
	case WM_DESTROY:
		wsprintf(str, TEXT("WM_DESTROY meassge is received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

