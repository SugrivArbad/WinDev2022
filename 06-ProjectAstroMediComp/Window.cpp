// header Files 
#pragma once
#include <Windows.h>
#include "Window.h"
#include "MyDialog.h"

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);

BOOL (CALLBACK *pMYDLGPROC)(HWND, UINT, WPARAM, LPARAM);

// global variable declarations
struct INPUT_T
{
    char name[50], address[50];
    int age, mstatus;
    float sal;
} in;

HINSTANCE glhInstance;

// entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("WINDEV");
    glhInstance = hInstance;

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
    HINSTANCE hInst;

	// code
	switch (iMsg)
	{
    case WM_CREATE:
        // hInst = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
        // call to Dialog Box
        DialogBox(glhInstance, "DATAENTRY", NULL, (DLGPROC) MyDlgProc);
        break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

// Dialog Box's procedure
BOOL CALLBACK MyDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    char salrs[6], salps[3];
    switch (iMsg)
    {
    case WM_INITDIALOG:
        // set focus in name Edit Box
        SetFocus(GetDlgItem(hDlg, ID_ETNAME));
        // keep married Radio Button checked
        SendDlgItemMessage(hDlg, ID_RBMARRIED, BM_SETCHECK, 1, 0);
        return (TRUE);

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_PBCONTINUE:
            EndDialog(hDlg, 0);
            break;
        case IDOK:
            // get the user-entered name
            GetDlgItemText(hDlg, ID_ETNAME, in.name, 50);
            // get the user-entered address
            GetDlgItemText(hDlg, ID_ETADDRESS, in.address, 50);
            // get the user-entered age
            //BOOL* pBOOL = NULL;
            in.age = GetDlgItemInt(hDlg, ID_ETAGE, NULL, TRUE);
            // get the user-entered salary
            GetDlgItemText(hDlg, ID_ETSALRS, salrs, 6);
            GetDlgItemText(hDlg, ID_ETSALPS, salps, 3);
            in.sal = atoi(salrs) + (float)atoi(salps)/100;
            // get the user-entered marrital status
            in.mstatus = SendDlgItemMessage(hDlg, ID_RBMARRIED, BM_GETCHECK, 0, 0);
            EndDialog(hDlg, 0);
            TCHAR str[255];
            wsprintf(str, " Name : %s\n Address : %s\n Age : %d\n Salary : %lf\n Marriage Status : %d\n", in.name, in.address, in.age, in.sal, in.mstatus);
            MessageBox(NULL, str, "Person Details", MB_OK);
            break;

        case IDCANCEL:
            EndDialog(hDlg, 0);
            break;
        }
        return (TRUE);
    }
    return (FALSE);
} // End of Dialog Procedure

/*
C:\Sugriv\WinDev2022\06-ProjectAstroMediComp>cl.exe Window.cpp /c /EHsc
Microsoft (R) C/C++ Optimizing Compiler Version 19.29.30146 for x64
Copyright (C) Microsoft Corporation.  All rights reserved.

Window.cpp

C:\Sugriv\WinDev2022\06-ProjectAstroMediComp>dir
 Volume in drive C has no label.
 Volume Serial Number is AACA-5058

 Directory of C:\Sugriv\WinDev2022\06-ProjectAstroMediComp

28-11-2022  21:40    <DIR>          .
28-11-2022  21:40    <DIR>          ..
28-11-2022  15:47               266 MyDialog.h
28-11-2022  21:33             1,038 MyDialog.rc
04-07-2022  22:25             3,870 MyIcon.ico
28-11-2022  19:43             3,947 Window.cpp
11-07-2022  23:54                22 Window.h
28-11-2022  21:40             4,669 Window.obj
12-07-2022  23:17                49 Window.rc
               7 File(s)         13,861 bytes
               2 Dir(s)  37,241,040,896 bytes free

C:\Sugriv\WinDev2022\06-ProjectAstroMediComp>rc.exe MyDialog.rc
Microsoft (R) Windows (R) Resource Compiler Version 10.0.10011.16384
Copyright (C) Microsoft Corporation.  All rights reserved.


C:\Sugriv\WinDev2022\06-ProjectAstroMediComp>dir
 Volume in drive C has no label.
 Volume Serial Number is AACA-5058

 Directory of C:\Sugriv\WinDev2022\06-ProjectAstroMediComp

28-11-2022  21:41    <DIR>          .
28-11-2022  21:41    <DIR>          ..
28-11-2022  15:47               266 MyDialog.h
28-11-2022  21:33             1,038 MyDialog.rc
28-11-2022  21:41               724 MyDialog.res
04-07-2022  22:25             3,870 MyIcon.ico
28-11-2022  19:43             3,947 Window.cpp
11-07-2022  23:54                22 Window.h
28-11-2022  21:40             4,669 Window.obj
12-07-2022  23:17                49 Window.rc
               8 File(s)         14,585 bytes
               2 Dir(s)  37,240,946,688 bytes free

C:\Sugriv\WinDev2022\06-ProjectAstroMediComp>rc.exe Window.rc
Microsoft (R) Windows (R) Resource Compiler Version 10.0.10011.16384
Copyright (C) Microsoft Corporation.  All rights reserved.


C:\Sugriv\WinDev2022\06-ProjectAstroMediComp>dir
 Volume in drive C has no label.
 Volume Serial Number is AACA-5058

 Directory of C:\Sugriv\WinDev2022\06-ProjectAstroMediComp

28-11-2022  21:41    <DIR>          .
28-11-2022  21:41    <DIR>          ..
28-11-2022  15:47               266 MyDialog.h
28-11-2022  21:33             1,038 MyDialog.rc
28-11-2022  21:41               724 MyDialog.res
04-07-2022  22:25             3,870 MyIcon.ico
28-11-2022  19:43             3,947 Window.cpp
11-07-2022  23:54                22 Window.h
28-11-2022  21:40             4,669 Window.obj
12-07-2022  23:17                49 Window.rc
28-11-2022  21:41             4,060 Window.res
               9 File(s)         18,645 bytes
               2 Dir(s)  37,240,811,520 bytes free

C:\Sugriv\WinDev2022\06-ProjectAstroMediComp>link.exe Window.obj Window.res MyDialog.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS
Microsoft (R) Incremental Linker Version 14.29.30146.0
Copyright (C) Microsoft Corporation.  All rights reserved.


C:\Sugriv\WinDev2022\06-ProjectAstroMediComp>dir
 Volume in drive C has no label.
 Volume Serial Number is AACA-5058

 Directory of C:\Sugriv\WinDev2022\06-ProjectAstroMediComp

28-11-2022  21:42    <DIR>          .
28-11-2022  21:42    <DIR>          ..
28-11-2022  15:47               266 MyDialog.h
28-11-2022  21:33             1,038 MyDialog.rc
28-11-2022  21:41               724 MyDialog.res
04-07-2022  22:25             3,870 MyIcon.ico
28-11-2022  19:43             3,947 Window.cpp
28-11-2022  21:42            99,840 Window.exe
11-07-2022  23:54                22 Window.h
28-11-2022  21:40             4,669 Window.obj
12-07-2022  23:17                49 Window.rc
28-11-2022  21:41             4,060 Window.res
              10 File(s)        118,485 bytes
               2 Dir(s)  37,240,631,296 bytes free

C:\Sugriv\WinDev2022\06-ProjectAstroMediComp>Window.exe
*/

