#pragma once
#include "Memory.h"

class OAM : Memory
{
	byte memory[256];
public:
	OAM();
	byte read(word addr);
	void write(word addr, byte value);
};

