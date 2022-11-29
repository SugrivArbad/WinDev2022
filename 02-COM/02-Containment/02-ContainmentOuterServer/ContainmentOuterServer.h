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

// CLSID of CSumSubtract Component {705893BA-2601-429F-81B9-660977075646}
const CLSID CLSID_SumSubtract = { 0x705893ba, 0x2601, 0x429f, 0x81, 0xb9, 0x66, 0x9, 0x77, 0x7, 0x56, 0x46 };

// IID of ISum Interface {49B989AF-071F-468A-B28F-F301CFFDBAE7}
const IID IID_ISum = { 0x49b989af, 0x71f, 0x468a, 0xb2, 0x8f, 0xf3, 0x1, 0xcf, 0xfd, 0xba, 0xe7 };

// IID of ISubtract Interface {D80DD081-1A39-4FA9-AE6A-AB9EC5BC64F4}
const IID IID_ISubtract = { 0xd80dd081, 0x1a39, 0x4fa9, 0xae, 0x6a, 0xab, 0x9e, 0xc5, 0xbc, 0x64, 0xf4 };

