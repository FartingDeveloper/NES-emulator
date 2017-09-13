#pragma once
#include "CPU.h"

class NES
{
	const int memorySize = 65536;

	CPU * cpu;
	PPU * ppu;
	RAM * ram;
	Mapper * mapper;
public:
	NES();
	void run();
	void loadROM(byte *bytes, int size);
	bool getDrawFlag();
	COLORREF * getScreenBuffer();
	int getScreenWidth();
	int getScreenHeight();
private:
	void reset();
};

