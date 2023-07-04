#pragma once
#include <Windows.h>
typedef enum _MEMORY_INFORMATION_CLASS {
	MemoryBasicInformation
} MEMORY_INFORMATION_CLASS;

NTSYSAPI NTSTATUS ZwQueryVirtualMemory(
	IN				HANDLE                   ProcessHandle,
	IN				PVOID                    BaseAddress OPTIONAL,
	IN				MEMORY_INFORMATION_CLASS MemoryInformationClass,
	OUT		        PVOID                    MemoryInformation,
	IN	            SIZE_T                   MemoryInformationLength,
	OUT				PSIZE_T                  ReturnLength OPTIONAL
);
NTSYSAPI
NTSTATUS
NTAPI
NtReadVirtualMemory(
	IN HANDLE ProcessHandle,
	IN PVOID BaseAddress,
	OUT PVOID Buffer,
	IN ULONG BufferLength,
	OUT PULONG ReturnLength OPTIONAL
);


using ZwQueryVirtualMemory_t = decltype(ZwQueryVirtualMemory);
using NtReadVirtualMemory_t = decltype(NtReadVirtualMemory);
