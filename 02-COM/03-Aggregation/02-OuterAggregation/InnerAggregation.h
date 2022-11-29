class IMultiplication : public IUnknown
{
public:
	// IMultiplication specific method declarations
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0; // pure virtual
};

class IDivision : public IUnknown
{
public:
	// IDivision specific method declarations
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0; // pure virtual
};

// CLSID of MultiplicationDivision Component {E9A70D7C-C382-4398-B540-AEFEF19232EB}
const CLSID CLSID_MultiplicationDivision = { 0xe9a70d7c, 0xc382, 0x4398, 0xb5, 0x40, 0xae, 0xfe, 0xf1, 0x92, 0x32, 0xeb };

// IID of IMultiplication Interface {931F5632-5822-4888-9581-9519B1EA630B}
const IID IID_IMultiplication = { 0x931f5632, 0x5822, 0x4888, 0x95, 0x81, 0x95, 0x19, 0xb1, 0xea, 0x63, 0xb };

// IID of IDivision Interface {5F80277A-B118-4F2B-8F57-FF3FA8E7C683}
const IID IID_IDivision = { 0x5f80277a, 0xb118, 0x4f2b, 0x8f, 0x57, 0xff, 0x3f, 0xa8, 0xe7, 0xc6, 0x83 };

// [HKEY_CLASSES_ROOT\CLSID\{354B2F5B-4DF3-45E6-B742-EBF6746863E4}\InprocServer32]

