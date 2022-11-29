#pragma once

class IMultiplication : public IUnknown
{
public:
	// IMultiplication specific method declarations pure virtual
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};

class IDivision : public IUnknown
{
public:
	//IDivision specific method declarations pure virtual
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};

// CLSID of MultiplicationDivision Component {FEF4B50F-49C0-42E0-9C7D-14402E6ED242}
const CLSID CLSID_MultiplicationDivision = { 0xfef4b50f, 0x49c0, 0x42e0, 0x9c, 0x7d, 0x14, 0x40, 0x2e, 0x6e, 0xd2, 0x42 };

// IID of IMultiplication Interface {005C4C6F-1171-4382-9E8D-FB70F89D088C}
const IID IID_IMultiplication = { 0x5c4c6f, 0x1171, 0x4382, 0x9e, 0x8d, 0xfb, 0x70, 0xf8, 0x9d, 0x8, 0x8c };

// IID of IDivision Interface {00E4084A-C620-4BC8-AFC9-2463783089C9}
const IID IID_IDivision = { 0xe4084a, 0xc620, 0x4bc8, 0xaf, 0xc9, 0x24, 0x63, 0x78, 0x30, 0x89, 0xc9 };

