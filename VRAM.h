#pragma once
#include "Memory.h"

class VRAM : Memory
{
	byte memory[16383];
public:
	VRAM();
	byte read(word addr);
	void write(word addr, byte value);
};

