#include "main.h"
#include <windows.h>
#include <iostream>
#include "../../PackAndVirtualize/PackAndVirtualize/helper.h"
#include "../../PackAndVirtualize/PackAndVirtualize/pack.h"
#include "unpacking.h"

#define CUSTOM_SECTION_NAME ".awsm"

#define INT3 0xcc

char byteShellcode[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // 8 byte current instruction

						}; 


int main(int argc, char* argv[]) {
	InitiateGreeting();

	const auto& baseExecutable = acquire_file_base("packedKafChal.exe");
	if (baseExecutable == nullptr) {
		return 1;
	}

	const PIMAGE_DOS_HEADER dosHeader = static_cast<PIMAGE_DOS_HEADER>(baseExecutable);
	const PIMAGE_NT_HEADERS32 ntHeader = reinterpret_cast<PIMAGE_NT_HEADERS32>(static_cast<char*>(baseExecutable) + dosHeader->e_lfanew);

	const PIMAGE_FILE_HEADER fileHeader = &ntHeader->FileHeader;
	const PIMAGE_OPTIONAL_HEADER32 optionalHeader = &ntHeader->OptionalHeader;

	const LPVOID sectionBegin = reinterpret_cast<BYTE*>(optionalHeader) + fileHeader->SizeOfOptionalHeader;
	const LPVOID sectionEnd = static_cast<BYTE*>(sectionBegin) + fileHeader->NumberOfSections * sizeof(IMAGE_SECTION_HEADER);
	PIMAGE_SECTION_HEADER currentSection = static_cast<PIMAGE_SECTION_HEADER>(sectionBegin);

	int i;

	// Find .awsm section
	for (i = 0; i < fileHeader->NumberOfSections && 
		std::strcmp(reinterpret_cast<char*>(currentSection->Name), CUSTOM_SECTION_NAME); i++) {
		currentSection = reinterpret_cast<PIMAGE_SECTION_HEADER>(static_cast<BYTE*>(sectionBegin) + i * sizeof(IMAGE_SECTION_HEADER));
	}

	// Handle could not find .awsm section case
	if (i == fileHeader->NumberOfSections) {
		printf("Could not find %s section, exiting...\n", CUSTOM_SECTION_NAME);
		return 1;
	}
	// address += currentSection->SizeOfRawData;
	BYTE* awesomeCodeStart = static_cast<BYTE*>(baseExecutable) + currentSection->PointerToRawData;
	const DWORD sectionLength = currentSection->SizeOfRawData;

	BYTE* currentPtr = awesomeCodeStart;
	BYTE* endOfSection = awesomeCodeStart + sectionLength;
	int actualIndex = 0;

	while (*reinterpret_cast<LONG64*>(currentPtr + actualIndex) != 0xdeadbeef) {
		int count = 0;
		do {
			*currentPtr = huge_unpacking_function(*(currentPtr + actualIndex));

			++currentPtr;
			++count;
		} while (*reinterpret_cast<WORD*>(currentPtr + actualIndex) != 0x1337);
		if (count >= 8) {
			printf("Found count: %d %x\n", count, currentPtr);
		}
		actualIndex += 2;
	}

	while (*reinterpret_cast<LONG64*>(currentPtr) != 0xdeadbeef)
		*(currentPtr++) = INT3;

	UnmapViewOfFile(baseExecutable);
}

void InitiateGreeting() {
	std::cout 
		<< "**********SOFTWARE PACKER 9000**********" << std::endl << std::endl
		<< "I have packed an important executable," << std::endl
		<< "are you able to tell me what it does?" << std::endl << std::endl
		<< "****************************************"	<< std::endl;
}