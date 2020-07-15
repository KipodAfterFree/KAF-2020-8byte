#include "opcode_helpers.h"
#include <Zydis/Zydis.h>
#include <iostream>

#ifdef _DEBUG
#include <sstream>
std::string get_inline_array(BYTE* beginningPtr, DWORD length) {
    std::stringstream ss;
    for (size_t i = 0; i < length; ++i)
    {
        if (i != 0)
            ss << "; ";
        char fmt[256];
        memset(fmt, 0, 256);
        sprintf_s(fmt, "%02x", *(beginningPtr + i));
        ss << fmt;
    }
    return ss.str();
}
#endif

DWORD acquire_opcode_length(BYTE* codePtr, const DWORD lengthToEnd
#ifdef _DEBUG
, const DWORD offset
#endif
)
{
	// Initialize decoder context
	ZydisDecoder decoder;
	ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_COMPAT_32, ZYDIS_ADDRESS_WIDTH_32);

    // Initialize formatter. Only required when you actually plan to do instruction
    // formatting ("disassembling"), like we do here
#ifdef _DEBUG
    ZydisFormatter formatter;
    ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL);
#endif
	ZyanU8* codePtrZy = static_cast<ZyanU8*>(codePtr);
    ZydisDecodedInstruction instruction;

    if (ZYAN_SUCCESS(ZydisDecoderDecodeBuffer(&decoder, codePtrZy, lengthToEnd,
        &instruction)))
    {
#ifdef _DEBUG
        // Format & print the binary instruction structure to human readable format
        char buffer[256];
        ZydisFormatterFormatInstruction(&formatter, &instruction, buffer, sizeof(buffer), 0);
        printf("[DEBUG] %08x: %s (%d) -> %s\n", offset, buffer, instruction.length, get_inline_array(codePtr, instruction.length).c_str());
#endif
        
        return instruction.length;
    }
	return -1;
}
