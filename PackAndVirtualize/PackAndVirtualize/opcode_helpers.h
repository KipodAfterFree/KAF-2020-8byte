#pragma once
#include <windows.h>

DWORD acquire_opcode_length(BYTE* codePtr, const DWORD lengthToEnd
#ifdef _DEBUG
	, const DWORD offset
#endif
);