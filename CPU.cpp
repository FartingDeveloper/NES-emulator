#include "CPU.h"



CPU::CPU()
{
}

void CPU::executeOpcode(byte opcode)
{
	switch (opcode & 0xE0)
	{
	case 0x00: {
		break;
	}
	case 0x01: {
		byte operand = indexedInderect();
		ORA(operand);
		break;
	}
	case 0x05: {
		byte operand = zeropage();
		ORA(operand);
		break;
	}
	case 0x06: {
		byte operand = zeropage();
		ASL(operand);
		break;
	}
	case 0x08: {
		PHP();
		break;
	}
	case 0x09: {
		byte operand = immediate();
		ORA(operand);
		break;
	}
	case 0x0A: {
		ASL(A);
		break;
	}
	case 0x0D: {
		byte operand = absolute();
		ORA(operand);
		break;
	}
	case 0x0E: {
		byte operand = absolute();
		ASL(operand);
		break;
	}
	case 0x10: {
		relative();
		return;
	}
	case 0x11: {
		byte operand = inderectIndexed();
		ORA(operand);
		break;
	}
	case 0x15: {
		byte operand = zeropageX();
		ORA(operand);
		break;
	}
	case 0x16: {
		byte operand = zeropageX();
		ASL(operand);
		break;
	}
	case 0x18: {
		CLC();
		break;
	}
	case 0x19: {
		byte operand = absoluteY();
		ORA(operand);
		break;
	}
	case 0x1D: {
		byte operand = absoluteX();
		ORA(operand);
		break;
	}
	case 0x1E: {
		byte operand = absoluteX();
		ASL(operand);
		break;
	}
	case 0x20: {
		JSR();
		return;
	}
	case 0x21: {
		byte operand = indexedInderect();
		AND(operand);
		break;
	}
	case 0x24: {

		break;
	}
	default:
		break;
	}
	PC++;
}

inline byte CPU::immediate()
{
	PC++;
	byte operand = memory->read(PC);
	return operand;
}

inline byte CPU::absolute()
{
	PC++;
	word operandAddr = memory->readWord(PC);
	byte operand = memory->read(operandAddr);
	return operand;
}

inline byte CPU::absoluteX()
{
	PC++;
	word operandAddr = memory->readWord(PC) + X;
	byte operand = memory->read(operandAddr);
	return operand;
}

inline byte CPU::absoluteY()
{
	PC++;
	word operandAddr = memory->readWord(PC) + Y;
	byte operand = memory->read(operandAddr);
	return operand;
}

inline byte CPU::indexedInderect()
{
	PC++;
	word operandAddr = (X + memory->read(PC)) & 0x00FF;
	byte operand = memory->read(operandAddr);
	return operand;
}

inline byte CPU::inderectIndexed()
{
	PC++;
	word operandAddr = memory->read(PC);
	operandAddr = memory->readWord(operandAddr) + Y;
	byte operand = memory->read(operandAddr);
	return operand;
}

inline byte CPU::zeropage()
{
	PC++;
	word operandAddr = memory->read(PC);
	byte operand = memory->read(operandAddr) & 0x00FF;
	return operand;
}

inline void CPU::relative()
{
	PC++;
	byte addr = memory->read(PC);
	PC++;
	PC += addr;
}

inline byte CPU::zeropageX()
{
	PC++;
	word operandAddr = memory->read(PC);
	byte operand = (memory->read(operandAddr) + X) & 0x00FF;
	return operand;
}

inline void CPU::indirect()
{
	PC++;
	PC = memory->read(PC);
}

inline void CPU::ORA(byte &operand)
{
	A |= operand;
	setNegativeStatusFlag(A);
	setZeroFlag(A);
}

inline void CPU::ASL(byte &operand)
{
	operand <<= 1;
	setNegativeStatusFlag(operand);
	setZeroFlag(operand);
	setCarryFlag(operand);
}

inline void CPU::PHP()
{
	memory->writeWord(SP, PC);
}

inline void CPU::CLC()
{
	P.C = 0;
}

inline void CPU::JSR()
{
	PHP();
	PC++;
	PC = memory->readWord(PC);
}

inline void CPU::AND(byte & operand)
{
	A &= operand;
	setNegativeStatusFlag(A);
	setZeroFlag(A);
}

inline void CPU::BIT(byte & operand)
{
	operand &= A;
	setZeroFlag(operand);
	setNegativeStatusFlag(operand);
	if (operand & 0x40) P.V = 1;
	else P.V = 0;

}

inline void CPU::setCarryFlag(byte value)
{
	if (value & 0x80) {
		if (!((value + 1) & 0x80)) P.C = 1;
	}
	else P.C = 0;
}

inline void CPU::setNegativeStatusFlag(byte value)
{
	if (value & 0x80) P.N = 1;
	else P.N = 0;
}

inline void CPU::setOverflowFlag(byte value1, byte value2, bool sign)
{
	if (sign) {
		if (!((value1 & 0x80) && (value2 & 0x80))) {
			value1 += value2;
			if ((value1 & 0x80) != (value2 & 0x80)) P.V = 1;
		}
		else {
			P.V = 0;
		}
	}
	else {
		if ((value1 & 0x80) != (value2 & 0x80)) {
			value1 += value2;
			if ((value1 & 0x80) != (value2 & 0x80)) P.V = 1;
		}
		else {
			P.V = 0;
		}
	}
}

inline void CPU::setZeroFlag(byte value)
{
	if (value) P.Z = 0;
	else P.Z = 1;
}

