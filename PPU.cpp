#include "PPU.h"


PPU::PPU()
{
	OAMADDR = 0;
	PPUSCROLL = 0;
	PPUADDR = 0;
	OAMDMA = 0;
}

void PPU::step()
{
	tick();


}

byte PPU::readRegister(word addr)
{
	switch (addr)
	{
	case 0x2002:
		return readPPUSTATUS();
	case 0x2004:
		return oam->read(OAMADDR);
	case 0x2007:
		return vram->read(PPUADDR);
	default:
		break;
	}
	return -1;
}

void PPU::writeRegister(word addr, byte value)
{
	switch (addr)
	{
	case 0x2000:
		writePPUCTRL(value);
		break;
	case 0x2001:
		writePPUMASK(value);
		break;
	case 0x2003:
		OAMADDR = value;
		break;
	case 0x2004:
		oam->write(OAMADDR, value);
		break;
	case 0x2006:
		PPUADDR |= value;
		PPUADDR <<= 8;
		break;
	case 0x2007:
		vram->write(PPUADDR, value);
		break;
	case 0x2014:
		oam->write(OAMADDR, value);
		OAMADDR++;
		break;
	default:
		break;
	}
}

void PPU::tick()
{
	if (cycle > 340) {
		scanline++;
		if (scanline > 261) scanline = 0;
	}
}

void PPU::writePPUCTRL(byte value)
{
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

void PPU::writePPUMASK(byte value)
{
	int mask = 1;
	PPUMASK.greyscale = value & mask;
	PPUMASK.backgroundLeftColumnEnable = value & (mask << 1);
	PPUMASK.spriteLeftColumnEnable = value & (mask << 2);
	PPUMASK.backgroundEnable = value & (mask << 3);
	PPUMASK.spriteEnable = value & (mask << 4);
	mask = 7;
	PPUMASK.colorEmphasis = value & (mask << 5);
}

byte PPU::readPPUSTATUS()
{
	byte value = 0;
	int mask = 1;
	if (PPUSTATUS.spriteOverflow) value |= (mask << 5);
	if (PPUSTATUS.spriteZeroHit) value |= (mask << 6);
	if (PPUSTATUS.vBlank) value |= (mask << 7);
}
