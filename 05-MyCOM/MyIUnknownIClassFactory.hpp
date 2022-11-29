
#ifndef MyIUnknownIClassFactory_HPP
#define MyIUnknownIClassFactory_HPP

class IMyUnknown
{
public:
    virtual HRESULT __stdcall QueryInterface(long, void**) = 0;
    virtual ULONG __stdcall AddRef(void) = 0;
    virtual ULONG __stdcall Release(void) = 0;
};

class IMyClassFactory : public IMyUnknown
{
public:
    virtual HRESULT __stdcall CreateInstance(IMyUnknown*, long, void**) = 0;
    virtual HRESULT __stdcall LockServer(BOOL) = 0;
};

// IID of IMyUnknown
const long IID_IMyUnknown       = 0;
// IID of IMyClassFactory
const long IID_IMyClassFactory  = 1;

#endif  // MyIUnknownIClassFactory_HPP

