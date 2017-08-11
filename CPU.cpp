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
		byte operand = zeropage();
		BIT(operand);
		break;
	}
	case 0x25: {
		byte operand = zeropage();
		AND(operand);
		break;
	}
	case 0x26:{
		byte operand = zeropage();
		ROL(operand);
		break;
	}
	case 0x28: {
		PLP();
		break;
	}
	case 0x29: {
		byte operand = immediate();
		AND(operand);
		break;
	}
	case 0x2A: {
		ROL(A);
		break;
	}
	case 0x2C: {
		byte operand = absolute();
		BIT(operand);
		break;
	}
	case 0x2D: {
		byte operand = absolute();
		BIT(operand);
		break;
	}
	case 0x2E: {
		byte operand = absolute();
		ROL(operand);
		break;
	}
	case 0x30: {
		BMI();
		return;
	}
	case 0x31: {
		byte operand = inderectIndexed();
		AND(operand);
		break;
	}
	case 0x35: {
		byte operand = zeropageX();
		AND(operand);
		break;
	}
	case 0x36: {
		byte operand = zeropageX();
		ROL(operand);
		break;
	}
	case 0x38: {
		SEC();
		break;
	}
	case 0x39: {
		byte operand = absoluteY();
		AND(operand);
		break;
	}
	case 0x3D: {
		byte operand = absoluteX();
		AND(operand);
		break;
	}
	case 0x3E: {
		byte operand = absoluteX();
		ROL(operand);
		break;
	}
	case 0x40: {
		RTI();
		return;
	}
	case 0x41: {
		byte operand = indexedInderect();
		EOR(operand);
		break;
	}
	case 0x45: {
		byte operand = zeropage();
		EOR(operand);
		break;
	}
	case 0x46: {
		byte operand = zeropage();
		LSR(operand);
		break;
	}
	case 0x48: {
		PHA();
		break;
	}
	case 0x49: {
		byte operand = immediate();
		EOR(operand);
		break;
	}
	case 0x4A: {
		LSR(A);
		break;
	}
	case 0x4C: {
		word addr = absolute();
		JMP(addr);
		return;
	}
	case 0x4D: {
		byte operand = absolute();
		EOR(operand);
		break;
	}
	case 0x4E: {
		byte operand = absolute();
		LSR(operand);
		break;
	}
	case 0x50: {
		BVC();
		return;
	}
	case 0x51: {
		byte operand = inderectIndexed();
		EOR(operand);
		break;
	}
	case 0x55: {
		byte operand = zeropageX();
		EOR(operand);
		break;
	}
	case 0x56: {
		byte operand = zeropageX();
		LSR(operand);
		break;
	}
	case 0x58: {
		CLI();
		break;
	}
	case 0x59: {
		byte operand = absoluteY();
		EOR(operand);
		break;
	}
	case 0x5D: {
		byte operand = absoluteX();
		EOR(operand);
		break;
	}
	case 0x5E: {
		byte operand = absoluteX();
		LSR(operand);
		break;
	}
	case 0x60: {
		RTS();
		return;
	}
	case 0x61: {
		byte operand = indexedInderect();
		ADC(operand);
		break;
	}
	case 0x65: {
		byte operand = zeropage();
		ADC(operand);
		break;
	}
	case 0x66: {
		byte operand = zeropage();
		ROR(operand);
		break;
	}
	case 0x68: {
		PLA();
		break;
	}
	case 0x69: {
		byte operand = immediate();
		ADC(operand);
		break;
	}
	case 0x6A: {
		ROR(A);
		break;
	}
	case 0x6C: {
		word operand = indirect();
		JMP(operand);
		return;
	}
	case 0x6D: {
		byte operand = absolute();
		ADC(operand);
		break;
	}
	case 0x6E: {
		byte operand = absoluteX();
		ROR(operand);
		break;
	}
	case 0x70: {
		BVS();
		return;
	}
	case 0x71: {
		byte operand = inderectIndexed();
		ADC(operand);
		break;
	}
	case 0x75: {
		byte operand = zeropageX();
		ADC(operand);
		break;
	}
	case 0x76: {
		byte operand = zeropageX();
		ROR(operand);
		break;
	}
	case 0x78: {
		SEI();
		break;
	}
	case 0x79: {
		byte operand = absoluteY();
		ADC(operand);
		break;
	}
	case 0x7D: {
		byte operand = absoluteX();
		ADC(operand);
		break;
	}
	case 0x7E: {
		byte operand = absolute();
		ROR(operand);
		break;
	}
	case 0x81: {
		byte operand = indexedInderect();
		STA(operand);
		break;
	}
	case 0x84: {
		byte operand = zeropage();
		STY(operand);
		break;
	}
	case 0x85: {
		byte operand = zeropage();
		STA(operand);
		break;
	}
	case 0x86: {
		byte operand = zeropage();
		STX(operand);
		break;
	}
	case 0x88: {
		DEY();
		break;
	}
	case 0x8A: {
		TXA();
		break;
	}
	case 0x8C: {
		byte operand = absolute();
		STY(operand);
		break;
	}
	case 0x8D: {
		byte operand = absolute();
		STA(operand);
		break;
	}
	case 0x8E: {
		byte operand = absolute();
		STX(operand);
		break;
	}
	case 0x90: {
		BCC();
		return;
	}
	case 0x91: {
		byte operand = inderectIndexed();
		STA(operand);
		break;
	}
	case 0x94: {
		byte operand = zeropageX();
		STY(operand);
		break;
	}
	case 0x95: {
		byte operand = zeropageX();
		STA(operand);
		break;
	}
	case 0x96: {
		byte operand = zeropageY();
		STX(operand);
		break;
	}
	case 0x98: {
		TYA();
		break;
	}
	case 0x99: {
		byte operand = absoluteY();
		STA(operand);
		break;
	}
	case 0x9A: {
		TXS();
		break;
	}
	case 0x9D: {
		byte operand = absoluteX();
		STA(operand);
		break;
	}
	case 0xA0: {
		byte operand = immediate();
		LDY(operand);
		break;
	}
	case 0xA1: {
		byte operand = indexedInderect();
		LDA(operand);
		break;
	}
	case 0xA2: {
		byte operand = immediate();
		LDX(operand);
		break;
	}
	case 0xA4: {
		byte operand = zeropage();
		LDY(operand);
		break;
	}
	case 0xA5: {
		byte operand = zeropage();
		LDA(operand);
		break;
	}
	case 0xA6: {
		byte operand = zeropage();
		LDX(operand);
		break;
	}
	case 0xA8: {
		TAY();
		break;
	}
	case 0xA9: {
		byte operand = immediate();
		LDA(operand);
		break;
	}
	case 0xAA: {
		TAX();
		break;
	}
	case 0xAC: {
		byte operand = absolute();
		LDY(operand);
		break;
	}
	case 0xAD: {
		byte operand = absolute();
		LDA(operand);
		break;
	}
	case 0xAE: {
		byte operand = absolute();
		LDX(operand);
		break;
	}
	case 0xB0: {
		BCS();
		return;
	}
	case 0xB1: {
		byte operand = inderectIndexed();
		LDA(operand);
		break;
	}
	case 0xB4: {
		byte operand = zeropageX();
		LDY(operand);
		break;
	}
	case 0xB5: {
		byte operand = zeropageX();
		LDA(operand);
		break;
	}
	case 0xB6: {
		byte operand = zeropageY();
		LDX(operand);
		break;
	}
	case 0xB8: {
		CLV();
		break;
	}
	case 0xB9: {
		byte operand = absoluteY();
		LDA(operand);
		break;
	}
	case 0xBA: {
		TSX();
		break;
	}
	case 0xBC: {
		byte operand = absoluteX();
		LDY(operand);
		break;
	}
	case 0xBD: {
		byte operand = absoluteX();
		LDA(operand);
		break;
	}
	case 0xBE: {
		byte operand = absoluteY();
		LDX(operand);
		break;
	}
	case 0xC0: {
		byte operand = immediate();
		CPY(operand);
		break;
	}
	case 0xC1: {
		byte operand = indexedInderect();
		CMP(operand);
		break;
	}
	case 0xC4: {
		byte operand = zeropage();
		CPY(operand);
		break;
	}
	case 0xC5: {
		byte operand = zeropage();
		CMP(operand);
		break;
	}
	case 0xC6: {
		byte operand = zeropage();
		DEC(operand);
		break;
	}
	case 0xC8: {
		INY();
		break;
	}
	case 0xC9: {
		byte operand = immediate();
		CMP(operand);
		break;
	}
	case 0xCA: {
		DEX();
		break;
	}
	case 0xCC: {
		byte operand = absolute();
		CPY(operand);
		break;
	}
	case 0xCD: {
		byte operand = absolute();
		CMP(operand);
		break;
	}
	case 0xCE: {
		byte operand = absolute();
		DEC(operand);
		break;
	}
	case 0xD0: {
		BNE();
		return;
	}
	case 0xD1: {
		byte operand = inderectIndexed();
		CMP(operand);
		break;
	}
	case 0xD5: {
		byte operand = zeropageX();
		CMP(operand);
		break;
	}
	case 0xD6: {
		byte operand = zeropageX();
		DEC(operand);
		break;
	}
	case 0xD8: {
		CLD();
		break;
	}
	case 0xD9: {
		byte operand = absoluteY();
		CMP(operand);
		break;
	}
	case 0xDD: {
		byte operand = absoluteX();
		CMP(operand);
		break;
	}
	case 0xDE: {
		byte operand = absoluteX();
		DEC(operand);
		break;
	}
	case 0xE0: {
		byte operand = immediate();
		CPX(operand);
		break;
	}
	case 0xE1: {
		byte operand = indexedInderect();
		SBC(operand);
		break;
	}
	case 0xE4: {
		byte operand = zeropage();
		CPX(operand);
		break;
	}
	case 0xE5: {
		byte operand = zeropage();
		SBC(operand);
		break;
	}
	case 0xE6: {
		byte operand = zeropage();
		INC(operand);
		break;
	}
	case 0xE8: {
		INX();
		break;
	}
	case 0xE9: {
		byte operand = immediate();
		SBC(operand);
		break;
	}
	case 0xEA: {
		//NOP
		break;
	}
	case 0xEC: {
		byte operand = absolute();
		CPX(operand);
		break;
	}
	case 0xED: {
		byte operand = absolute();
		SBC(operand);
		break;
	}
	case 0xEE: {
		byte operand = absolute();
		INC(operand);
		break;
	}
	case 0xF0: {
		BEQ();
		return;
	}
	case 0xF1: {
		byte operand = inderectIndexed();
		SBC(operand);
		break;
	}
	case 0xF5: {
		byte operand = zeropageX();
		SBC(operand);
		break;
	}
	case 0xF6: {
		byte operand = zeropageX();
		INC(operand);
		break;
	}
	case 0xF8: {
		SED();
		break;
	}
	case 0xF9: {
		byte operand = absoluteY();
		SBC(operand);
		break;
	}
	case 0xFD: {
		byte operand = absoluteX();
		SBC(operand);
		break;
	}
	case 0xFE: {
		byte operand = absoluteX();
		INC(operand);
		break;
	}
	default:
		break;
	}
	PC++;
}

byte CPU::convertFlags()
{
	byte b = 0;
	if (P.C) b += 1;
	if (P.Z) b += 1 << 1;
	if (P.I) b += 1 << 2;
	if (P.D) b += 1 << 3;
	if (P.B) b += 1 << 4;
	b += 1 << 5;
	if (P.V) b += 1 << 6;
	if (P.N) b += 1 << 7;
	return b;
}

inline void CPU::setFlags(byte b)
{
	int mask = 1;
	P.C = b & mask;
	P.Z = b & (mask << 1);
	P.I = b & (mask << 2);
	P.D = b & (mask << 3);
	P.B = b & (mask << 4);
	P.V = b & (mask << 6);
	P.N = b & (mask << 7);
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

inline byte CPU::zeropageY()
{
	PC++;
	word operandAddr = memory->read(PC);
	byte operand = (memory->read(operandAddr) + Y) & 0x00FF;
	return operand;
}

inline word CPU::indirect()
{
	PC++;
	return memory->readWord(PC);
}

inline void CPU::ORA(byte &operand)
{
	A |= operand;
	setNegativeStatusFlag(A);
	setZeroFlag(A);
}

inline void CPU::ASL(byte &operand)
{
	setCarryFlag(operand, operand << 1);
	operand <<= 1;
	setNegativeStatusFlag(operand);
	setZeroFlag(operand);
}

inline void CPU::PHP()
{
	byte flags = convertFlags();
	memory->push(SP, flags);
}

inline void CPU::CLC()
{
	P.C = 0;
}

inline void CPU::JSR()
{
	PC++;
	memory->pushWord(SP, PC + 1);
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

inline void CPU::ROL(byte & operand)
{
	setCarryFlag(operand, operand << 1);
	operand <<= 1;
	if (P.C) operand += 1;
	setNegativeStatusFlag(operand);
	setZeroFlag(operand);
}

inline void CPU::PLP()
{
	byte flags = memory->pop(SP);
	setFlags(flags);
}

inline void CPU::BMI()
{
	if (P.N) relative();
}

inline void CPU::SEC()
{
	P.C = 1;
}

inline void CPU::RTI()
{
	PLP();
	PC = memory->popWord(SP);
}

inline void CPU::EOR(byte &operand)
{
	A ^= operand;
	setNegativeStatusFlag(A);
	setZeroFlag(A);
}

inline void CPU::LSR(byte & operand)
{
	byte old = operand;
	operand = (operand >> 1) | (operand & 0x80);
	setCarryFlag(old, operand);
	setNegativeStatusFlag(0);
	setZeroFlag(operand);
}

inline void CPU::PHA()
{
	memory->push(SP, A);
}

inline void CPU::JMP(word &operand)
{
	PC = operand;
}

inline void CPU::BVC()
{
	if (!P.V) relative();
}

inline void CPU::CLI()
{
	P.I = 0;
}

inline void CPU::RTS()
{
	PC = memory->popWord(SP);
}

inline void CPU::ADC(byte & operand)
{
	byte old = A;
	A += operand + P.C;
	setCarryFlag(old, A);
	setOverflowFlag(old, A);
	setNegativeStatusFlag(0);
	setZeroFlag(operand);
}

inline void CPU::ROR(byte & operand)
{
	if (operand & 1) P.C = 1;
	operand >>= 1;
	if (P.C) operand += 0x80;
	setNegativeStatusFlag(operand);
	setZeroFlag(operand);
}

inline void CPU::PLA()
{
	A = memory->pop(SP);
	setNegativeStatusFlag(A);
	setZeroFlag(A);
}

inline void CPU::BVS()
{
	if(P.V) relative();
}

inline void CPU::SEI()
{
	P.I = 1;
}

inline void CPU::STA(byte &operand)
{
	memory->write(operand, A);
}

inline void CPU::STY(byte & operand)
{
	memory->write(operand, Y);
}

inline void CPU::STX(byte & operand)
{
	memory->write(operand, X);
}

inline void CPU::DEY()
{
	Y--;
	setNegativeStatusFlag(Y);
	setZeroFlag(Y);
}

inline void CPU::TXA()
{
	A = X;
	setNegativeStatusFlag(A);
	setZeroFlag(A);
}

inline void CPU::BCC()
{
	if (!P.C) relative();
}

inline void CPU::TYA()
{
	A = Y;
	setNegativeStatusFlag(A);
	setZeroFlag(A);
}

inline void CPU::TXS()
{
	SP = X;
}

inline void CPU::LDY(byte & operand)
{
	Y = operand;
	setNegativeStatusFlag(Y);
	setZeroFlag(Y);
}

inline void CPU::LDA(byte & operand)
{
	A = operand;
	setNegativeStatusFlag(A);
	setZeroFlag(A);
}

inline void CPU::LDX(byte & operand)
{
	X = operand;
	setNegativeStatusFlag(X);
	setZeroFlag(X);
}

inline void CPU::TAY()
{
	Y = A;
	setNegativeStatusFlag(Y);
	setZeroFlag(Y);
}

inline void CPU::TAX()
{
	X = A;
	setNegativeStatusFlag(X);
	setZeroFlag(X);
}

inline void CPU::BCS()
{
	if (P.C) relative();
}

inline void CPU::CLV()
{
	P.V = 0;
}

inline void CPU::TSX()
{
	SP = X;
	setNegativeStatusFlag(X);
	setZeroFlag(X);
}

inline void CPU::CPY(byte & operand)
{
	byte res = Y - operand;
	setNegativeStatusFlag(res);
	setZeroFlag(res);
	setCarryFlag(Y, res);
}

inline void CPU::CMP(byte & operand)
{
	byte res = A - operand;
	setNegativeStatusFlag(res);
	setZeroFlag(res);
	setCarryFlag(A, res);
}

inline void CPU::DEC(byte & operand)
{
	operand--;
	setNegativeStatusFlag(operand);
	setZeroFlag(operand);
}

inline void CPU::INY()
{
	Y++;
	setNegativeStatusFlag(Y);
	setZeroFlag(Y);
}

inline void CPU::DEX()
{
	X--;
	setNegativeStatusFlag(X);
	setZeroFlag(X);
}

inline void CPU::BNE()
{
	if (!P.Z) relative();
}

inline void CPU::CLD()
{
	P.D = 0;
}

inline void CPU::CPX(byte & operand)
{
	byte res = X - operand;
	setNegativeStatusFlag(res);
	setZeroFlag(res);
	setCarryFlag(X, res);
}

inline void CPU::SBC(byte & operand)
{
	byte old = A;
	A = A - operand - P.C;
	setCarryFlag(old, A);
	setOverflowFlag(old, A);
	setNegativeStatusFlag(0);
	setZeroFlag(operand);
}

inline void CPU::INC(byte & operand)
{
	operand++;
	setNegativeStatusFlag(operand);
	setZeroFlag(operand);
}

inline void CPU::INX()
{
	X++;
	setNegativeStatusFlag(X);
	setZeroFlag(X);
}

inline void CPU::BEQ()
{
	if (P.Z) relative();
}

inline void CPU::SED()
{
	P.D = 1;
}

inline void CPU::setCarryFlag(byte oldValue, byte newValue)
{
	if (oldValue & 0x80) {
		if (!(newValue & 0x80)) P.C = 1;
	}
	else P.C = 0;
}

inline void CPU::setNegativeStatusFlag(byte value)
{
	if (value & 0x80) P.N = 1;
	else P.N = 0;
}

inline void CPU::setOverflowFlag(byte value1, byte value2)
{
	if ((value1 & 0x80) == (value1 & 0x80)) {
		if ((value1 + value2) & 0x80 != (value1 & 0x80)) P.V = 1;
	}
	else {
		P.V = 0;
	}
}

inline void CPU::setZeroFlag(byte value)
{
	if (value) P.Z = 0;
	else P.Z = 1;
}

