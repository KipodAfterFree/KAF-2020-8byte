#include "packed_exe_section.h"
#include <iostream>
#pragma section(".awsm", execute, read)
#pragma comment(linker, "/SECTION:.awsm,ER")

#pragma code_seg(".awsm")
int _tmain(int argc, char* argv[]) {
	std::cout << "Hello world!" << std::endl;
	test_function();

	return 0;
}

void test_function() { printf("hello world!!!!"); }