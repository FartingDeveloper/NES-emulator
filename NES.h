#pragma once
#include "CPU.h"

class NES
{
	CPU *cpu;
	Memory *memory;
	Mapper * mapper;
public:
	NES();
	void run();
	void loadROM(byte *bytes, int size);
};

