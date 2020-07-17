#pragma once
#include <windows.h>

#ifndef _PACK_H
#define _PACK_H

BYTE volatile huge_packing_function(BYTE initalVal);
BYTE volatile huge_unpacking_function(BYTE initialVal);

BYTE volatile inline pack_1(BYTE initialVal);
BYTE volatile inline pack_2(BYTE initialVal);
BYTE volatile inline pack_3(BYTE initialVal);
BYTE volatile inline pack_4(BYTE initialVal);

// unpack operations

BYTE volatile inline rev_pack_1(BYTE initialVal);
BYTE volatile inline rev_pack_2(BYTE initialVal);
BYTE volatile inline rev_pack_3(BYTE initialVal);
BYTE volatile inline rev_pack_4(BYTE initialVal);

#endif