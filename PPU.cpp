#include "PPU.h"


PPU::PPU(Memory * memory)
{
	this->memory = memory;
}

byte PPU::readRegister(word addr)
{
	switch (addr)
	{
	default:
		break;
	}
	return byte();
}

void PPU::writeRegister(word addr, byte value)
{
	switch (addr)
	{
	default:
		break;
	}
}

void PPU::updatePPUCTRL()
{
	byte value = memory->read(0x2000);
	int mask = 3;
	PPUCTRL.nameTable = value & mask;
	mask = 1;
	PPUCTRL.incrementMode = value & (mask << 2);
	PPUCTRL.spriteTile = value & (mask << 3);
	PPUCTRL.backgroundTile = value & (mask << 4);
	PPUCTRL.spriteHeight = value & (mask << 5);
	PPUCTRL.masterSlave = value & (mask << 6);
	PPUCTRL.NMI = value & (mask << 7);
}

void PPU::updatePPUMASK()
{
	byte value = memory->read(0x2001);
	int mask = 1;
	PPUMASK.greyscale = value & mask;
	PPUMASK.backgroundLeftColumnEnable = value & (mask << 1);
	PPUMASK.spriteLeftColumnEnable = value & (mask << 2);
	PPUMASK.backgroundEnable = value & (mask << 3);
	PPUMASK.spriteEnable = value & (mask << 4);
	mask = 7;
	PPUMASK.colorEmphasis = value & (mask << 5);
}

void PPU::updatePPUSTATUS()
{
	byte value = memory->read(0x2002);
	int mask = 1;
	PPUSTATUS.spriteOverflow = value & (mask << 5);
	PPUSTATUS.spriteZeroHit = value & (mask << 6);
	PPUSTATUS.vBlank = value & (mask << 7);
}
