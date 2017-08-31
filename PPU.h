#pragma once
#include "types.h"
#include "Memory.h"

class PPU
{
	const int vRamSize = 16383;
	const int oamSize = 256;

	Memory * VRAM;
	Memory  * OAM;

	struct {
		unsigned NMI : 1;
		unsigned masterSlave : 1;
		unsigned spriteSize : 1;
		unsigned backgroundTileAddress : 1;
		unsigned spriteTileAddress : 1;
		unsigned incrementMode : 1;
		unsigned nametableAddress : 2;
	} PPUCTRL;

	struct {
		unsigned blue : 1;
		unsigned green : 1;
		unsigned red : 1;
		unsigned showSprite : 1;
		unsigned showBackground : 1;
		unsigned showLeftSprite : 1;
		unsigned showLeftBackground : 1;
		unsigned greyscale : 1;
	} PPUMASK;

	struct {
		unsigned vBlank : 1;
		unsigned spriteZeroHit : 1;
		unsigned spriteOverflow : 1;
	} PPUSTATUS;

	word v; //current VRAM addr
	word t; //temporary VRAM addr

	byte x; // x scroll
	byte w; //first or second write toggle

	word OAMADDR;
	word OAMDMA;

	word tileAddress;
	word attrivuteAddress;

	byte nameTableByte;
	byte attributeTableByte;
	byte lowTileByte;
	byte hightTileByte;
	byte tile[8];

	int scanline;
	int cycle;
public:
	PPU();
	void step();
	byte readRegister(word addr);
	void writeRegister(word addr, byte value);
private:
	void tick();

	void renderPixel();
	void fetchNameTableByte();
	void fetchAttributeTableByte();
	void fetchLowTileByte();
	void fetchHightTileByte();
	void storeTileData();

	void incrementX();
	void incrementY();
	void copyX();
	void copyY();

	inline void writePPUCTRL(byte value);
	inline void writePPUMASK(byte value);
	inline void writePPUSCROLL(byte value);
	inline void writeOAMADDR(byte value);
	inline void writeOAMDATA(byte value);
	inline void writePPUADDR(byte value);
	inline void writePPUDATA(byte value);
	inline void writeOAMDMA(byte value);

	inline byte readPPUSTATUS();
	inline byte readOAMDATA();
	inline byte readPPUDATA();
};

