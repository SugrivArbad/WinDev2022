#pragma once

// Interface ISum
class ISum : public IUnknown
{
public:
	// ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0; // pure virtual
};

// Interface ISubtract
class ISubtract : public IUnknown
{
public:
	// ISubtract specific method declarations
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0; // pure virtual
};

// Interface IMultiplication
class IMultiplication : public IUnknown
{
public:
	// IMultiplication specific method declarations pure virtual
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};

// Interface IDivision
class IDivision : public IUnknown
{
public:
	//IDivision specific method declarations pure virtual
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};

// CLSID of CSumSubtract Component {705893BA-2601-429F-81B9-660977075646}
const CLSID CLSID_SumSubtract = { 0x705893ba, 0x2601, 0x429f, 0x81, 0xb9, 0x66, 0x9, 0x77, 0x7, 0x56, 0x46 };

// IID of ISum Interface {49B989AF-071F-468A-B28F-F301CFFDBAE7}
const IID IID_ISum = { 0x49b989af, 0x71f, 0x468a, 0xb2, 0x8f, 0xf3, 0x1, 0xcf, 0xfd, 0xba, 0xe7 };

// IID of ISubtract Interface {D80DD081-1A39-4FA9-AE6A-AB9EC5BC64F4}
const IID IID_ISubtract = { 0xd80dd081, 0x1a39, 0x4fa9, 0xae, 0x6a, 0xab, 0x9e, 0xc5, 0xbc, 0x64, 0xf4 };

// IID of IMultiplication Interface {005C4C6F-1171-4382-9E8D-FB70F89D088C}
const IID IID_IMultiplication = { 0x5c4c6f, 0x1171, 0x4382, 0x9e, 0x8d, 0xfb, 0x70, 0xf8, 0x9d, 0x8, 0x8c };

// IID of IDivision Interface {00E4084A-C620-4BC8-AFC9-2463783089C9}
const IID IID_IDivision = { 0xe4084a, 0xc620, 0x4bc8, 0xaf, 0xc9, 0x24, 0x63, 0x78, 0x30, 0x89, 0xc9 };

