#include <windows.h>
#pragma comment(lib, "MyMathOne.lib")

// Hungarian Notation
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	//code
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		break;

	default:
		break;
	}

	return (TRUE);
}

// Microsoft specific specifier
__declspec(dllexport) int MakeSquare(int num)
{
	//code
	return (num*num);
}

