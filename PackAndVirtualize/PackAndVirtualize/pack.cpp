#include "pack.h"

static inline BYTE rotl(BYTE n, int c)
{
	const unsigned int mask = (sizeof(n) - 1);

	// assert ( (c<=mask) &&"rotate by type width or more");
	c &= mask;
	return (n << c) | (n >> ((-c) & mask));
}

static inline BYTE rotr(BYTE n, int c)
{
	const unsigned int mask = (sizeof(n) - 1);

	// assert ( (c<=mask) &&"rotate by type width or more");
	c &= mask;
	return (n >> c) | (n << ((-c) & mask));
}

volatile BYTE huge_packing_function(BYTE initalVal)
{
	return pack_1(pack_4(pack_3(pack_1(pack_4(pack_2(pack_2(pack_1(initalVal) + 12) - 13) + 20) - 15) + 21) - 3) + 13);
}

volatile BYTE huge_unpacking_function(BYTE initialVal) {
	return rev_pack_1(rev_pack_2(rev_pack_2(rev_pack_4(rev_pack_1(rev_pack_3(rev_pack_4(rev_pack_1(initialVal) - 13) + 3) - 21) + 15) - 20) + 13) - 12);
}

volatile inline BYTE pack_1(BYTE initialVal)
{
	// (((initialVal << 10) ^ 0b00110101 + 2) >> 5) + 10) << 10
	return rotl(rotr(rotl(initialVal, 5) + 2, 5) + 10, 7) ^ 0b00110101;
}

volatile inline BYTE pack_2(BYTE initialVal)
{
	return rotr(rotl((rotl(initialVal ^ 0b11001010, 61) + 13), 5) + 20, 4);
}

volatile inline BYTE pack_3(BYTE initialVal)
{
	// (((((initialVal - 5) >> 10 + 5) << 5) >> 10 - 10) >> 5 - 2) >> 4
	return rotr(rotr(rotr(rotl(rotr(initialVal - 5, 10) + 5, 5), 10) - 10, 5) - 2, 4) ^ 0b1110101;
}

volatile inline BYTE pack_4(BYTE initialVal)
{
	// ((((((initialVal - 12) >> 13 + 6) >> 18) << 14 - 9) >> 1 - 6) << 31) ^ 0b10101010
	return rotl(rotr(rotl(rotr(rotr(initialVal - 12, 13) + 6, 18), 14) - 9, 1) - 6, 31) ^ 0b10101010;
}

volatile inline BYTE rev_pack_1(BYTE initialVal)
{
	// initialVal << 10
	return rotr((rotl(rotr(initialVal ^ 0b00110101, 7) - 10, 5) - 2), 5);
}

volatile inline BYTE rev_pack_2(BYTE initialVal)
{
	return rotr((rotr(rotl(initialVal, 4) - 20, 5) - 13), 61) ^ 0b11001010;
}

volatile inline BYTE rev_pack_3(BYTE initialVal)
{
	// (initialVal - 5)
	return rotl(rotr(rotl(rotl(rotl(initialVal ^ 0b1110101, 4) + 2, 5) + 10, 10), 5) - 5, 10) + 5;
}

volatile inline BYTE rev_pack_4(BYTE initialVal)
{
	// initialVal - 12
	return rotl(rotl(rotr(rotl(rotr(initialVal ^ 0b10101010, 31) + 6, 1) + 9, 14), 18) - 6, 13) + 12;
}


