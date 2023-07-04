#include "api.h"
#include "utils.h"
#include <filesystem>


namespace filesystem = std::filesystem;
API::API()
{
	path = std::wstring(L"./") + std::to_wstring(static_cast<long>(time(0)));
	filesystem::create_directories(path);
}


bool API::QueryPage(HANDLE hProcess, PMEMORY_BASIC_INFORMATION pMemInfo, LPCVOID address)
{
	if (VirtualQueryEx(hProcess, address, pMemInfo, sizeof(MEMORY_BASIC_INFORMATION)))
		return true;

	return false;
}


bool API::ReadMemory(HANDLE hProcesss, LPVOID buffer, LPVOID baseAddress, SIZE_T size)
{
	SIZE_T v;
	if (ReadProcessMemory(hProcesss, baseAddress, buffer, size, &v))
		return true;
	return false;
}


bool API::WriteBuffer(LPCVOID buffer, size_t size, std::wstring fname_app)
{
    std::wstring fname = path;
	fname.append(L"\\");
    fname.append(fname_app);



    HANDLE hFile = CreateFileW(fname.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

    DWORD bytesWritten;

    //write dumped memory to file
	if (!WriteFile(hFile, buffer, size, &bytesWritten, nullptr))
		return false;

    CloseHandle(hFile);
	return true;

}	

bool API::DumpMemory(HANDLE hProcess, LPVOID baseAddress, SIZE_T size)
{
	char* buf = new char[size];
	WriteBuffer(buf, size, ToWstring(ToHex((SIZE_T)baseAddress)) + L".bin");
	delete[] buf;
}



