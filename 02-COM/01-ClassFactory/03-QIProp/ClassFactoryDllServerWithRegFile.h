#pragma once
class ISum: public IUnknown
{
public:
	// he calling convention waparanar function return hotana swatacha stack swata clear karat
	// #include <windef.h> for __pascal
	// #include <objbase.h> for STDMEHODCALLTYPE
	// typedef WINAPI __stdcall
	// typedef WINAPI CALLBACK
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubtract: public IUnknown
{
public:
	virtual HRESULT __stdcall SubtractTwoIntegers(int, int, int*) = 0;
};

class IMultiply: public IUnknown
{
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};

//Stringized form of GUID and Numeric/Programatic form of GUID
// {E7A2EC19-796A-4427-829B-521987413843}
const CLSID CLSID_SumSubtractMultiply = { 0xe7a2ec19, 0x796a, 0x4427, 0x82, 0x9b, 0x52, 0x19, 0x87, 0x41, 0x38, 0x43 };

// {B8D78A46-4441-4720-A83B-563E7BF1C6F4}
const IID IID_ISum = { 0xb8d78a46, 0x4441, 0x4720, 0xa8, 0x3b, 0x56, 0x3e, 0x7b, 0xf1, 0xc6, 0xf4 };

// {29D7C723-3008-4ED9-8C1F-8D64D763DA4E}
const IID IID_ISubtract = { 0x29d7c723, 0x3008, 0x4ed9, 0x8c, 0x1f, 0x8d, 0x64, 0xd7, 0x63, 0xda, 0x4e };

// {64A77DE4-AD13-4714-9B7B-7FFEBB9DC397}
const IID IID_IMultiply = { 0x64a77de4, 0xad13, 0x4714, 0x9b, 0x7b, 0x7f, 0xfe, 0xbb, 0x9d, 0xc3, 0x97 };
