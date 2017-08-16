#include "Memory.h"


Memory::Memory(Mapper *&mapper)
{
	this->mapper = mapper;
	RAM[4015] = 0x00;
	RAM[4017] = 0x00;
	for (int i = 0x4000; i <= 0x400F; i++) RAM[i] = 0x00;
}

word Memory::popWord(byte & addr)
{
	word result = RAM[stack + addr % 0x0800];
	addr--;
	result <<= 8;
	result |= RAM[stack + addr % 0x0800];
	addr--;
	return result;
}

void Memory::pushWord(byte & addr, word value)
{
	RAM[stack + addr % 0x0800] = value & 0x00FF;
	addr++;
	RAM[stack + addr % 0x0800] = (value & 0xFF00) >> 8;
	addr++;

}

byte Memory::pop(byte & addr)
{
	byte result = RAM[stack + addr % 0x0800];
	addr--;
	return result;

}

void Memory::push(byte & addr, byte value)
{
	RAM[stack + addr % 0x0800] = value;
	addr++;
}

word Memory::readWord(word &addr)
{
	switch (addr & 0xF000)
	{
	case 0x0000:
	case 0x1000:
		word result = RAM[addr % 0x0800];
		addr++;
		result <<= 8;
		result |= RAM[addr % 0x0800];
		return result;
	case 0x2000:
	case 0x3000:
		word result = RAM[0x2000 + addr % 0x0008];
		addr++;
		result <<= 8;
		result |= RAM[0x2000 + addr % 0x0008];
		return result;
	case 0x4000:
		if (addr < 0x4020) {
			word result = RAM[addr];
			addr++;
			result <<= 8;
			result |= RAM[addr];
			return result;
		}
		//else mapper
		break;
	}
	return -1;
}

void Memory::writeWord(word &addr, word value)
{
	switch (addr & 0xF000)
	{
	case 0x0000:
	case 0x1000:
		RAM[addr % 0x0800] = value & 0x00FF;
		addr++;
		RAM[addr % 0x0800] = (value & 0xFF00) >> 8;
		break;
	case 0x2000:
	case 0x3000:
		RAM[0x2000 + addr % 0x0008] = value & 0x00FF;
		addr++;
		RAM[0x2000 + addr % 0x0008] = (value & 0xFF00) >> 8;
		break;
	case 0x4000:
		if (addr < 0x4020) {
			RAM[addr] = value & 0x00FF;
			addr++;
			RAM[addr] = (value & 0xFF00) >> 8;
		}
		//else mapper
		break;
	}
}

byte Memory::read(word addr)
{
	switch (addr & 0xF000)
	{
	case 0x0000:
	case 0x1000:
		return RAM[addr % 0x0800];
	case 0x2000:
	case 0x3000:
		return RAM[0x2000 + addr % 0x0008];
	case 0x4000:
		if (addr < 0x4020) return RAM[addr];
		//else mapper
		break;
	}
	return -1;
}

void Memory::write(word addr, byte value)
{
	switch (addr & 0xF000)
	{
	case 0x0000:
	case 0x1000:
		RAM[addr % 0x0800] = value;
		break;
	case 0x2000:
	case 0x3000:
		RAM[0x2000 + addr % 0x0008] = value;
		break;
	case 0x4000:
		if(addr < 0x4020) RAM[addr] = value;
		//else mapper
		break;
	}
}

