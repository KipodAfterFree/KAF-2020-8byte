#pragma once
#include <windows.h>


#ifndef _UNPACKING_H
#define _UNPACKING_H

#define CUSTOM_SECTION_NAME ".awsm"

#define INT3 0xcc

// Define frame of main_unpacking_loop
typedef struct {
	BYTE* currentPtr;
	DWORD actualIndex;
	DWORD mainStackEsp;
	DWORD unpackEFlags;
	DWORD unpackStackEsp;
	BYTE* awsmStart;
} mainLoopFrame, * pMainLoopFrame;


extern mainLoopFrame mainLoopUnpack;

void clean_opcodes(unsigned char* opcodes);
void parse_current_opcode(unsigned char* opcodes, unsigned char opcode_length);
void init_unpacking(BYTE* codeStart, const DWORD sectionLength);
void main_unpacking_loop();

#endif