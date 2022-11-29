#pragma once

class IMultiplication : public IUnknown
{
public:
	// IMultiplication specific method declarations
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;	// pure virtual
};

class IDivision : public IUnknown
{
public:
	// IDivision specific method declarations
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;	// pure virtual
};

// CLSID of IMultiplicationDivision Component {BBB02707-82BA-4ADD-84F7-BE9FBF855EB4}
const CLSID CLSID_MultiplicationDivision = { 0xbbb02707, 0x82ba, 0x4add, 0x84, 0xf7, 0xbe, 0x9f, 0xbf, 0x85, 0x5e, 0xb4 };

// IID of IMultiplication Interface {A4962282-A18E-4B5B-B8BF-1E8F82B9B05D}
const IID IID_IMultiplication = { 0xa4962282, 0xa18e, 0x4b5b, 0xb8, 0xbf, 0x1e, 0x8f, 0x82, 0xb9, 0xb0, 0x5d };

// IID of IDivision Interface {B95A34D2-5C41-4E1F-B0DB-2BFCFFEE17CA}
const IID IID_IDivision = { 0xb95a34d2, 0x5c41, 0x4e1f, 0xb0, 0xdb, 0x2b, 0xfc, 0xff, 0xee, 0x17, 0xca };

