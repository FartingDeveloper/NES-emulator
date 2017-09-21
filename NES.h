#pragma once
#include "CPU.h"

class NES
{
	const int memorySize = 65536;

	CPU * cpu;
	PPU * ppu;
	RAM * ram;
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

	void pressKey(bool controllerNumber, byte button);
	void releaseKey(bool controllerNumber, byte button);
private:
	void reset();
};

