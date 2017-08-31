#include "Memory.h"

Memory::Memory(int size)
{
	memory = new byte[size];
}

byte Memory::read(word addr)
{
	return memory[addr];
}

void Memory::write(word addr, byte value)
{
	memory[addr] = value;
}
