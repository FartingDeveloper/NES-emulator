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
			tile <<= 4;
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
			if(visibleScanline) evaluateSprite();
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

void PPU::renderPixel()
{
	int x = cycle - 1;
	int y = scanline;
	byte background = backgroundPixel();
	byte sprite = spritePixel();
	byte pixel;

	if (!PPUMASK.showLeftBackground && (x < 7)) {
		background = 0;
	}
	if (!PPUMASK.showLeftSprite && (x < 7)) {
		sprite = 0;
	}

	bool backgroundTransparency = background % 4;
	bool spriteTransparency = sprite % 4;

	if (!backgroundTransparency && !spriteTransparency) {
		pixel = 0;
	}
	else if (!backgroundTransparency && spriteTransparency) {
		pixel = sprite | 0x10;
	}
	else if (backgroundTransparency && !spriteTransparency) {
		pixel = background;
	}
	else{
		if (spriteIndexes[spriteCount] == 0 && x < 255) {
			PPUSTATUS.spriteZeroHit = 1;
		}
		if (spritePriorities[spriteCount]) {
			pixel = background;
		}
		else {
			pixel = sprite | 0x10;
		}
	}

	byte color = VRAM->read(0x3F00 + pixel);
	screenBuffer[y * 240 + x] = palette->transform(color % 64);
}

byte PPU::backgroundPixel()
{
	if (PPUMASK.showBackground) {
		int x = (cycle - 1) % 8;
		byte pixel = tile >> ((7 - x) * 4);
		return (pixel & 0x0F);
	}
	else return 0;
}

byte PPU::spritePixel()
{
	if (PPUMASK.showSprite) {
		for (int i = 0; i < 7; i++) {
			int offset = (cycle - 1) - spritePositions[i];
			if (offset >= 0 & offset < 8) {// in range
				spriteCount = i;
				byte pixel = spriteTiles[i] >> ((7 - offset) * 4);
				if (pixel % 4 == 0) continue; //if transparent
				return (pixel & 0x0F);
			}
		}
	}
	else {
		return 0;
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
	byte shift = ((v >> 4) & 4) | (v & 2);
	attributeTableByte = ((VRAM->read(addr) >> shift) & 3) << 2;
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
	for (int i = 0; i < 8; i++) {
		byte p1 = (lowTileByte & 0x80) >> 7;
		byte p2 = (hightTileByte & 0x80) >> 6;
		lowTileByte <<= 1;
		hightTileByte <<= 1;
		tile = attributeTableByte | p1 | p2;
		tile <<= 4;
	}
}

void PPU::evaluateSprite()
{
	byte h;
	if (PPUCTRL.spriteSize) {
		h = 16;
	} 
	else {
		h = 8;
	}
	int count = 0;

	for (int i = 0; i < 64; i++) {
		byte y = OAM->read(i * 4);
		byte index = OAM->read(i * 4 + 1);
		byte a = OAM->read(i * 4 + 2);
		byte x = OAM->read(i * 4 + 3);
		byte row = scanline - y;

		if (row >= 0 && row < h) { //in range
			spriteTiles[count] = fetchSpriteData(h, row, index, a);
			spritePositions[count] = x;
			spritePriorities[count] = (a >> 5) & 1;
			spriteIndexes[count] = i;
			count++;
		}
	}
	if (count > 8) {
		PPUSTATUS.spriteOverflow = 1;
	}
}

__int32 PPU::fetchSpriteData(byte h, byte row, byte index, byte a)
{
	__int32 tile = 0;
	word addr;
	if (PPUCTRL.spriteSize) {
		word table = 0x1000 * (index & 1);
		word tileNumber = index >> 1;
		word offset = row;
		if (a & 0x80) offset = 15 - row; //Flip sprite vertically
		addr = table + tileNumber + row;
	}
	else {
		word table = 0x1000 * PPUCTRL.spriteTileAddress;
		word tileNumber = index >> 1;
		word offset = row;
		if (a & 0x80) offset = 7 - row; //Flip sprite vertically
		addr = table + tileNumber + row;
	}

	byte lowTileByte = VRAM->read(addr);
	byte hightTileByte = VRAM->read(addr + h);
	byte palette = (a & 3) << 2;

	if ((a << 1) & 0x80) { //Flip sprite horizontally
		for (int i = 0; i < 8; i++) {
			byte p1 = lowTileByte & 1;
			byte p2 = hightTileByte & 1;
			lowTileByte >>= 1;
			hightTileByte >>= 1;
			tile = palette | p1 | p2;
			tile <<= 4;
		}
	}
	else {
		for (int i = 0; i < 8; i++) {
			byte p1 = (lowTileByte & 0x80) >> 7;
			byte p2 = (hightTileByte & 0x80) >> 6;
			lowTileByte <<= 1;
			hightTileByte <<= 1;
			tile = palette | p1 | p2;
			tile <<= 4;
		}
	}
	return tile;
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
