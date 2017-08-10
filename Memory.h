#pragma once
#include "types.h"

class Memory
{
	byte RAM[65536];
public:
	Memory();
	word readWord(word &addr);
	void writeWord(word &addr, word value);

	byte read(word addr);
	void write(word addr, byte value);
};

