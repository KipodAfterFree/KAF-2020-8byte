// PackAndVirtualize.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "helper.h"
#include <iostream>
#include <windows.h>


#define MODIFY_SECTION ".awsm"

int  main(int argc, char* argv[])
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
	const PIMAGE_NT_HEADERS32 ntHeader = static_cast<PIMAGE_NT_HEADERS32>((LPVOID)((char*)baseExecutable + dosHeader->e_lfanew));
	// printf("%c %c %c %c\n", (headers->Signature >> 24) & 0xff , (headers->Signature >> 16) & 0xff, (headers->Signature >> 8) & 0xff, headers->Signature & 0xff);
	// printf("%x\n", headers->Signature);

	const PIMAGE_FILE_HEADER fileHeader = &ntHeader->FileHeader;
	const PIMAGE_OPTIONAL_HEADER32 optionalHeader = &ntHeader->OptionalHeader;

	const LPVOID sectionBegin = (BYTE*)optionalHeader + fileHeader->SizeOfOptionalHeader;
	const LPVOID sectionEnd = (BYTE*)sectionBegin + fileHeader->NumberOfSections * sizeof(IMAGE_SECTION_HEADER);
	PIMAGE_SECTION_HEADER currentSection = static_cast<PIMAGE_SECTION_HEADER>(sectionBegin);

	int i;
	// DWORD address = 0;
	for (i = 0; i < fileHeader->NumberOfSections && std::strcmp(const_cast<const char*>((char*)currentSection->Name), MODIFY_SECTION); i++) {
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
		currentSection = static_cast<PIMAGE_SECTION_HEADER>((LPVOID)((BYTE*)sectionBegin + i * sizeof(IMAGE_SECTION_HEADER)));
	}

	if (i == fileHeader->NumberOfSections) {
		printf("Could not find %s section, exiting...\n", MODIFY_SECTION);
		return 1;
	}
	// address += currentSection->SizeOfRawData;
	const BYTE* awesomeCodeStart = (BYTE*)baseExecutable + currentSection->PointerToRawData;
	auto fromLittleToBig = [](DWORD x) { return (x & 0x000000ff) << 24u | (x & 0x0000ff00) << 8u | 
														  (x & 0x00ff0000) >> 8u | (x & 0xff000000) >> 24u;  };
	for (i = 0; i < 100; ++i) {
		printf("%02x ", *(BYTE*)(awesomeCodeStart + i));
	}
	
	// Clean up
	UnmapViewOfFile(baseExecutable);
	return 0;
}

