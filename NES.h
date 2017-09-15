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
	Controller * controllerOne;
	Controller * controllerTwo;
public:
	NES();

	void run();
	bool loadROM(byte *bytes, int size);

	bool getDrawFlag();
	COLORREF * getScreenBuffer();
	int getScreenWidth();
	int getScreenHeight();

	void pressKey(bool controllerNumber, byte value);
	void releaseKey(bool controllerNumber, byte value);
private:
	void reset();
};

