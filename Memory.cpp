#include "Memory.h"



Memory::Memory()
{
}

word Memory::popWord(byte & addr)
{
	word result = RAM[stack + addr];
	addr--;
	result <<= 8;
	result |= RAM[stack + addr];
	addr--;
	return result;
}

void Memory::pushWord(byte & addr, word value)
{
	RAM[stack + addr] = value & 0x00FF;
	addr++;
	RAM[stack + addr] = (value & 0xFF00) >> 8;
	addr++;
}

byte Memory::pop(byte & addr)
{
	byte result = RAM[stack + addr];
	addr--;
	return result;
}

void Memory::push(byte & addr, byte value)
{
	RAM[stack + addr] = value;
	addr++;
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

