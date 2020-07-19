// PackAndVirtualize.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "helper.h"
#include "pack.h"
#include "opcode_helpers.h"
#include <iostream>
#include <windows.h>


#define MODIFY_SECTION ".awsm"

#define FILLER_SIZE 5 * 1024 * 1024 // 10MB

#define PUSH_EBP 0x55
#define INT3 0xcc

BYTE parse_special_opcodes() {
	return 1;
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		
		printf("Usage: %s filename.exe", argv[0]);
		exit(-1);
	}

	
	// printf("%d", sizeof(IMAGE_SECTION_HEADER));
	const auto& baseExecutable = acquire_file_base(argv[1]);
	if (baseExecutable == nullptr) {
		return 1;
	}

	const PIMAGE_DOS_HEADER dosHeader = static_cast<PIMAGE_DOS_HEADER>(baseExecutable);
	const PIMAGE_NT_HEADERS32 ntHeader = reinterpret_cast<PIMAGE_NT_HEADERS32>(static_cast<char*>(baseExecutable) + dosHeader->e_lfanew);
	// printf("%c %c %c %c\n", (headers->Signature >> 24) & 0xff , (headers->Signature >> 16) & 0xff, (headers->Signature >> 8) & 0xff, headers->Signature & 0xff);
	// printf("%x\n", headers->Signature);

	const PIMAGE_FILE_HEADER fileHeader = &ntHeader->FileHeader;
	const PIMAGE_OPTIONAL_HEADER32 optionalHeader = &ntHeader->OptionalHeader;

	const LPVOID sectionBegin = reinterpret_cast<BYTE*>(optionalHeader) + fileHeader->SizeOfOptionalHeader;
	const LPVOID sectionEnd = static_cast<BYTE*>(sectionBegin) + fileHeader->NumberOfSections * sizeof(IMAGE_SECTION_HEADER);
	PIMAGE_SECTION_HEADER currentSection = static_cast<PIMAGE_SECTION_HEADER>(sectionBegin);

	int i;
	// DWORD address = 0;
	for (i = 0; i < fileHeader->NumberOfSections && std::strcmp(const_cast<const char*>(reinterpret_cast<char*>(currentSection->Name)), MODIFY_SECTION); ++i) {
		/*
		printf("Name: %s\n", currentSection->Name);
		printf("VirtualSize: %x\n", currentSection->Misc.VirtualSize);
		printf("VirtualAddress: %x\n", currentSection->VirtualAddress);
		printf("SizeOfRawData: %x\n", currentSection->SizeOfRawData);
		printf("PointerToRawData: %x\n", currentSection->PointerToRawData);
		printf("Characteristics: %x\n", currentSection->Characteristics);
		printf("\n");
		*/
		// address += currentSection->Misc.VirtualSize;
		currentSection = reinterpret_cast<PIMAGE_SECTION_HEADER>(static_cast<BYTE*>(sectionBegin) + i * sizeof(IMAGE_SECTION_HEADER));
		
	}

	if (i > fileHeader->NumberOfSections) {
		printf("Could not find %s section, exiting...\n", MODIFY_SECTION);
		return 1;
	}
	// address += currentSection->SizeOfRawData;
	BYTE* awesomeCodeStart = static_cast<BYTE*>(baseExecutable) + currentSection->PointerToRawData;
	const DWORD section_length = currentSection->SizeOfRawData;
	/*
	auto fromLittleToBig = [](DWORD x) { return (x & 0x000000ff) << 24u | (x & 0x0000ff00) << 8u | 
														  (x & 0x00ff0000) >> 8u | (x & 0xff000000) >> 24u;  };

	for (i = 0; i < 100; ++i) {
		printf("%02x ", *(BYTE*)(awesomeCodeStart + i));
	}
	*/
	i = 0;
	
	while (*(BYTE*)(awesomeCodeStart + ++i) != PUSH_EBP)
		*(BYTE*)(awesomeCodeStart + i) = INT3;

	BYTE* currentOpcodePtr = awesomeCodeStart + i;
	BYTE* copyToOpcodePtr = awesomeCodeStart;
	const BYTE* sectionEndPtr = awesomeCodeStart + section_length;
	while (currentOpcodePtr < sectionEndPtr) {
		
		DWORD instructionLength = acquire_opcode_length(currentOpcodePtr, sectionEndPtr - currentOpcodePtr
#ifdef _DEBUG
			, copyToOpcodePtr - awesomeCodeStart
#endif
		);

		if (instructionLength == -1)
			break;
		BYTE* initCopyToOpcodePtr = copyToOpcodePtr;
		while (copyToOpcodePtr < initCopyToOpcodePtr + instructionLength) {
			*copyToOpcodePtr = huge_packing_function(*currentOpcodePtr);
			*currentOpcodePtr = INT3;

			++currentOpcodePtr;
			++copyToOpcodePtr;
		}
		*(WORD*)copyToOpcodePtr = 0x1337;
		copyToOpcodePtr += 2;
	}
	*(LONG64*)(copyToOpcodePtr) = 0xdeadbeef;
	
	
	// Code is supposed to be at 
	// LPVOID originalEntry = currentSection + section_length - ;
	/*
	while (*(LONG64*)(awesomeCodeStart + i) != 0xdeadbeef) {
		
		for (int j =0; j < 8; j++)
			*(BYTE*)(awesomeCodeStart + i + j) = huge_unpacking_function(*(BYTE*)(awesomeCodeStart + i + j));
		i += 8;
	}
	*/
	// Clean up
	UnmapViewOfFile(baseExecutable);
	return 0;
}

