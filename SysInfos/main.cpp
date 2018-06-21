#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <intrin.h>

#include <vector>
#include <bitset>
#include <array>
#include <string>
#include <intrin.h>

#include <windows.h>
#include <iostream>
#include <cstdlib>

#pragma comment(lib, "user32.lib")

#define INFO_BUFFER_SIZE 32767


void test4()
{
	MEMORYSTATUSEX statex;

	statex.dwLength = sizeof(statex); // I misunderstand that

	GlobalMemoryStatusEx(&statex);
	std::cout << "Physical RAM => " << (float)statex.ullTotalPhys / (1024 * 1024 * 1024) << std::endl;
	std::cout << "Avail RAM => " << (float)statex.ullAvailPhys / (1024 * 1024 * 1024) << std::endl;

}


//https://docs.microsoft.com/en-us/cpp/intrinsics/cpuid-cpuidex
void test0()
{
	std::vector<std::array<int, 4>> data_;
	std::vector<std::array<int, 4>> extdata_;

	std::array<int,4> v4;

	__cpuid(v4.data(), 0);
	int nMax=v4[0];
	for (int i = 0; i <= nMax; ++i)
	{
		__cpuidex(v4.data(), i, 0);
		data_.push_back(v4);
	}

	char vendor[0x20];
	memset(vendor, 0, sizeof(vendor));
	*reinterpret_cast<int*>(vendor) = data_[0][1];
	*reinterpret_cast<int*>(vendor + 4) = data_[0][3];
	*reinterpret_cast<int*>(vendor + 8) = data_[0][2];
	std::cout << vendor << std::endl;

	// Calling __cpuid with 0x80000000 as the function_id argument
	// gets the number of the highest valid extended ID.
	__cpuid(v4.data(), 0x80000000);
	int nMaxEx = v4[0];
	for (int i = 0x80000000; i <= nMaxEx; ++i)
	{
		__cpuidex(v4.data(), i, 0);
		extdata_.push_back(v4);
	}

	char brand[0x40];
	memset(brand, 0, sizeof(brand));
	memcpy(brand, extdata_[2].data(), sizeof(v4));
	memcpy(brand + 16, extdata_[3].data(), sizeof(v4));
	memcpy(brand + 32, extdata_[4].data(), sizeof(v4));
	std::cout << brand << std::endl;
}


void test1()
{
	TCHAR  infoBuf[INFO_BUFFER_SIZE];
	DWORD  bufCharCount = INFO_BUFFER_SIZE;

	// Get and display the name of the computer.
	GetComputerName(infoBuf, &bufCharCount);
		
	printf(TEXT("Computer name:      %s\n"), infoBuf);

	// Get and display the user name.
	GetUserName(infoBuf, &bufCharCount);
	printf(TEXT("User name:          %s\n"), infoBuf);
}

void test()
{
	SYSTEM_INFO siSysInfo;

	// Copy the hardware information to the SYSTEM_INFO structure. 

	GetSystemInfo(&siSysInfo);

	// Display the contents of the SYSTEM_INFO structure. 

	printf("Hardware information: \n");
	//printf("  OEM ID: %u\n", siSysInfo.dwOemId);
	printf("  Number of processors: %u\n",
		siSysInfo.dwNumberOfProcessors);
	printf("  Page size: %u\n", siSysInfo.dwPageSize);
	printf("  Processor type: %u\n", siSysInfo.dwProcessorType);
	printf("  Minimum application address: %p\n",
		siSysInfo.lpMinimumApplicationAddress);
	printf("  Maximum application address: %p\n",
		siSysInfo.lpMaximumApplicationAddress);
	printf("  Active processor mask: %llu\n",
		siSysInfo.dwActiveProcessorMask);
}

int main(int argc, char **argv)
{
	std::cout << "Hello world" << std::endl;
	test();
	test1();
	test0();
	test4();
	std::cout << "Wait key..." << std::endl;
	int c=getchar();
}