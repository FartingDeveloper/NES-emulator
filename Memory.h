#pragma once
#include "types.h"

class Memory {
protected:
	byte * memory;
public:
	Memory(int size);
	Memory(byte * bytes, int size); //for mappers
	virtual byte read(word addr);
	virtual void write(word addr, byte value);
};