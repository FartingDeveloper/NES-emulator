#pragma once
#include "Memory.h"

class NROM: public Memory
{
public:
	NROM(byte * bytes, int size);
};

