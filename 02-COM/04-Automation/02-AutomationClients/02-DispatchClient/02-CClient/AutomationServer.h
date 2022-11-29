#pragma once

#undef INTERFACE // compiler specific keyboard
#define INTERFACE IMyMath
DECLARE_INTERFACE_(IMyMath, IDispatch)
{
	// IDispatch Methods
	// HRESULT CMyMath::GetTypeInfoCount(UINT* pCountTypeInfo)
	STDMETHOD(GetTypeInfoCount)(THIS_ UINT*) PURE;	// STDMETHOD method HRESULT __stdcall, FUNC PTR
	// HRESULT CMyMath::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo** ppITypeInfo)
	STDMETHOD(GetTypeInfo)(THIS_ UINT, LCID, ITypeInfo**) PURE;	// STDMETHOD method HRESULT __stdcall, FUNC PTR
	// HRESULT CMyMath::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId)
	STDMETHOD(GetIDsOfNames)(THIS_ REFIID, LPOLESTR*, UINT, LCID, DISPID*) PURE;	// STDMETHOD method HRESULT __stdcall, FUNC PTR
	// HRESULT CMyMath::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr)
	STDMETHOD(Invoke)(THIS_ DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*) PURE;	// STDMETHOD method HRESULT __stdcall, FUNC PTR

	// ISum method
	STDMETHOD(SumOfTwoIntegers)(THIS_ int, int, int*) PURE;
	// ISubtract method
	STDMETHOD(SubtractionTwoIntegers)(THIS_ int, int, int*) PURE;
};


/*
class IMyMath : public IDispatch
{
public:
	// pure virtual
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;

	// pure virtual
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

	STDMETHOD_(ULONG, Release)(THIS) PURE; // OtherRetVal __stdcall
*/

// CLSID of MyMath Component : {C331AB68-B16E-4092-B6D7-54E1DD16E574}
const CLSID CLSID_MyMath = { 0xc331ab68, 0xb16e, 0x4092, 0xb6, 0xd7, 0x54, 0xe1, 0xdd, 0x16, 0xe5, 0x74 };

// IID of IMyMath Interface : {D14281F6-DD7C-4891-A4AE-7C5D94648E2B}
const IID IID_IMyMath = { 0xd14281f6, 0xdd7c, 0x4891, 0xa4, 0xae, 0x7c, 0x5d, 0x94, 0x64, 0x8e, 0x2b };

