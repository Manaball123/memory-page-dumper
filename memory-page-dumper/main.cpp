#include "api.h"
#include <iostream>

API* api;





int main(int argc, char** argv)
{
	api = new API;
	
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 33492);
	MEMORY_BASIC_INFORMATION memInfo = { 0 };
	LPVOID address = 0;
	while (api->QueryPage(hProc, &memInfo, address))
	{
		address = memInfo.BaseAddress;
		
		api->DumpMemory(hProc, address, memInfo.RegionSize);

		std::cout << "Dumped " << std::hex << address << std::endl;
		address = (LPVOID)((size_t)address + memInfo.RegionSize);
		

	}
	


	

	
}