#pragma once
#include "CPU.h"

class NES
{
	CPU * cpu;
	PPU * ppu;
	Memory * memory;
	Mapper * mapper;
public:
	NES();
	void run();
	void loadROM(byte *bytes, int size);
private:
	void reset();
};

