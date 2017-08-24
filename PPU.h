#pragma once
#include "types.h"
#include "VRAM.h"
#include "OAM.h"

class PPU
{
	VRAM * vram;
	OAM  * oam;
	struct {
		unsigned NMI : 1;
		unsigned masterSlave : 1;
		unsigned spriteHeight : 1;
		unsigned backgroundTile : 1;
		unsigned spriteTile : 1;
		unsigned incrementMode : 1;
		unsigned nameTable : 2;
	} PPUCTRL;

	struct {
		unsigned colorEmphasis : 3;
		unsigned spriteEnable : 1;
		unsigned backgroundEnable : 1;
		unsigned spriteLeftColumnEnable : 1;
		unsigned backgroundLeftColumnEnable : 1;
		unsigned greyscale : 1;
	} PPUMASK;

	struct {
		unsigned vBlank : 1;
		unsigned spriteZeroHit : 1;
		unsigned spriteOverflow : 1;
	} PPUSTATUS;

	word OAMADDR;
	word PPUSCROLL;
	word PPUADDR;
	word OAMDMA;

	int scanline;
	int cycle;
public:
	PPU();
	void step();
	byte readRegister(word addr);
	void writeRegister(word addr, byte value);
private:
	void tick();

	inline void writePPUCTRL(byte value);
	inline void writePPUMASK(byte value);
	inline byte readPPUSTATUS();
};

