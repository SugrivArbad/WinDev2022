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

// CLSID of SumSubtract Component {354B2F5B-4DF3-45E6-B742-EBF6746863E4}
const CLSID CLSID_SumSubtract = { 0x354b2f5b, 0x4df3, 0x45e6, 0xb7, 0x42, 0xeb, 0xf6, 0x74, 0x68, 0x63, 0xe4 };

// IID of ISum Interface {E377D2CE-BE42-47A3-BD42-4AC8C8FDF052}
const IID IID_ISum = { 0xe377d2ce, 0xbe42, 0x47a3, 0xbd, 0x42, 0x4a, 0xc8, 0xc8, 0xfd, 0xf0, 0x52 };

// IID of ISubtract Interface {3D266A94-7C57-4347-86F3-F75D21672E1B}
const IID IID_ISubtract = { 0x3d266a94, 0x7c57, 0x4347, 0x86, 0xf3, 0xf7, 0x5d, 0x21, 0x67, 0x2e, 0x1b };

