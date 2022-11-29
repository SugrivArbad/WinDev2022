// MyClassFactoryServer.h
// call convention -> __stdcall -> standard calling convention

#pragma once
#include "..\\..\\MyIUnknownIClassFactory.hpp"

class ISum : public IMyUnknown
{
public:
    virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubtract : public IMyUnknown
{
public:
    virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};


// CSLSID of coclass SumSubtract
const long CLSID_SumSubtract    = 1001;

// IID of Interface ISum
const long IID_ISum             = 1002;

// IID of Interface ISubtract
const long IID_ISubtract        = 1003;

