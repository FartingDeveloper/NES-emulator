#pragma once
#include "CPU.h"
#include "NROM.h"
#include <string>

class NES
{
	const int memorySize = 65536;

	CPU * cpu;
	PPU * ppu;
	RAM * ram;
	Memory * mapper;
public:
	NES();

	void run();
	bool loadROM(byte *bytes, int size);

	bool getDrawFlag();
	COLORREF * getScreenBuffer();
	int getScreenWidth();
	int getScreenHeight();
private:
	void reset();
};

