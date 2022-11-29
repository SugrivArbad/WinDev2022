#pragma once

class IMyMath : public IDispatch
{
public:
	// pure virtual
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;

	// pure virtual
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

// CLSID of MyMath Component : {C331AB68-B16E-4092-B6D7-54E1DD16E574}
const CLSID CLSID_MyMath = { 0xc331ab68, 0xb16e, 0x4092, 0xb6, 0xd7, 0x54, 0xe1, 0xdd, 0x16, 0xe5, 0x74 };

// IID of IMyMyth Interface : {D14281F6-DD7C-4891-A4AE-7C5D94648E2B}
const IID IID_IMyMath = { 0xd14281f6, 0xdd7c, 0x4891, 0xa4, 0xae, 0x7c, 0x5d, 0x94, 0x64, 0x8e, 0x2b };

