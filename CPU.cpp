#include "CPU.h"

CPU::CPU(RAM *& memory)
{
	this->memory = memory;

	cycles = 0;

	A = 0;
	X = 0;
	Y = 0;
	SP = 0xFD;
	PC = 0;
	P.C = 0;
	P.Z = 0;
	P.I = 0; 
	P.D = 1;
	P.B = 1;
	P.V = 1;
	P.N = 0;
}

int CPU::step()
{
	cycles = 0;

	checkInterrupt();

	byte opcode = memory->read(PC);

	switch (opcode & 0xE0)
	{
	case 0x00: {
		BRK();
		cycles += 7;
		return cycles;
	}
	case 0x01: {
		byte operand = indexedInderect();
		ORA(operand);
		cycles += 6;
		break;
	}
	case 0x05: {
		byte operand = zeropage();
		ORA(operand);
		cycles += 3;
		break;
	}
	case 0x06: {
		byte operand = zeropage();
		ASL(operand);
		cycles += 5;
		break;
	}
	case 0x08: {
		PHP();
		cycles += 3;
		break;
	}
	case 0x09: {
		byte operand = immediate();
		ORA(operand);
		cycles += 2;
		break;
	}
	case 0x0A: {
		ASL(A);
		cycles += 2;
		break;
	}
	case 0x0D: {
		byte operand = absolute();
		ORA(operand);
		cycles += 4;
		break;
	}
	case 0x0E: {
		byte operand = absolute();
		ASL(operand);
		cycles += 6;
		break;
	}
	case 0x10: {
		BPL();
		return cycles;
	}
	case 0x11: {
		byte operand = inderectIndexed();
		ORA(operand);
		cycles += 5;
		break;
	}
	case 0x15: {
		byte operand = zeropageX();
		ORA(operand);
		cycles += 4;
		break;
	}
	case 0x16: {
		byte operand = zeropageX();
		ASL(operand);
		cycles += 6;
		break;
	}
	case 0x18: {
		CLC();
		cycles += 2;
		break;
	}
	case 0x19: {
		byte operand = absoluteY();
		ORA(operand);
		if (pageCrossed) cycles += 5;
		else cycles += 4;
		break;
	}
	case 0x1D: {
		byte operand = absoluteX();
		ORA(operand);
		if (pageCrossed) cycles += 5;
		else cycles += 4;
		break;
	}
	case 0x1E: {
		byte operand = absoluteX();
		ASL(operand);
		cycles += 7;
		break;
	}
	case 0x20: {
		JSR();
		cycles += 6;
		return cycles;
	}
	case 0x21: {
		byte operand = indexedInderect();
		AND(operand);
		cycles += 6;
		break;
	}
	case 0x24: {
		byte operand = zeropage();
		BIT(operand);
		cycles += 3;
		break;
	}
	case 0x25: {
		byte operand = zeropage();
		AND(operand);
		cycles += 3;
		break;
	}
	case 0x26:{
		byte operand = zeropage();
		ROL(operand);
		cycles += 5;
		break;
	}
	case 0x28: {
		PLP();
		cycles += 4;
		break;
	}
	case 0x29: {
		byte operand = immediate();
		AND(operand);
		cycles += 2;
		break;
	}
	case 0x2A: {
		ROL(A);
		cycles += 2;
		break;
	}
	case 0x2C: {
		byte operand = absolute();
		BIT(operand);
		cycles += 4;
		break;
	}
	case 0x2D: {
		byte operand = absolute();
		AND(operand);
		cycles += 4;
		break;
	}
	case 0x2E: {
		byte operand = absolute();
		ROL(operand);
		cycles += 6;
		break;
	}
	case 0x30: {
		BMI();
		return cycles;
	}
	case 0x31: {
		byte operand = inderectIndexed();
		AND(operand);
		cycles += 5;
		break;
	}
	case 0x35: {
		byte operand = zeropageX();
		AND(operand);
		cycles += 4;
		break;
	}
	case 0x36: {
		byte operand = zeropageX();
		ROL(operand);
		cycles += 6;
		break;
	}
	case 0x38: {
		SEC();
		cycles += 2;
		break;
	}
	case 0x39: {
		byte operand = absoluteY();
		AND(operand);
		if(pageCrossed) cycles += 5;
		else cycles += 4;
		break;
	}
	case 0x3D: {
		byte operand = absoluteX();
		AND(operand);
		if (pageCrossed) cycles += 5;
		else cycles += 4;
		break;
	}
	case 0x3E: {
		byte operand = absoluteX();
		ROL(operand);
		cycles += 7;
		break;
	}
	case 0x40: {
		RTI();
		cycles += 6;
		return cycles;
	}
	case 0x41: {
		byte operand = indexedInderect();
		EOR(operand);
		cycles += 6;
		break;
	}
	case 0x45: {
		byte operand = zeropage();
		EOR(operand);
		cycles += 3;
		break;
	}
	case 0x46: {
		byte operand = zeropage();
		LSR(operand);
		cycles += 5;
		break;
	}
	case 0x48: {
		PHA();
		cycles += 3;
		break;
	}
	case 0x49: {
		byte operand = immediate();
		EOR(operand);
		cycles += 2;
		break;
	}
	case 0x4A: {
		LSR(A);
		cycles += 2;
		break;
	}
	case 0x4C: {
		word addr = absolute();
		JMP(addr);
		cycles += 3;
		return cycles;
	}
	case 0x4D: {
		byte operand = absolute();
		EOR(operand);
		cycles += 4;
		break;
	}
	case 0x4E: {
		byte operand = absolute();
		LSR(operand);
		cycles += 6;
		break;
	}
	case 0x50: {
		BVC();
		return cycles;
	}
	case 0x51: {
		byte operand = inderectIndexed();
		EOR(operand);
		if (pageCrossed) cycles += 6;
		else cycles += 5;
		break;
	}
	case 0x55: {
		byte operand = zeropageX();
		EOR(operand);
		cycles += 4;
		break;
	}
	case 0x56: {
		byte operand = zeropageX();
		LSR(operand);
		cycles += 6;
		break;
	}
	case 0x58: {
		CLI();
		cycles += 2;
		break;
	}
	case 0x59: {
		byte operand = absoluteY();
		EOR(operand);
		if (pageCrossed) cycles += 5;
		else cycles += 4;
		break;
	}
	case 0x5D: {
		byte operand = absoluteX();
		EOR(operand);
		if (pageCrossed) cycles += 5;
		else cycles += 4;
		break;
	}
	case 0x5E: {
		byte operand = absoluteX();
		LSR(operand);
		cycles += 7;
		break;
	}
	case 0x60: {
		RTS();
		cycles += 6;
		return cycles;
	}
	case 0x61: {
		byte operand = indexedInderect();
		ADC(operand);
		cycles += 6;
		break;
	}
	case 0x65: {
		byte operand = zeropage();
		ADC(operand);
		cycles += 3;
		break;
	}
	case 0x66: {
		byte operand = zeropage();
		ROR(operand);
		cycles += 5;
		break;
	}
	case 0x68: {
		PLA();
		cycles += 4;
		break;
	}
	case 0x69: {
		byte operand = immediate();
		ADC(operand);
		cycles += 2;
		break;
	}
	case 0x6A: {
		ROR(A);
		cycles += 2;
		break;
	}
	case 0x6C: {
		word operand = indirect();
		JMP(operand);
		cycles += 5;
		return cycles;
	}
	case 0x6D: {
		byte operand = absolute();
		ADC(operand);
		cycles += 4;
		break;
	}
	case 0x6E: {
		byte operand = absoluteX();
		ROR(operand);
		cycles += 6;
		break;
	}
	case 0x70: {
		BVS();
		return cycles;
	}
	case 0x71: {
		byte operand = inderectIndexed();
		ADC(operand);
		if (pageCrossed) cycles += 6;
		else cycles += 5;
		break;
	}
	case 0x75: {
		byte operand = zeropageX();
		ADC(operand);
		cycles += 4;
		break;
	}
	case 0x76: {
		byte operand = zeropageX();
		ROR(operand);
		cycles += 6;
		break;
	}
	case 0x78: {
		SEI();
		cycles += 2;
		break;
	}
	case 0x79: {
		byte operand = absoluteY();
		ADC(operand);
		if (pageCrossed) cycles += 5;
		else cycles += 4;
		break;
	}
	case 0x7D: {
		byte operand = absoluteX();
		ADC(operand);
		if (pageCrossed) cycles += 5;
		else cycles += 4;
		break;
	}
	case 0x7E: {
		byte operand = absolute();
		ROR(operand);
		cycles += 7;
		break;
	}
	case 0x81: {
		byte operand = indexedInderect();
		STA(operand);
		cycles += 6;
		break;
	}
	case 0x84: {
		byte operand = zeropage();
		STY(operand);
		cycles += 3;
		break;
	}
	case 0x85: {
		byte operand = zeropage();
		STA(operand);
		cycles += 3;
		break;
	}
	case 0x86: {
		byte operand = zeropage();
		STX(operand);
		cycles += 3;
		break;
	}
	case 0x88: {
		DEY();
		cycles += 2;
		break;
	}
	case 0x8A: {
		TXA();
		cycles += 2;
		break;
	}
	case 0x8C: {
		byte operand = absolute();
		STY(operand);
		cycles += 4;
		break;
	}
	case 0x8D: {
		byte operand = absolute();
		STA(operand);
		cycles += 4;
		break;
	}
	case 0x8E: {
		byte operand = absolute();
		STX(operand);
		cycles += 4;
		break;
	}
	case 0x90: {
		BCC();
		return cycles;
	}
	case 0x91: {
		byte operand = inderectIndexed();
		STA(operand);
		cycles += 6;
		break;
	}
	case 0x94: {
		byte operand = zeropageX();
		STY(operand);
		cycles += 4;
		break;
	}
	case 0x95: {
		byte operand = zeropageX();
		STA(operand);
		cycles += 4;
		break;
	}
	case 0x96: {
		byte operand = zeropageY();
		STX(operand);
		cycles += 4;
		break;
	}
	case 0x98: {
		TYA();
		cycles += 2;
		break;
	}
	case 0x99: {
		byte operand = absoluteY();
		STA(operand);
		cycles += 5;
		break;
	}
	case 0x9A: {
		TXS();
		cycles += 2;
		break;
	}
	case 0x9D: {
		byte operand = absoluteX();
		STA(operand);
		cycles += 5;
		break;
	}
	case 0xA0: {
		byte operand = immediate();
		LDY(operand);
		cycles += 2;
		break;
	}
	case 0xA1: {
		byte operand = indexedInderect();
		LDA(operand);
		cycles += 6;
		break;
	}
	case 0xA2: {
		byte operand = immediate();
		LDX(operand);
		cycles += 2;
		break;
	}
	case 0xA4: {
		byte operand = zeropage();
		LDY(operand);
		cycles += 3;
		break;
	}
	case 0xA5: {
		byte operand = zeropage();
		LDA(operand);
		cycles += 3;
		break;
	}
	case 0xA6: {
		byte operand = zeropage();
		LDX(operand);
		cycles += 3;
		break;
	}
	case 0xA8: {
		TAY();
		cycles += 2;
		break;
	}
	case 0xA9: {
		byte operand = immediate();
		LDA(operand);
		cycles += 2;
		break;
	}
	case 0xAA: {
		TAX();
		cycles += 2;
		break;
	}
	case 0xAC: {
		byte operand = absolute();
		LDY(operand);
		cycles += 4;
		break;
	}
	case 0xAD: {
		byte operand = absolute();
		LDA(operand);
		cycles += 4;
		break;
	}
	case 0xAE: {
		byte operand = absolute();
		LDX(operand);
		cycles += 4;
		break;
	}
	case 0xB0: {
		BCS();
		return cycles;
	}
	case 0xB1: {
		byte operand = inderectIndexed();
		LDA(operand);
		if (pageCrossed) cycles += 6;
		else cycles += 5;
		break;
	}
	case 0xB4: {
		byte operand = zeropageX();
		LDY(operand);
		cycles += 4;
		break;
	}
	case 0xB5: {
		byte operand = zeropageX();
		LDA(operand);
		cycles += 4;
		break;
	}
	case 0xB6: {
		byte operand = zeropageY();
		LDX(operand);
		cycles += 4;
		break;
	}
	case 0xB8: {
		CLV();
		cycles += 2;
		break;
	}
	case 0xB9: {
		byte operand = absoluteY();
		LDA(operand);
		if (pageCrossed) cycles += 5;
		else cycles += 4;
		break;
	}
	case 0xBA: {
		TSX();
		cycles += 2;
		break;
	}
	case 0xBC: {
		byte operand = absoluteX();
		LDY(operand);
		if (pageCrossed) cycles += 5;
		else cycles += 4;
		break;
	}
	case 0xBD: {
		byte operand = absoluteX();
		LDA(operand);
		if (pageCrossed) cycles += 5;
		else cycles += 4;
		break;
	}
	case 0xBE: {
		byte operand = absoluteY();
		LDX(operand);
		if (pageCrossed) cycles += 5;
		else cycles += 4;
		break;
	}
	case 0xC0: {
		byte operand = immediate();
		CPY(operand);
		cycles += 2;
		break;
	}
	case 0xC1: {
		byte operand = indexedInderect();
		CMP(operand);
		cycles += 6;
		break;
	}
	case 0xC4: {
		byte operand = zeropage();
		CPY(operand);
		cycles += 3;
		break;
	}
	case 0xC5: {
		byte operand = zeropage();
		CMP(operand);
		cycles += 3;
		break;
	}
	case 0xC6: {
		byte operand = zeropage();
		DEC(operand);
		cycles += 5;
		break;
	}
	case 0xC8: {
		INY();
		cycles += 2;
		break;
	}
	case 0xC9: {
		byte operand = immediate();
		CMP(operand);
		cycles += 2;
		break;
	}
	case 0xCA: {
		DEX();
		cycles += 2;
		break;
	}
	case 0xCC: {
		byte operand = absolute();
		CPY(operand);
		cycles += 4;
		break;
	}
	case 0xCD: {
		byte operand = absolute();
		CMP(operand);
		cycles += 4;
		break;
	}
	case 0xCE: {
		byte operand = absolute();
		DEC(operand);
		cycles += 6;
		break;
	}
	case 0xD0: {
		BNE();
		return cycles;
	}
	case 0xD1: {
		byte operand = inderectIndexed();
		CMP(operand);
		if (pageCrossed) cycles += 6;
		else cycles += 5;
		break;
	}
	case 0xD5: {
		byte operand = zeropageX();
		CMP(operand);
		cycles += 4;
		break;
	}
	case 0xD6: {
		byte operand = zeropageX();
		DEC(operand);
		cycles += 6;
		break;
	}
	case 0xD8: {
		CLD();
		cycles += 2;
		break;
	}
	case 0xD9: {
		byte operand = absoluteY();
		CMP(operand);
		if (pageCrossed) cycles += 5;
		else cycles += 4;
		break;
	}
	case 0xDD: {
		byte operand = absoluteX();
		CMP(operand);
		if (pageCrossed) cycles += 5;
		else cycles += 4;
		break;
	}
	case 0xDE: {
		byte operand = absoluteX();
		DEC(operand);
		cycles += 7;
		break;
	}
	case 0xE0: {
		byte operand = immediate();
		CPX(operand);
		cycles += 2;
		break;
	}
	case 0xE1: {
		byte operand = indexedInderect();
		SBC(operand);
		cycles += 6;
		break;
	}
	case 0xE4: {
		byte operand = zeropage();
		CPX(operand);
		cycles += 3;
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
		cycles += 5;
		break;
	}
	case 0xE8: {
		INX();
		cycles += 2;
		break;
	}
	case 0xE9: {
		byte operand = immediate();
		SBC(operand);
		cycles += 2;
		break;
	}
	case 0xEA: {
		//NOP
		cycles += 2;
		break;
	}
	case 0xEC: {
		byte operand = absolute();
		CPX(operand);
		cycles += 4;
		break;
	}
	case 0xED: {
		byte operand = absolute();
		SBC(operand);
		cycles += 4;
		break;
	}
	case 0xEE: {
		byte operand = absolute();
		INC(operand);
		cycles += 6;
		break;
	}
	case 0xF0: {
		BEQ();
		return cycles;
	}
	case 0xF1: {
		byte operand = inderectIndexed();
		SBC(operand);
		cycles += 5;
		break;
	}
	case 0xF5: {
		byte operand = zeropageX();
		SBC(operand);
		cycles += 4;
		break;
	}
	case 0xF6: {
		byte operand = zeropageX();
		INC(operand);
		cycles += 6;
		break;
	}
	case 0xF8: {
		SED();
		cycles += 2;
		break;
	}
	case 0xF9: {
		byte operand = absoluteY();
		SBC(operand);
		if(pageCrossed) cycles += 5;
		else cycles += 4;
		break;
	}
	case 0xFD: {
		byte operand = absoluteX();
		SBC(operand);
		if (pageCrossed) cycles += 5;
		else cycles += 4;
		break;
	}
	case 0xFE: {
		byte operand = absoluteX();
		INC(operand);
		cycles += 7;
		break;
	}
	default:
		break;
	}
	PC++;
}

void CPU::reset()
{
	A = 0;
	X = 0;
	Y = 0;
	SP = 0xFD;
	PC = memory->read(0xFFFD)*256 + memory->read(0xFFFC);
	P.C = 0;
	P.Z = 0;
	P.I = 0;
	P.D = 1;
	P.B = 1;
	P.V = 1;
	P.N = 0;
}

inline void CPU::checkInterrupt()
{
	byte NMI = memory->read(0x2000) & 0x8000;
	byte IRQ = P.B;
	if (NMI || IRQ) {
		memory->pushWord(SP, PC);
		PHP();
		P.I = 1;

		if (NMI) { //NMI Interrupt
			word addr = 0xFFFA;
			PC = memory->readWord(addr);
		}
		else if (IRQ) { //IRQ Interrupt
			word addr = 0xFFFE;
			PC = memory->readWord(addr);
		}
		cycles += 7;
	} 
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
	checkPageCrossing(PC, operandAddr);
	return operand;
}

inline byte CPU::absoluteX()
{
	PC++;
	word operandAddr = memory->readWord(PC) + X;
	byte operand = memory->read(operandAddr);
	checkPageCrossing(PC, operandAddr);
	return operand;
}

inline byte CPU::absoluteY()
{
	PC++;
	word operandAddr = memory->readWord(PC) + Y;
	byte operand = memory->read(operandAddr);
	checkPageCrossing(PC, operandAddr);
	return operand;
}

inline byte CPU::indexedInderect()
{
	PC++;
	word operandAddr = (memory->read(PC + X)) & 0x00FF;
	byte operand = memory->read(operandAddr);
	checkPageCrossing(PC, operandAddr);
	return operand;
}

inline byte CPU::inderectIndexed()
{
	PC++;
	word operandAddr = memory->read(PC);
	operandAddr = memory->readWord(operandAddr) + Y;
	byte operand = memory->read(operandAddr);
	checkPageCrossing(PC, operandAddr);
	return operand;
}

inline byte CPU::zeropage()
{
	PC++;
	word operandAddr = memory->read(PC) & 0x00FF;
	byte operand = memory->read(operandAddr);
	checkPageCrossing(PC, operandAddr);
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
	operandAddr = (operandAddr + X) & 0x00FF;
	byte operand = memory->read(operandAddr);
	checkPageCrossing(PC, operandAddr);
	return operand;
}

inline byte CPU::zeropageY()
{
	PC++;
	word operandAddr = memory->read(PC);
	operandAddr = (operandAddr + Y) & 0x00FF;
	byte operand = memory->read(operandAddr);
	checkPageCrossing(PC, operandAddr);
	return operand;
}

inline word CPU::indirect()
{
	PC++;
	return memory->readWord(PC);
}

inline void CPU::checkPageCrossing(word a, word b)
{
	pageCrossed = a & 0xFF00 != b & 0xFF00;
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
	if (P.N) {
		relative();
		if (pageCrossed) cycles += 4;
		else cycles += 3;
	}
	else {
		PC += 2;
		cycles += 2;
	}
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
	if (!P.V) {
		relative();
		if(pageCrossed) cycles += 4;
		else cycles += 3;
	}
	else {
		PC += 2;
		cycles += 2;
	}
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
	if (P.V) {
		relative();
		if (pageCrossed) cycles += 4;
		else cycles += 3;
	}
	else {
		PC += 2;
		cycles += 2;
	}
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
	if (!P.C) {
		relative();
		if (pageCrossed) cycles += 4;
		else cycles += 3;
	}
	else {
		PC += 2;
		cycles += 2;
	}
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
	if (P.C) {
		relative();
		if (pageCrossed) cycles += 4;
		else cycles += 3;
	}
	else {
		PC += 2;
		cycles += 2;
	}
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
	if (!P.Z) {
		relative();
		if (pageCrossed) cycles += 4;
		else cycles += 3;
	}
	else {
		PC += 2;
		cycles += 2;
	}
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
	if (P.Z) {
		relative();
		if(pageCrossed) cycles += 4;
		else cycles += 3;
	}
	else {
		PC += 2;
		cycles += 2;
	}
}

inline void CPU::SED()
{
	P.D = 1;
}

inline void CPU::BRK()
{
	P.B = 1;
	P.I = 1;

	PC++;
	memory->pushWord(SP, PC);
	PHP();
	PC = memory->readWord(0xFFFE);
}

inline void CPU::BPL()
{
	if (!P.N) {
		relative();
		if (pageCrossed) cycles += 4;
		else cycles += 3;
	}
	else {
		PC += 2;
		cycles += 2;
	}
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

