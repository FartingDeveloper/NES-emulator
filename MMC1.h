#pragma once
#include "Mapper.h"

class MMC1: public Mapper
{
public:
	MMC1(byte * bytes, int size);
	void write(word addr, byte value);
	byte read(word addr);
	void control(byte value);
};

