#include "PPU.h"


PPU::PPU()
{
	OAMADDR = 0;
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
		return readOAMDATA();
	case 0x2007:
		return readPPUDATA();
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
		writeOAMADDR(value);
		break;
	case 0x2004:
		writeOAMDATA(value);
		break;
	case 0x2005:
		writePPUSCROLL(value);
		break;
	case 0x2006:
		writePPUADDR(value);
		break;
	case 0x2007:
		writePPUDATA(value);
		break;
	case 0x2014:
		writeOAMDMA(value);
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
	
	// t: ....BA.. ........ = d: ......BA
	word tmp = 0;
	tmp |= (value & 0x03) << 10;
	t |= tmp;
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

inline void PPU::writePPUSCROLL(byte value)
{
	if (w == 0) {
		//t: ....... ...HGFED = d: HGFED...
	    //x:              CBA = d : .....CBA
		//w : = 1
		t |= value >> 3;
		x = value & 0x08;
		w = 1;
	}
	else {
		//t: CBA..HG FED..... = d: HGFEDCBA
	    //w: = 0
		word tmp = 0;
		tmp = (value & 0x07) << 12;
		tmp |= (value & 0xF8) << 2;
		t |= tmp;
		w = 0;
	}
}

inline void PPU::writeOAMADDR(byte value)
{
	OAMADDR = value;
}

inline void PPU::writeOAMDATA(byte value)
{
	oam->write(OAMADDR, value);
	OAMADDR++;
}

inline void PPU::writePPUADDR(byte value)
{
	if (w == 0) {
		//t: .FEDCBA ........ = d: ..FEDCBA
	    //t: X...... ........ = 0
		//w : = 1
		t |= value & 0x3F << 8;
		t &= 0x7FFF;
		w = 1;
	}
	else {
	    //t: .......HGFEDCBA = d : HGFEDCBA
		//v = t
		//w : = 0
		t = value;
		v = t;
		w = 0;
	}
}

inline void PPU::writePPUDATA(byte value)
{
	vram->write(v, value);
}

inline void PPU::writeOAMDMA(byte value)
{
	oam->write(OAMDMA, value);
	OAMDMA++;
	if (OAMDMA == 255) OAMDMA = 0;
}

byte PPU::readPPUSTATUS()
{
	byte value = 0;
	int mask = 1;
	if (PPUSTATUS.spriteOverflow) value |= (mask << 5);
	if (PPUSTATUS.spriteZeroHit) value |= (mask << 6);
	if (PPUSTATUS.vBlank) value |= (mask << 7);

	//w:=0
	w = 0;
}

inline byte PPU::readOAMDATA()
{
	return oam->read(OAMADDR);
}

inline byte PPU::readPPUDATA()
{
	return vram->read(v);
}
