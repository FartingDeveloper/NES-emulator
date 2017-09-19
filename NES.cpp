#include "NES.h"
#include "NROM.h"

NES::NES()
{
	ppu = new PPU();
	controllerOne = new Controller();
	controllerTwo = new Controller();
	mapper = new Memory();
	ram = new RAM(memorySize, ppu, mapper, controllerOne, controllerTwo);
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
	
	byte type = (bytes[6] & 0xF0 >> 4) | bytes[7] & 0xF0;

	switch (type)
	{
	case 0:
		mapper = new NROM(bytes, size); //NROM
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

void NES::pressKey(bool controllerNumber, byte button)
{
	if (controllerNumber) controllerOne->setButton(button, true);
	else controllerTwo->setButton(button, true);
}

void NES::releaseKey(bool controllerNumber, byte button)
{
	if (controllerNumber) controllerOne->setButton(button, false);
	else controllerTwo->setButton(button, false);
}

void NES::reset()
{
	cpu->reset();
	ppu->reset();
	ram->reset();
}

