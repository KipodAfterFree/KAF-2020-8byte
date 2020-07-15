#include "unpacking.h"

void init_unpacking(BYTE* codeStart, const DWORD sectionLength)
{
	gCodeStart = codeStart;
	gSectionLength = sectionLength;
	main_unpacking_loop();
}

void main_unpacking_loop()
{
}
