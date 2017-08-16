#pragma once
#include "types.h"
#include "Memory.h"

class PPU
{
	Memory * memory;
	byte OAM[256];

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
public:
	PPU(Memory * memory);
};

