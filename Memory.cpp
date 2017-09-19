#include "Memory.h"

Memory::Memory()
{
	memory = new byte[0];
}

Memory::Memory(int size)
{
	memory = new byte[size];
}

void Memory::init(byte * bytes, int size)
{
	delete[] memory;

	memory = new byte[size];

	for (int i = 0; i < size; i++) {
		memory[i] = bytes[i];
	}
}

byte Memory::read(word addr)
{
	return memory[addr];
}

void Memory::write(word addr, byte value)
{
	memory[addr] = value;
}
