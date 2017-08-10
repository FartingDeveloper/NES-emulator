#include "Memory.h"



Memory::Memory()
{
}

word Memory::readWord(word &addr)
{
	word result = RAM[addr];
	addr++;
	result <<= 8;
	result |= RAM[addr];
	return result;
}

void Memory::writeWord(word &addr, word value)
{
	RAM[addr] = value & 0x00FF;
	addr++;
	RAM[addr] = (value & 0xFF00) >> 8;
}

byte Memory::read(word addr)
{
	return RAM[addr];
}

void Memory::write(word addr, byte value)
{
	RAM[addr] = value;
}

