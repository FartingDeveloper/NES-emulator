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

bool NES::loadROM(byte * bytes, int size)
{
	reset();
	delete mapper;
	
	std::string name;
	for (int i = 0; i < 3; i++) {
		name += bytes[i];
	}

	if (name != "NES") return false;

	switch (bytes[3])
	{
	case 0:
		mapper = new NROM(bytes, size);
		break;
	default:
		return false;
	}
	return true;
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

