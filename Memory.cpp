#include "Memory.h"


Memory::Memory(Mapper *&mapper, PPU *&ppu)
{
	this->mapper = mapper;
	this->ppu = ppu;
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

word Memory::readWord(word addr)
{
	word result = read(addr);
	addr++;
	result <<= 8;
	result |= read(addr);
	return result;
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
		return ppu->readRegister(addr);
	case 0x6000:
	case 0x7000:
	case 0x8000:
	case 0x9000:
	case 0xA000:
	case 0xB000:
	case 0xC000:
	case 0xD000:
	case 0xE000:
	case 0xF000:
		return mapper->read(addr);
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
		ppu->writeRegister(addr, value);
		break;
	case 0x6000:
	case 0x7000:
	case 0x8000:
	case 0x9000:
	case 0xA000:
	case 0xB000:
	case 0xC000:
	case 0xD000:
	case 0xE000:
	case 0xF000:
		mapper->write(addr, value);
		break;
	}
}

void Memory::setMapper(Mapper * mapper)
{
	this->mapper = mapper;
}

void Memory::reset()
{
	this->mapper = nullptr;
	RAM[4015] = 0x00;
	RAM[4017] = 0x00;
	for (int i = 0x4000; i <= 0x400F; i++) RAM[i] = 0x00;
}

