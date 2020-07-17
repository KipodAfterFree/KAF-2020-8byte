#pragma once
#include <windows.h>
#include <tuple>

#ifndef _HELPER_H
#define _HELPER_H
const PIMAGE_SECTION_HEADER get_section_by_name(const LPVOID baseExecutable, const char* custom_section_name);
const DWORD get_section_address(const char* sectionName);
HMODULE* get_proc_modules(HANDLE hProc, DWORD& size);
// (File headers, File content)
const LPVOID acquire_file_base(const char* filename);
#endif
