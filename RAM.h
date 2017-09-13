#pragma once
#include "types.h"
#include "Mapper.h"
#include "PPU.h"

class RAM : public Memory
{
	byte * memory;

	Memory * mapper;
	PPU * ppu;
public:
	RAM(int size, PPU *&ppu, Memory *&mapper);

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

