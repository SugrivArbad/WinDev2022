#pragma once
#undef INTERFACE // compiler specific keyboard
#define INTERFACE ISum
DECLARE_INTERFACE_(ISum, IUnknown)
{
	// IUnknown Method
	STDMETHOD(QueryInterface)(THIS_ REFIID, void**) PURE;	// STDMETHOD method HRESULT __stdcall, FUNC PTR
	STDMETHOD_(ULONG, AddRef)(THIS) PURE; // OtherRetVal __stdcall
	STDMETHOD_(ULONG, Release)(THIS) PURE; // OtherRetVal __stdcall

	// ISum method
	STDMETHOD(SumOfTwoIntegers)(THIS_ int, int, int*) PURE;
};

#undef INTERFACE // compiler specific keyboard
#define INTERFACE ISubtract
DECLARE_INTERFACE_(ISubtract, IUnknown)
{
	// IUnknown Method
	STDMETHOD(QueryInterface)(THIS_ REFIID, void**) PURE;	// STDMETHOD method HRESULT __stdcall, func ptr
	STDMETHOD_(ULONG, AddRef)(THIS) PURE; // OtherRetVal __stdcall
	STDMETHOD_(ULONG, Release)(THIS) PURE; // OtherRetVal __stdcall

	// ISubtract method
	STDMETHOD(SubtractTwoIntegers)(THIS_ int, int, int*) PURE;
};

//Stringized form of GUID and Numeric/Programatic form of GUID
// {FB3B7CE8-9C8A-40DD-9259-C83A1BFB0A84}
const CLSID CLSID_SumSubtract = { 0xfb3b7ce8, 0x9c8a, 0x40dd, 0x92, 0x59, 0xc8, 0x3a, 0x1b, 0xfb, 0xa, 0x84 };

// {0E4EF058-8280-4554-AE6A-45E1990009B8}
const IID IID_ISum = { 0xe4ef058, 0x8280, 0x4554, 0xae, 0x6a, 0x45, 0xe1, 0x99, 0x0, 0x9, 0xb8 };

// {07E29BFD-1194-4A57-A8D6-B943DF10B531}
const IID IID_ISubtract = { 0x7e29bfd, 0x1194, 0x4a57, 0xa8, 0xd6, 0xb9, 0x43, 0xdf, 0x10, 0xb5, 0x31 };

