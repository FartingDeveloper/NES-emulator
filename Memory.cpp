#include "Memory.h"

Memory::Memory(int size)
{
	memory = new byte[size];
}

Memory::Memory(byte * bytes, int size)
{
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
