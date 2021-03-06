#include "packed_exe_section.h"
#include <iostream>
#include <windows.h>

#define FILLER_SIZE 4 * 1024 * 2// 2KB

#pragma section(".awsm", execute, read)
#pragma comment(linker, "/SECTION:.awsm,ER")

__declspec(allocate(".awsm")) unsigned char bigarray[FILLER_SIZE] = { 0x90 };

#pragma code_seg(".awsm")
int _tmain(int argc, char* argv[]) {
	// flag is KAF{e1ght_byt3s_1s_4ll_1t_t4k3s}
	// printf("Hello world!\n");
	const auto flag_attempt = __argv[1];
	const auto flag_length = strlen(flag_attempt);
	constexpr size_t len = 32;
	if (flag_length != len) {
		printf("Failed!");
		exit(1);
	}

	if ((flag_attempt[28] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[28] & 2) != 2) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[28] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[28] & 16) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[28] & 4) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[28] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[28] & 8) != 8) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[28] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[10] & 1) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[10] & 16) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[10] & 8) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[10] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[10] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[10] & 4) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[10] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[10] & 2) != 2) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[16] & 8) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[16] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[16] & 2) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[16] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[16] & 4) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[16] & 64) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[16] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[16] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[21] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[21] & 2) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[21] & 8) != 8) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[21] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[21] & 1) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[21] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[21] & 4) != 4) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[21] & 16) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[25] & 4) != 4) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[25] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[25] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[25] & 2) != 2) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[25] & 8) != 8) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[25] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[25] & 32) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[25] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[19] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[19] & 8) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[19] & 1) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[19] & 64) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[19] & 4) != 4) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[19] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[19] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[19] & 2) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[29] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[29] & 8) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[29] & 64) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[29] & 4) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[29] & 2) != 2) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[29] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[29] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[29] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[11] & 2) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[11] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[11] & 4) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[11] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[11] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[11] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[11] & 8) != 8) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[11] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[7] & 2) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[7] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[7] & 16) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[7] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[7] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[7] & 1) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[7] & 8) != 8) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[7] & 4) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[2] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[2] & 2) != 2) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[2] & 8) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[2] & 1) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[2] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[2] & 4) != 4) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[2] & 32) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[2] & 16) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[9] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[9] & 4) != 4) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[9] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[9] & 2) != 2) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[9] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[9] & 32) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[9] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[9] & 8) != 8) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[24] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[24] & 8) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[24] & 2) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[24] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[24] & 1) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[24] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[24] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[24] & 4) != 4) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[22] & 4) != 4) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[22] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[22] & 2) != 2) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[22] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[22] & 32) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[22] & 8) != 8) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[22] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[22] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[17] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[17] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[17] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[17] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[17] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[17] & 8) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[17] & 4) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[17] & 2) != 2) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[30] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[30] & 8) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[30] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[30] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[30] & 4) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[30] & 2) != 2) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[30] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[30] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[5] & 4) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[5] & 2) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[5] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[5] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[5] & 8) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[5] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[5] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[5] & 64) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[13] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[13] & 64) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[13] & 8) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[13] & 2) != 2) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[13] & 4) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[13] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[13] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[13] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[15] & 8) != 8) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[15] & 4) != 4) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[15] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[15] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[15] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[15] & 2) != 2) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[15] & 32) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[15] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[4] & 8) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[4] & 4) != 4) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[4] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[4] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[4] & 2) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[4] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[4] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[4] & 16) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[18] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[18] & 4) != 4) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[18] & 8) != 8) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[18] & 2) != 2) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[18] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[18] & 32) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[18] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[18] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[27] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[27] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[27] & 8) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[27] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[27] & 4) != 4) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[27] & 2) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[27] & 1) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[27] & 64) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[8] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[8] & 1) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[8] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[8] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[8] & 2) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[8] & 8) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[8] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[8] & 4) != 4) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[26] & 4) != 4) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[26] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[26] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[26] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[26] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[26] & 8) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[26] & 1) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[26] & 2) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[6] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[6] & 16) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[6] & 4) != 4) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[6] & 2) != 2) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[6] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[6] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[6] & 8) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[6] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[1] & 32) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[1] & 4) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[1] & 8) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[1] & 16) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[1] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[1] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[1] & 2) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[1] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[31] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[31] & 8) != 8) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[31] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[31] & 4) != 4) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[31] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[31] & 2) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[31] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[31] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[3] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[3] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[3] & 8) != 8) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[3] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[3] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[3] & 4) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[3] & 2) != 2) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[3] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[14] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[14] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[14] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[14] & 2) != 2) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[14] & 4) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[14] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[14] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[14] & 8) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[12] & 1) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[12] & 4) != 4) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[12] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[12] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[12] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[12] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[12] & 2) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[12] & 8) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[23] & 2) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[23] & 4) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[23] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[23] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[23] & 16) != 16) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[23] & 64) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[23] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[23] & 8) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[20] & 1) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[20] & 4) != 4) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[20] & 32) != 32) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[20] & 2) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[20] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[20] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[20] & 16) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[20] & 8) != 8) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[0] & 32) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[0] & 64) != 64) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[0] & 1) != 1) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[0] & 4) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[0] & 16) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[0] & 2) != 2) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[0] & 128) != 0) { printf("Failed!"); _exit(1); }
	if ((flag_attempt[0] & 8) != 8) { printf("Failed!"); _exit(1); }
	
	printf("Success!!!");
	_exit(1);
}

