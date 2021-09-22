#include <iostream>
#include <Windows.h>
#include <tchar.h>
#define DLL_NAME _T("kernel32.dll")
#define PROC_NAME _T("AcquireSRWLockExclusive")
FARPROC WINAPI GetMyProcAddress(_In_ HMODULE hModule, _In_ LPCSTR lpProcName);

int _tmain()
{
	HMODULE hDll = GetModuleHandle(DLL_NAME);
	//FARPROC procAddress = GetMyProcAddress(hDll,(LPCSTR)1);
	FARPROC procAddress = GetProcAddress(hDll, (LPCSTR)1);
	return NULL;
}

FARPROC WINAPI GetMyProcAddress(_In_ HMODULE hModule, _In_ LPCSTR lpProcName) {
	PIMAGE_DOS_HEADER dos = NULL;
	PIMAGE_NT_HEADERS nt = NULL;
	PIMAGE_EXPORT_DIRECTORY export_dir = NULL;
	dos = (PIMAGE_DOS_HEADER)hModule;
	nt = (PIMAGE_NT_HEADERS)((DWORD)dos->e_lfanew + (DWORD)dos);
	export_dir = (PIMAGE_EXPORT_DIRECTORY)(nt->OptionalHeader.DataDirectory[0].VirtualAddress + (DWORD)dos);
	DWORD dwBase = export_dir->Base;
	DWORD *pAddressOfFunction = (DWORD *)(export_dir->AddressOfFunctions+(DWORD)hModule);
	DWORD dwName = (DWORD)lpProcName;
	if (dwName &0xFFFF0000 != 0) {
		//当以函数名来寻址
	}
	
	if(dwName< dwBase || (dwName- dwBase)+1>export_dir->NumberOfFunctions)
		return NULL;
	return (FARPROC)(pAddressOfFunction[dwName - dwBase]+(DWORD)hModule);

	return NULL;
}
