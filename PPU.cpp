#include "PPU.h"


PPU::PPU()
{
	VRAM = new Memory(vRamSize);
	OAM = new Memory(oamSize);
	OAMADDR = 0;
}

void PPU::step()
{
	tick();

	bool preScanline = scanline == 261;
	bool visibleScanline = scanline < 240;
	bool visibleCycle = cycle > 0 && cycle < 257;
	bool fetchScanlineCycle = cycle > 320 && cycle < 337;

	if (PPUMASK.showBackground || PPUMASK.showSprite) { //render
		if (visibleScanline && visibleCycle) {
			renderPixel();
		}
		if ((visibleScanline || preScanline) && (visibleCycle || fetchScanlineCycle)) {
			switch (cycle % 8)
			{
			case 1:
				fetchNameTableByte();
				break;
			case 3:
				fetchAttributeTableByte();
				break;
			case 5:
				fetchLowTileByte();
				break;
			case 7:
				fetchHightTileByte();
				break;
			case 0:
				storeTileData();
				break;
			}
		}
		if (cycle == 256) {
			incrementY();
		}
		if (cycle == 257) {
			copyX();
		}
		if (preScanline && (cycle >= 280 && cycle <= 304)) {
			copyY();
		}
		if ((visibleScanline || preScanline) && (cycle % 8 == 0)) {
			incrementX();
		}
	}

	if (scanline == 241 && cycle == 1) PPUSTATUS.vBlank = 1; //Image ready
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
	cycle++;
	if (cycle > 340) {
		cycle = 0;
		scanline++;
		if (scanline > 261) scanline = 0;
	}
}

void PPU::fetchNameTableByte()
{
	word addr = 0x2000 | (v & 0x0FFF); //Tile address
	nameTableByte = VRAM->read(addr);
}

void PPU::fetchAttributeTableByte()
{
	word addr = 0x23C0 | (v & 0x0C00) | ((v >> 4) & 0x38) | ((v >> 2) & 0x07); //Attribute address
	attributeTableByte = VRAM->read(addr);

	byte mask = 3;
	byte topLeft = attributeTableByte & mask;
	byte topRight = (attributeTableByte >> 2) & mask;
	byte bottomLeft = (attributeTableByte >> 4) & mask;
	byte bottomRight = (attributeTableByte >> 6) & mask;
	attributeTableByte = (topLeft << 0) | (topRight << 2) | (bottomLeft << 4) | (bottomRight << 6);
}

void PPU::fetchLowTileByte()
{
	word y = (v >> 12) & 0x0007; //Fine Y offset, the row number within a tile
	word table = 0x1000 * PPUCTRL.backgroundTileAddress; //Background pattern table address (0: $0000; 1: $1000)
	word addr = table + nameTableByte + y;
	lowTileByte = VRAM->read(addr);
}

void PPU::fetchHightTileByte()
{
	word y = (v >> 12) & 0x0007; //Fine Y offset, the row number within a tile
	word table = 0x1000 * PPUCTRL.backgroundTileAddress; //Background pattern table address (0: $0000; 1: $1000)
	word addr = table + nameTableByte + y;
	lowTileByte = VRAM->read(addr + 8);
}

void PPU::storeTileData() //Turn the attribute data and the pattern table data into palette indices
{

}

void PPU::incrementX()
{
	if ((v & 0x001F) == 31) {// if coarse X == 31
		v &= ~0x001F;  // coarse X = 0
		v ^= 0x0400; // switch horizontal nametable
	}
	else {
		v += 1;  // increment coarse X
	}
}

void PPU::incrementY()
{
	if ((v & 0x7000) != 0x7000) { // if fine Y < 7
		v += 0x1000; // increment fine Y
	}
	else {
		v &= ~0x7000; // fine Y = 0
		int y = (v & 0x03E0) >> 5; // let y = coarse Y
		if (y == 29) {
			y = 0;  // coarse Y = 0
			v ^= 0x0800; // switch vertical nametable
		}
		else if (y == 31) {
			y = 0; // coarse Y = 0, nametable not switched
		}
		else {
			y += 1; // increment coarse Y
		}
		v = (v & ~0x03E0) | (y << 5); // put coarse Y back into v
	}
}

void PPU::copyX()
{
	//v: ....F.. ...EDCBA = t: ....F.. ...EDCBA
	v = (v & 0xFBE0) | (t & 0x041F);
}

void PPU::copyY()
{
	// v: .IHGF.ED CBA..... = t: .IHGF.ED CBA.....
	v = (v & 0x841F) | (t & 0x7BE0);
}

void PPU::writePPUCTRL(byte value)
{
	int mask = 3;
	PPUCTRL.nametableAddress = value & mask;
	mask = 1;
	PPUCTRL.incrementMode = value & (mask << 2);
	PPUCTRL.spriteTileAddress = value & (mask << 3);
	PPUCTRL.backgroundTileAddress = value & (mask << 4);
	PPUCTRL.spriteSize = value & (mask << 5);
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
	PPUMASK.showLeftBackground= value & (mask << 1);
	PPUMASK.showLeftSprite = value & (mask << 2);
	PPUMASK.showBackground = value & (mask << 3);
	PPUMASK.showSprite = value & (mask << 4);
	PPUMASK.red = value & (mask << 5);
	PPUMASK.green = value & (mask << 6);
	PPUMASK.blue = value & (mask << 7);
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
	OAM->write(OAMADDR, value);
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
	VRAM->write(v, value);

	if (PPUCTRL.incrementMode) {
		v += 32;
	}
	else {
		v += 1;
	}
}

inline void PPU::writeOAMDMA(byte value)
{
	OAM->write(OAMDMA, value);
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
	return OAM->read(OAMADDR);
}

inline byte PPU::readPPUDATA()
{
	byte result = VRAM->read(v);

	if (PPUCTRL.incrementMode) {
		v += 32;
	}
	else {
		v += 1;
	}
	return result;
}
