#pragma once
#include "types.h"
#include "PPU.h"
#include "Controller.h"

class RAM : public Memory
{
	Memory * mapper;
	PPU * ppu;
	Controller * controllerOne;
	Controller * controllerTwo;
public:
	RAM(int size, PPU *&ppu, Controller *& controllerOne, Controller *& controllerTwo);

	word popWord(byte &addr);
	void pushWord(byte &addr, word value);

	byte pop(byte &addr);
	void push(byte &addr, byte value);
	
	word readWord(word addr);
	byte read(word addr);
	void write(word addr, byte value);

	void setMapper(Memory * mapper);
	void reset();
};

