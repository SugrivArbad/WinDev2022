#pragma once
#include "MyIUnknownIClassFactory.hpp"
#include <fstream>
#include <string>

// gloabal function declarations
HRESULT __stdcall MyCoGetClassObject(long, long, void**);

typedef HRESULT(*DLLGETCLASSOBJECTPROC)(long, long, void**);
typedef HRESULT(*DLLCANUNLOADNOW)(void);

HRESULT MyCoCreateInstance(long rclsid, IMyUnknown* pUnkOuter, long riid, void** ppv)
{
    MessageBox(NULL, TEXT("MyCoCreateInstance() start"), TEXT("RESULT"), MB_OK);
    IMyClassFactory* pIMyClassFactory = NULL;
    HRESULT hr;
    
    hr = MyCoGetClassObject(rclsid, IID_IMyClassFactory, (void**)&pIMyClassFactory);
    if (SUCCEEDED(hr))
    {
        pIMyClassFactory->CreateInstance(pUnkOuter, riid, ppv); // 235
        pIMyClassFactory->Release();
    }

    MessageBox(NULL, TEXT("MyCoCreateInstance() end"), TEXT("RESULT"), MB_OK);
    return (S_OK);
}

HRESULT MyCoGetClassObject(long rclsid, long riid, void** ppv)
{
    MessageBox(NULL, TEXT("MyCoGetClassObject() start"), TEXT("RESULT"), MB_OK);
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

    if (idlong == rclsid)
        MessageBox(NULL, TEXT("rclsid found"), TEXT("RESULT"), MB_OK);

    // find dllPath
    getline(fin, line);

    index = 0;
    while (line[index++] != '\"');

    while (line[index] != '\"')
        dllPath += line[index++];

    MessageBox(NULL, dllPath.c_str(), TEXT("RESULT"), MB_OK);

    fin.close();
    
    // loading dll manually
    HINSTANCE hDll = NULL;
    hDll = LoadLibrary(dllPath.c_str());

    wsprintf(str, TEXT("hDll = %#x : LoadLibrary() Succeeded"), hDll);
    MessageBox(NULL, str, TEXT("RESULT"), MB_OK);

    DLLGETCLASSOBJECTPROC pDllGetClassObject = NULL;
    pDllGetClassObject = (DLLGETCLASSOBJECTPROC)GetProcAddress(hDll, TEXT("MyDllGetClassObject"));

    wsprintf(str, TEXT("pDllGetClassObject = %x : GetProcAddress()"), pDllGetClassObject);
    MessageBox(NULL, str, TEXT("RESULT"), MB_OK);

    HRESULT hr = NULL;
    hr = pDllGetClassObject(rclsid, riid, ppv);
    if (SUCCEEDED(hr))
        MessageBox(NULL, TEXT("pDllGetClassObject() Succeeded"), TEXT("RESULT"), MB_OK);

    //MyDllGetClassObject(rclsid, riid, ppv);  // 260
    MessageBox(NULL, TEXT("MyCoGetClassObject() end"), TEXT("RESULT"), MB_OK);
    return (hr);
}

