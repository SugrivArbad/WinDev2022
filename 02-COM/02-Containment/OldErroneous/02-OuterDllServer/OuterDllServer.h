#pragma once

class ISum : public IUnknown
{
public:
	// ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0; // pure virtual
};

class ISubtract : public IUnknown
{
public:
	// ISubtract specific method declarations
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0; // pure virtual
};

// CLSID of SumSubtract Component {FFCDBBFA-95CB-4674-9E19-05DCBF7E160C}
const CLSID CLSID_SumSubtract = { 0xffcdbbfa, 0x95cb, 0x4674, 0x9e, 0x19, 0x5, 0xdc, 0xbf, 0x7e, 0x16, 0xc };

// IID of ISum Interface {A684D8E7-9E8D-4BDE-8FD0-D90DDF233054}
const IID IID_ISum = { 0xa684d8e7, 0x9e8d, 0x4bde, 0x8f, 0xd0, 0xd9, 0xd, 0xdf, 0x23, 0x30, 0x54 };

// IID of ISubtract Interface {69BF5ED2-2F7D-4426-B296-FADAEC4B5015}
const IID IID_ISubtract = { 0x69bf5ed2, 0x2f7d, 0x4426, 0xb2, 0x96, 0xfa, 0xda, 0xec, 0x4b, 0x50, 0x15 };

