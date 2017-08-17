#pragma once
#include "types.h"

class Mapper
{
protected:
	byte *ROM;
	int size;

	int header;
public:
	Mapper(byte * bytes, int size);

	virtual word readWord(word &addr) = 0;
	virtual void writeWord(word &addr, word value) = 0;

	virtual byte read(word addr) = 0;
	virtual void write(word addr, byte value) = 0;
};

