#pragma once
#include "types.h"

class Memory
{
	byte RAM[65536];
	const word stack = 0x100;
public:
	Memory();

	word popWord(byte &addr);
	void pushWord(byte &addr, word value);

	byte pop(byte &addr);
	void push(byte &addr, byte value);

	word readWord(word &addr);
	void writeWord(word &addr, word value);

	byte read(word addr);
	void write(word addr, byte value);
};

