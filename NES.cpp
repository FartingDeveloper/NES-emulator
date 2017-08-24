#include "NES.h"


NES::NES()
{
	ppu = new PPU();
	memory = new RAM(ppu, mapper);
	cpu = new CPU(memory);
}

void NES::run()
{

}

