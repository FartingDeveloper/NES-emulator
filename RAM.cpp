#include "RAM.h"

RAM::RAM(int size, PPU *&ppu, Memory *&mapper, Controller *& controllerOne, Controller *& controllerTwo) :Memory(size)
{
	this->ppu = ppu;
	this->mapper = mapper;
	this->controllerOne = controllerOne;
	this->controllerTwo = controllerTwo;
	memory[4015] = 0x00;
	memory[4017] = 0x00;
	for (int i = 0x4000; i <= 0x400F; i++) memory[i] = 0x00;
}

word RAM::popWord(byte & addr)
{
	word result = memory[addr % 0x0800];
	addr--;
	result <<= 8;
	result |= memory[addr % 0x0800];
	addr--;
	return result;
}

void RAM::pushWord(byte & addr, word value)
{
	memory[addr % 0x0800] = value & 0x00FF;
	addr++;
	memory[addr % 0x0800] = (value & 0xFF00) >> 8;
	addr++;

}

byte RAM::pop(byte & addr)
{
	byte result = memory[addr % 0x0800];
	addr--;
	return result;

}

void RAM::push(byte & addr, byte value)
{
	memory[addr % 0x0800] = value;
	addr++;
}

word RAM::readWord(word addr)
{
	word result = read(addr);
	addr++;
	result <<= 8;
	result |= read(addr);
	return result;
}

byte RAM::read(word addr)
{
	switch (addr & 0xF000)
	{
	case 0x0000:
	case 0x1000:
		return memory[addr % 0x0800];
	case 0x2000:
	case 0x3000:
		return ppu->readRegister(0x2000 + addr % 0x0008);
	case 0x4000:
		switch (addr)
		{
		case 0x4016:
			return controllerOne->read();
		case 0x4017:
			return controllerTwo->read();
		}
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
		return mapper->read(addr);
	}
	return -1;
}

void RAM::write(word addr, byte value)
{
	switch (addr & 0xF000)
	{
	case 0x0000:
	case 0x1000:
		memory[addr % 0x0800] = value;
		break;
	case 0x2000:
	case 0x3000:
		ppu->writeRegister(0x2000 + addr % 0x0008, value);
		break;
	case 0x4000:
		switch (addr)
		{
		case 0x4014:
			ppu->writeRegister(0x2003, 0);
			word XX = 0;
			XX = value << 8;
			for (word i = XX; i < (XX | 0x00FF); i++) {
				value = read(i);
				ppu->writeRegister(addr, value);
			}
			break;
		case 0x4016:
			controllerOne->write(value);
			break;
		case 0x4017:
			controllerTwo->write(value);
			break;
		}
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

void RAM::setMapper(Memory * mapper)
{
	this->mapper = mapper;
}

void RAM::reset()
{
	this->mapper = nullptr;
	memory[4015] = 0x00;
	memory[4017] = 0x00;
	for (int i = 0x4000; i <= 0x400F; i++) memory[i] = 0x00;
}

