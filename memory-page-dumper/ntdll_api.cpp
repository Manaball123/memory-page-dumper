#include "api.h"





NTDLLAPI::NTDLLAPI()
{
	//too lazy 2 do error handling 
	HMODULE hMod = LoadLibraryA("ntdll.dll");
	pZwQueryVirtualMemory = reinterpret_cast<ZwQueryVirtualMemory_t*>(GetProcAddress(hMod, "ZwQueryVirtualMemory"));
	pNtReadVirtualMemory = reinterpret_cast<NtReadVirtualMemory_t*>(GetProcAddress(hMod, "NtReadVirtualMemory"));
}

bool NTDLLAPI::QueryPage(HANDLE hProcess, PMEMORY_BASIC_INFORMATION pMemInfo, LPCVOID address)
{
	//using the zw one cuz nt one sounds weird(seriously wtf is a __kernel_entry NTSYSCALLAPI NTSTATUS)
	//(0 = STATUS_SUCCESS)
	if (pZwQueryVirtualMemory(hProcess, (PVOID)address, MemoryBasicInformation, pMemInfo, sizeof(MEMORY_BASIC_INFORMATION), NULL) == 0)
		return true;
	return false;
}


bool NTDLLAPI::ReadMemory(HANDLE hProcesss, LPVOID buffer, LPVOID baseAddress, SIZE_T size)
{
	ULONG v;
	if (pNtReadVirtualMemory(hProcesss, baseAddress, buffer, size, &v))
		return true;
	return false;
}
