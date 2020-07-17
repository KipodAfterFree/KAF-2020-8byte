#include "packed_exe_section.h"
#include <iostream>

#define FILLER_SIZE 5 * 1024 * 1024 // 10MB


#pragma section(".awsm", execute, read)
#pragma comment(linker, "/SECTION:.awsm,ER")

__declspec(allocate(".awsm")) unsigned char bigarray[FILLER_SIZE] = { 0x90 };

#pragma code_seg(".awsm")
int _tmain(int argc, char* argv[]) {
	char flag[16];
	flag[0] = 'a';
	flag[1] = 'b';
	flag[2] = 'c';
	flag[3] = 'd';
	flag[4] = 'e';
	flag[5] = 'f';
	flag[6] = 'g';
	flag[7] = 'h';
	flag[8] = 'i';
	flag[9] = 'j';
	flag[10] = 'k';
	flag[11] = 'l';
	flag[12] = 'm';
	flag[13] = 'n';
	flag[14] = 'o';
	flag[15] = 'p';

 	if (flag[2] == 'h') {
		flag[1] = 'g';
		// printf("Success!!!");
	}
	else if (flag[4] == 'd') {
		flag[1] = 'b';
	}
	else {
		flag[1] = 'b';
	}
	
	test_function();
	return 0;
}

void test_function() { printf("hello world!!!!"); }

