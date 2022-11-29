#pragma once
#include "MyIUnknownIClassFactory.hpp"
#include <iostream>
#include <fstream>
#include <string>

// gloabal function declarations
HRESULT __stdcall MyCoGetClassObject(long, long, void**);

typedef HRESULT(*DLLGETCLASSOBJECTPROC)(long, long, void**);
typedef HRESULT(*DLLCANUNLOADNOW)(void);

HRESULT MyCoCreateInstance(long rclsid, IMyUnknown* pUnkOuter, long riid, void** ppv)
{
    IMyClassFactory* pIMyClassFactory = NULL;
    HRESULT hr;
    
    hr = MyCoGetClassObject(rclsid, IID_IMyClassFactory, (void**)&pIMyClassFactory);
    if (SUCCEEDED(hr))
    {
        pIMyClassFactory->CreateInstance(pUnkOuter, riid, ppv); // 235
        pIMyClassFactory->Release();
    }

    return (S_OK);
}

HRESULT MyCoGetClassObject(long rclsid, long riid, void** ppv)
{
    std::ifstream fin;
    std::string line;
    int index;
    std::string idstr = "";
    std::string dllPath = "";
    TCHAR str[255];

    fin.open("MyClassFactoryReg.txt", std::ios::in);

    // find rclsid
    getline(fin, line);

    index = 0;
    while (line[index] != '\"')
        index++;
    index++;
    while (line[index] != '\"')
        idstr += line[index++];
    
    long idlong = atol(idstr.c_str());

    // find dllPath
    getline(fin, line);

    index = 0;
    while (line[index++] != '\"');

    while (line[index] != '\"')
        dllPath += line[index++];

    fin.close();
    
    // loading dll manually
    HINSTANCE hDll = NULL;
    hDll = LoadLibrary(dllPath.c_str());

    DLLGETCLASSOBJECTPROC pDllGetClassObject = NULL;
    pDllGetClassObject = (DLLGETCLASSOBJECTPROC)GetProcAddress(hDll, TEXT("MyDllGetClassObject"));

    HRESULT hr = NULL;
    hr = pDllGetClassObject(rclsid, riid, ppv);

    return (hr);
}

