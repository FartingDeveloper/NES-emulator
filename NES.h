#pragma once
#include "CPU.h"

class NES
{
	const int memorySize = 65536;

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

