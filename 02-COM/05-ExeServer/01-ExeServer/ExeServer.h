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

// CLSID of SumSubtract component {13309C46-B65A-4C73-B7CD-1E701038594F}
const CLSID CLSID_SumSubtract = { 0x13309c46, 0xb65a, 0x4c73, 0xb7, 0xcd, 0x1e, 0x70, 0x10, 0x38, 0x59, 0x4f };

// IID of ISum Interface {19EC9C50-0F01-4E1C-A67B-DA404E2DB19D}
const IID IID_ISum = { 0x19ec9c50, 0xf01, 0x4e1c, 0xa6, 0x7b, 0xda, 0x40, 0x4e, 0x2d, 0xb1, 0x9d };

// IID of ISubtract interface {6ED29EC5-9628-46E8-8285-4881CB5ECE63}
const IID IID_ISubtract = { 0x6ed29ec5, 0x9628, 0x46e8, 0x82, 0x85, 0x48, 0x81, 0xcb, 0x5e, 0xce, 0x63 };

