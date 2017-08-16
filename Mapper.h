#pragma once
#include "types.h"

class Mapper
{
	byte *ROM;
	int size;
public:
	Mapper(byte * bytes, int size);
};

