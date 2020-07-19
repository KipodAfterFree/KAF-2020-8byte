#include "main.h"
#include "unpacking.h"
#include "packed_exe_section.h"

#include <windows.h>
#include <iostream>
#include "../../PackAndVirtualize/PackAndVirtualize/helper.h"
#include "../../PackAndVirtualize/PackAndVirtualize/pack.h"

#define FUNC_PTR_TO_LITTLE_ENDIAN(func_name) (reinterpret_cast<unsigned int>(&func_name) >> 24) & 0x000000ff | \
											 (reinterpret_cast<unsigned int>(&func_name) << 8)  & 0x00ff0000 | \
											 (reinterpret_cast<unsigned int>(&func_name) >> 8)  & 0x0000ff00 | \
											 (reinterpret_cast<unsigned int>(&func_name) << 24) & 0xff000000
			



#pragma section(".awsm1", execute, read, write)
#pragma comment(linker, "/SECTION:.awsm1,ERW")

__declspec(allocate(".awsm1")) unsigned char byteShellcode[17] = { 
#ifdef _DEBUG
	0xcc,
#endif
	0x58, // pop eax
	0x00, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // Reserved for current unpacked opcode
	// 0xEA, 
	0x68, // push
	// 0x8D, 0x3D, // lea edi, FUNC_PTR_TO_LITTLE_ENDIAN
	0x00, 0x00, 0x00, 0x00, // Reserved for main loop address
	0xC3 // ret
	// 0xFF, 0xE7 // Absolute `jmp eax`
};
//        ^ Address
//  ^ Absolute jump 

#pragma code_seg(".text")

int main(int argc, char* argv[]) {
	// Display prints at beginning
	InitiateGreeting();

	// Map packed executable into memory
	//const auto& baseExecutable = acquire_file_base("packedKafChal.exe");
	//if (baseExecutable == nullptr) {
	//	return 1;
	//}
	const auto& baseExecutable = static_cast<LPVOID>(GetModuleHandleA(NULL));

	const auto& currentSection = get_section_by_name(baseExecutable, CUSTOM_SECTION_NAME);

	if (currentSection == NULL) {
		return 1;
	}
	// Get offset to beginning of the .awsm section
	BYTE* awesomeCodeStart = static_cast<BYTE*>(baseExecutable) + currentSection->VirtualAddress;
	const DWORD sectionLength = currentSection->Misc.VirtualSize;

	// Start unpacking
	init_unpacking(awesomeCodeStart, sectionLength);

	// Unmap file from memory
	UnmapViewOfFile(baseExecutable);
}

void InitiateGreeting() {
	std::cout 
		<< "**********SOFTWARE PACKER 9000**********" << std::endl << std::endl
		<< "I have packed an important executable," << std::endl
		<< "are you able to tell me what it does?" << std::endl << std::endl
		<< "****************************************"	<< std::endl;
}