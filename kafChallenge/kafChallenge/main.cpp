#include "main.h"
#include <windows.h>
#include <iostream>

int main(int argc, char* argv[]) {
	InitiateGreeting();
}

void InitiateGreeting() {
	std::cout 
		<< "**********SOFTWARE PACKER 9000**********" << std::endl << std::endl
		<< "I have packed an important executable," << std::endl
		<< "are you able to tell me what it does?" << std::endl << std::endl
		<< "****************************************"	<< std::endl;
}