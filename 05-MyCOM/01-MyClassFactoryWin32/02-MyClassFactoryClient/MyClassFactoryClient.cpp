#pragma once
#include <Windows.h>
#include "..\\..\\MyCom.hpp"
#include "MyClassFactoryClient.h"
#include "MyClassFactoryServer.h"

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    WNDCLASSEX wndclass;
    TCHAR szAppName[] = TEXT("SVA_MY_WINDOW_APP_NAME");
    HWND hwnd;
    MSG msg;

    wndclass.cbSize = sizeof (WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;
    wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

    RegisterClassEx(&wndclass);

    hwnd = CreateWindow(
        szAppName,
        TEXT("SVA: My Window"), // display name
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL);

    ShowWindow(hwnd, nShowCmd);

    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    HRESULT hr;
    ISum* pISum = NULL;
    ISubtract* pISubtract = NULL;
    int iNum1, iNum2, iSum, iSubtract;
    TCHAR str[255];

    switch (iMsg)
    {
    case WM_CREATE:
        hr = MyCoCreateInstance(CLSID_SumSubtract, NULL, IID_ISum, (void**)&pISum);
        //HRESULT __stdcall MyCoCreateInstance(long, IMyUnknown*, long, void**);
        if (FAILED(hr))
        {
            MessageBox(NULL, TEXT("ISum cannot be obtained"), TEXT("ERROR"), MB_OK);
            DestroyWindow(hwnd);
        }
        
        iNum1 = 55;
        iNum2 = 45;
        pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);
        wsprintf(str, TEXT("%d + %d = %d"), iNum1, iNum2, iSum);
        MessageBox(NULL, str, TEXT("RESULT"), MB_OK);

        pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
        pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSubtract);
        wsprintf(str, TEXT("%d - %d = %d"), iNum1, iNum2, iSubtract);
        MessageBox(NULL, str, TEXT("RESULT"), MB_OK);

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

        //DestroyWindow(hwnd);

        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        break;
    }

    return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

