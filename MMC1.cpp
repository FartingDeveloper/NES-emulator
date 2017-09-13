#include "MMC1.h"

MMC1::MMC1(byte * bytes, int size):Memory(bytes, size)
{
}

void MMC1::write(word addr, byte value)
{
	switch (addr & 0x8000)
	{
	case 0x8000:
	case 0x9000:

		break;
	case 0xA000:
	case 0xB000:

		break;
	case 0xC000:
	case 0xD000:

		break;
	case 0xE000:
	case 0xF000:

		break;
	}
}

void MMC1::control(byte value)
{
	int mask = 3;
	
}
