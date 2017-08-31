#pragma once
#include "types.h"

class Memory {
protected:
	byte * memory;
public:
	Memory(int size);
	byte read(word addr);
	void write(word addr, byte value);
};