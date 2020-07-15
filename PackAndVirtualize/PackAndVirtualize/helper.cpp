#include "helper.h"
#include <ostream>


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