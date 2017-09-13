#include "NES.h"


NES::NES()
{
	ppu = new PPU();
	ram = new RAM(memorySize, ppu, mapper);
	cpu = new CPU(ram);
}

void NES::run()
{
	int cycles = cpu->step();
	for (int i = 0; i < cycles * 3; i++) {
		ppu->step();
	}
}

void NES::loadROM(byte * bytes, int size)
{
	reset();
	delete mapper;
	
}

bool NES::getDrawFlag()
{
	return ppu->getDrawFlag();
}

COLORREF * NES::getScreenBuffer()
{
	return ppu->getScreenBuffer();
}

int NES::getScreenWidth()
{
	return ppu->getScreenWidth();
}

int NES::getScreenHeight()
{
	return ppu->getScreenHeight();
}

void NES::reset()
{
	cpu->reset();
	ppu->reset();
	ram->reset();
}

