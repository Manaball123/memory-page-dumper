#pragma once
#include <Windows.h>
#include "ntdll_headers.h"
#include <string>
#include <fstream>




//you can change this if you're using a custom kernel driver to do stuff


//Default API, overload these functions
class API
{
	
	std::wstring path;
public:
	API();
	virtual bool QueryPage(HANDLE hProcess, PMEMORY_BASIC_INFORMATION pMemInfo, LPCVOID address);
	virtual bool ReadMemory(HANDLE hProcesss, LPVOID buffer, LPVOID baseAddress, SIZE_T size);
	virtual bool WriteBuffer(LPCVOID buffer, size_t size, std::wstring fname_app);
	virtual bool DumpMemory(HANDLE hProcess, LPVOID baseAddress, SIZE_T size);

};


//Example: uses functions from ntdll instead of k32


class NTDLLAPI : public API
{
	ZwQueryVirtualMemory_t* pZwQueryVirtualMemory;
	NtReadVirtualMemory_t* pNtReadVirtualMemory;
public:
	NTDLLAPI();
	bool QueryPage(HANDLE hProcess, PMEMORY_BASIC_INFORMATION pMemInfo, LPCVOID address);
	bool ReadMemory(HANDLE hProcesss, LPVOID buffer, LPVOID baseAddress, SIZE_T size);

};