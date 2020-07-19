#pragma once

#ifndef _PACKED_EXE_SECTION_H
#define _PACKED_EXE_SECTION_H
int _tmain(int, char*[]);
void test_function();

template <size_t length>
constexpr size_t static_len(const char(&str)[length]) {
	return length - 1;
}

#endif