#pragma once
#include <windows.h>

BYTE* gCodeStart;
DWORD gSectionLength;

typedef struct {
	BYTE* currentPtr;

} mainLoopStruct, *pMainLoopStruct;

void init_unpacking(BYTE* codeStart, const DWORD sectionLength);

void main_unpacking_loop();