#include "helper.h"
#include <Psapi.h>
#include <ostream>

#define MAX_PROCS_INIT 1024

const PIMAGE_SECTION_HEADER get_section_by_name(const LPVOID baseExecutable, const char* custom_section_name) {
	// Locate DOS header (and end)
	const PIMAGE_DOS_HEADER dosHeader = static_cast<PIMAGE_DOS_HEADER>(baseExecutable);
	const PIMAGE_NT_HEADERS32 ntHeader = reinterpret_cast<PIMAGE_NT_HEADERS32>(static_cast<char*>(baseExecutable) + dosHeader->e_lfanew);

	// Acquire IMAGE_FILE_HEADER, IMAGE_OPTIONAL_HEADER from the NTHeader  
	const PIMAGE_FILE_HEADER fileHeader = &ntHeader->FileHeader;
	const PIMAGE_OPTIONAL_HEADER32 optionalHeader = &ntHeader->OptionalHeader;

	// Acquire first section
	const LPVOID firstSectionBegin = reinterpret_cast<BYTE*>(optionalHeader) + fileHeader->SizeOfOptionalHeader;
	const LPVOID allSectionEnd = static_cast<BYTE*>(firstSectionBegin) + fileHeader->NumberOfSections * sizeof(IMAGE_SECTION_HEADER);
	PIMAGE_SECTION_HEADER currentSection = static_cast<PIMAGE_SECTION_HEADER>(firstSectionBegin);

	int i;

	// Find .awsm section
	for (i = 0; i < fileHeader->NumberOfSections &&
		std::strcmp(reinterpret_cast<char*>(currentSection->Name), custom_section_name); i++) {
		currentSection = reinterpret_cast<PIMAGE_SECTION_HEADER>(static_cast<BYTE*>(firstSectionBegin) + i * sizeof(IMAGE_SECTION_HEADER));
	}

	// Handle could not find .awsm section case
	if (i == fileHeader->NumberOfSections) {
		printf("Could not find %s section, exiting...\n", custom_section_name);
		return NULL;
	}

	return currentSection;
}

HMODULE* get_proc_modules(HANDLE hProc, DWORD& size) {
	HMODULE* procs;
	DWORD bytesReturned;
	DWORD current_mem = MAX_PROCS_INIT;
	do {
		procs = new HMODULE[current_mem];
		if (EnumProcessModules(hProc, procs, current_mem * sizeof(HMODULE), &bytesReturned) == 0) {}
		if (bytesReturned / sizeof(HMODULE) == current_mem) {
			current_mem *= 2;
			delete[] procs;
			procs = nullptr;
		}
		else { break; }
	} while (true);
	size = bytesReturned / sizeof(HMODULE);
	return procs;
}

const DWORD get_section_address(const char* sectionName) {
	return get_section_by_name((LPVOID)GetModuleHandle(NULL), ".text")->VirtualAddress;
}

const LPVOID acquire_file_base(const char* filename) {

	const HANDLE hFile = CreateFileA(filename, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	char buffer[260];
	const auto currentDir = GetCurrentDirectoryA(MAX_PATH, (LPSTR)buffer);
	if (hFile == INVALID_HANDLE_VALUE) {
		printf("CreateFile failed in read mode, error: %d", GetLastError());
		return nullptr;
	}

	printf("Mapping file...\n");
	const HANDLE hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE | SEC_COMMIT, 0, 0, NULL);
	if (hFileMap == NULL) {
		printf("CreateFileMapping failed with: %d", GetLastError());
		CloseHandle(hFile);
		return nullptr;
	}

	const LPVOID lpFileBase = MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (lpFileBase == NULL) {
		printf("Could not map file, failed with: %d", GetLastError());
		CloseHandle(hFile);
		CloseHandle(hFileMap);
		return nullptr;
	}

	/*
	printf("Getting file size...\n");
	DWORD filesize;
	if ((filesize = GetFileSize(hFile, NULL)) == 0) {
		printf("Could not get file size, failed with: %d", GetLastError());
		CloseHandle(hFile);
		CloseHandle(hFileMap);
		throw "Error";
	}
	const LPVOID buffer= new char[filesize];

	printf("Reading file...\n");
	if (ReadFile(hFile, buffer, filesize, 0, NULL) == 0) {
		printf("Could not read file, failed with: %d", GetLastError());
		delete[] buffer;
		CloseHandle(hFile);
		CloseHandle(hFileMap);
		throw "Error";
	}
	*/
	return std::move(lpFileBase);
}