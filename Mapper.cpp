#include "Mapper.h"

Mapper::Mapper(byte * bytes, int size)
{
	this->size = size;
	for (int i = 0; i < size; i++) {
		ROM[i] = bytes[i];
	}
}
