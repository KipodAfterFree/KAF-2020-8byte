#include "unpacking.h"
#include "../../PackAndVirtualize/PackAndVirtualize/helper.h"
#include "../../PackAndVirtualize/PackAndVirtualize/pack.h"
#include "main.h"
#include <iostream>
#include <string.h>


#define FILLER_SIZE 4 * 1024 * 2// 2KB

mainLoopFrame mainLoopUnpack;

#define TO_LITTLE_ENDIAN(val) static_cast<signed int>(val >> 24 & 0x000000ff | \
													  val << 8  & 0x00ff0000 | \
													  val >> 8  & 0x0000ff00 | \
													  val << 24 & 0xff000000)

void init_unpacking(BYTE* codeStart, const DWORD sectionLength)
{
	/*
	Initialize frame of main_unpacking_loop
	*/

	mainLoopUnpack.currentPtr = codeStart;
	mainLoopUnpack.awsmStart = codeStart;
	mainLoopUnpack.actualIndex = 0;
	mainLoopUnpack.unpackEFlags = 0;
	mainLoopUnpack.mainStackEsp = { 0 };
	mainLoopUnpack.unpackStackEsp = { 0 };

	// Set jmp absolute address to main_unpacking_loop's address
	unsigned int mainLoopAddress = reinterpret_cast<unsigned int>(&main_unpacking_loop);
#ifdef _DEBUG
	* reinterpret_cast<unsigned int*>(&byteShellcode[8 + 2 + 1]) = mainLoopAddress;
#else
	* reinterpret_cast<unsigned int*>(&byteShellcode[8 + 2]) = mainLoopAddress;
#endif
	
	// unsigned char currentOpcode[8] = { 0x55, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
	// Go into main loop
	// HANDLE myThread = GetCurrentThread();
	// GetThreadContext(myThread, &mainLoopUnpack.mainContext);
	__asm {
		// Set everything to zero (idk if needed, probably will remove later.)
		xor eax, eax
		xor ebx, ebx 
		xor ecx, ecx 
		xor edx, edx

		// Call reduces esp by 4 (since it pushes eip)
		lea ebx, [esp - 4]

		// Initialize stack esp
		mov [mainLoopUnpack.mainStackEsp], ebx
		mov [mainLoopUnpack.unpackStackEsp], ebx
	}
	
	main_unpacking_loop();
}

void clean_opcodes(unsigned char* opcodes) {
	for (int i = 0; i < 8; i++)
		opcodes[i] = 0x90;
}

void parse_current_opcode(unsigned char* opcodes, unsigned char opcode_length) {
	signed char offset = 0;
	switch (opcode_length) {
	case 2:
		switch (opcodes[0]) {
			// near jmp
			case 0xEB:
				// Offset to jmp to:
				offset = static_cast<signed char>(opcodes[1]);
				mainLoopUnpack.currentPtr += offset;
				clean_opcodes(opcodes);
				break;
			// jne
			case 0x75:
			case 0x74:
				if (opcodes[0] == 0x75) {
					__asm {
						// Check flags
						mov eax, [mainLoopUnpack.unpackEFlags]
						push eax
						popfd
						jz successjmp
					}
				}
				else {
					__asm {
						// Check flags
						mov eax, [mainLoopUnpack.unpackEFlags]
						push eax
						popfd
						jnz successjmp
					}
				}
				offset = static_cast<signed char>(opcodes[1]);
			successjmp:
				if (offset != 0) {
					// Increase actual index to actual index 
					while (offset != 0) {
						if (*(WORD*)mainLoopUnpack.currentPtr != 0x1337) {
							--offset;
							++mainLoopUnpack.actualIndex;
						}
						else
							++mainLoopUnpack.currentPtr;
						++mainLoopUnpack.currentPtr;
					}
					++mainLoopUnpack.currentPtr;
					++mainLoopUnpack.currentPtr;
				}
				clean_opcodes(opcodes);
				break;
			}
	case 5:
		switch (opcodes[0]) {
			case 0xE8:
				const BYTE * beginningAwsmFile = mainLoopUnpack.awsmStart;
				const unsigned int offset = mainLoopUnpack.actualIndex;
				const BYTE* actual_address = mainLoopUnpack.awsmStart + FILLER_SIZE + offset;
				signed int* offsetInCall = reinterpret_cast<signed int*>(opcodes + 1);
				const signed int relative_address = *offsetInCall;
				const BYTE* final_address = actual_address + relative_address;
				//								                 v prelog
				//								                     v call length
#ifdef _DEBUG
				* offsetInCall = final_address - (byteShellcode + 2 + 5);
#else 
				* offsetInCall = final_address - (byteShellcode + 1 + 5);
#endif
				break;
		}
			
		break;
	}
}


void main_unpacking_loop_() {

	/*
	This function is like main_unpacking_loop() but generated without assembly. 
	I wrote the other function for more accuracy and for saving the stack pointer.
	(couldn't do it easily or elegantly in regular code)
	*/

	// Save unpacked stack pointer (and frame), and restore main stack pointer.

	/* NOTE: THIS IS NOT HERE, ONLY IN THE ASSEMBLY VERSION. */

	// Checks if the end of the code has been reached.
	if (*reinterpret_cast<unsigned int*>(mainLoopUnpack.currentPtr) == 0xdeadbeef) {
		__asm {
			ret
		}
	}

	// Contains current unpacked opcode instructions
	unsigned char currentOpcode[8] = 
#ifdef _DEBUG
	{ 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
#else
	{ 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
#endif

	// Contains actual opcode length.
	unsigned char count = 0;
	do {
		*(BYTE*)(currentOpcode + count) = huge_unpacking_function(*(BYTE*)mainLoopUnpack.currentPtr);

		++mainLoopUnpack.actualIndex;
		++mainLoopUnpack.currentPtr;
		++count;
	} while (*reinterpret_cast<WORD*>(mainLoopUnpack.currentPtr) != 0x1337);

	// Skip separator (0x1337 = 2 bytes)
	// REMINDER: the structure is <OPCODES> 0x1337 <OPCODES> 0x1337 .... 0xdeadbeef
	mainLoopUnpack.currentPtr += 2;

	// Uses acquired unpacked opcode and parses it.
	parse_current_opcode(currentOpcode, count);

	// Copy opcodes to actual executed shellcode
	
#ifdef _DEBUG
	memcpy(byteShellcode + 1 + 1, currentOpcode, 8);
#else 
	memcpy(byteShellcode + 1, currentOpcode, 8);
#endif
		

	// Save main stack pointer, and restore unpacked stack pointer (and frame).

	/* NOTE: NOT ALL OF THIS IS HERE, ONLY IN THE ASSEMBLY VERSION. */

	__asm {
		add esp, 0xc
		popad // Revert flags register to previous one
		// push edi
		// Acquire address to bytecode
		push eax
		lea eax, byteShellcode
		jmp eax
	}
}

// extern void* memcpy(void*, const void*, size_t);
// #pragma intrinsic(memcpy)
__declspec(naked) void main_unpacking_loop()
{
	/*
	Basically an async function cut into many pieces. (not really)
	Detects where it's currently at in the code position using the 
	mainLoopUnpack frame.
	*/

	__asm {
		// Save unpacking stack pointer and insert it into global variable
		mov [mainLoopUnpack.unpackStackEsp], esp

		// save flags
		pushfd
		pop [mainLoopUnpack.unpackEFlags]
		// Restore main stack pointer and push unpacking frame
		mov esp, [mainLoopUnpack.mainStackEsp]
		pushad
		
		 // Save state of running program
		mov ebp, esp
		sub esp, 12 // 8 for currentOpcodes + 1 for counter (12 for alignment)
		
		/*
		if (*reinterpret_cast<unsigned int*>(mainLoopUnpack.currentPtr) == 0xdeadbeef) {
			__asm {
				ret
			}
		}
		*/
		mov eax, mainLoopUnpack.currentPtr
		mov eax, [eax]
		mov ebx, 0xdeadbeef
		cmp eax, ebx
		jnz cont
		// Reached end, exit
		ret

	cont:

		/*
		unsigned char currentOpcode[8];
	
		for (int i = 0; i < 8; i++)
			currentOpcode[i] = 0x90;
		*/
		mov [ebp], 0x90
		mov [ebp - 1], 0x90
		mov [ebp - 2], 0x90
		mov [ebp - 3], 0x90
		mov [ebp - 4], 0x90
		mov [ebp - 5], 0x90
		mov [ebp - 6], 0x90
		mov [ebp - 7], 0x90
		
		
		// int count = 0;
		mov [ebp - 8], 0 

		/*
		do {
			*(BYTE*)(currentOpcode + count)= huge_unpacking_function(*(BYTE*)mainLoopUnpack.currentPtr);
			++mainLoopUnpack.currentPtr;
			++count;
		} while (*reinterpret_cast<WORD*>(mainLoopUnpack.currentPtr) != 0x1337);
		*/

	loopdi_loop:
		// (BYTE*)mainLoopUnpack.currentPtr
		lea esi, mainLoopUnpack.currentPtr
		mov ebx, [esi]

		// *(BYTE*)mainLoopUnpack.currentPtr
		xor eax, eax 
		mov al, [ebx]

		// huge_unpacking_function(*(BYTE*)mainLoopUnpack.currentPtr);
		push eax 
		call huge_unpacking_function
		add esp, 4

		// count
		lea edi, [ebp - 8]
		xor ecx, ecx
		mov cl, [edi]

		// *(BYTE*)(currentOpcode + count)
		lea ebx, [ebp + ecx - 7] // length of currentOpcode

		// *(BYTE*)(currentOpcode + count) = huge_unpacking_function(*(BYTE*)mainLoopUnpack.currentPtr);
		mov [ebx], al

		// ++mainLoopUnpack.currentPtr;
		// ++count;
		mov ebx, [esi]
		inc ebx 
		mov [esi], ebx
		inc [edi]

		// ++mainLoopUnpack.actualIndex
		lea edi, mainLoopUnpack.actualIndex
		mov ecx, [edi]
		inc ecx 
		mov [edi], ecx

		// *reinterpret_cast<WORD*>(mainLoopUnpack.currentPtr)
		mov esi, [esi]
		xor ebx, ebx
		mov bx, [esi]

		// while (*reinterpret_cast<WORD*>(mainLoopUnpack.currentPtr) != 0x1337);
		mov ax, 0x1337
		cmp bx, ax 
		jnz loopdi_loop

		// mainLoopUnpack.currentPtr += 2;
		lea esi, mainLoopUnpack.currentPtr
		mov eax, [esi]
		add eax, 2
		mov [esi], eax

		// Count
		lea edi, [ebp - 8]
		xor eax, eax 
		mov al, [edi]

		// parse_current_opcode(currentOpcode, count);
		push eax // count

		lea esi, [ebp - 7]
		push esi // currentOpcode
		call parse_current_opcode
		add esp, 8

		// memcpy(byteShellcode + 2, currentOpcode, 8);
		push 8 // 8

		lea ebx, [ebp - 7]
		push ebx  // currentOpcode

		lea ebx, byteShellcode
#ifdef _DEBUG
			add ebx, 2
#else
			add ebx, 1
#endif
		push ebx // byteShellcode + 2

		call memcpy
		add esp, 0xc

		// Restore stack
		add esp, 12

		// Save main stack frame
		lea ebx, [esp + 16]
		lea esi, mainLoopUnpack.mainStackEsp
		mov [esi], ebx
		
		// Restore unpacking stack frame
		popad
		
		// Restore previous unpacking stack pointer
		mov esp, [mainLoopUnpack.unpackStackEsp]

		// Jump to shellcode
		push eax
		lea eax, byteShellcode
		jmp eax
	}
}
