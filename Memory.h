#pragma once
#include "types.h"
#include "Mapper.h"
#include "PPU.h"

class Memory
{
	byte RAM[65536];
	const word stack = 0x100;

	Mapper * mapper;
	PPU * ppu;
public:
	Memory(Mapper *&mapper, PPU *&ppu);

	word popWord(byte &addr);
	void pushWord(byte &addr, word value);

	byte pop(byte &addr);
	void push(byte &addr, byte value);
	
	word readWord(word addr);
	byte read(word addr);
	void write(word addr, byte value);

	void setMapper(Mapper * mapper);
	void reset();
};

