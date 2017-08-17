#include "NES.h"


NES::NES()
{
	memory = new Memory(mapper);
	cpu = new CPU(memory);
}

