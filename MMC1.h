#pragma once
#include "Mapper.h"

class MMC1: public Mapper
{
public:
	MMC1(byte * bytes, int size);

	word readWord(word &addr);

	byte read(word addr);
	void write(word addr, byte value);

	void control(byte value);
};

