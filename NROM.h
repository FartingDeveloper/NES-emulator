#pragma once
#include "Memory.h"

class NROM: public Memory
{
	int size;
public:
	NROM(byte * bytes, int size);
	virtual byte read(word addr);
};

