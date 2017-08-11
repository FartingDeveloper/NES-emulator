#pragma once
#include "Memory.h"

class CPU
{
	byte A, X, Y, SP;
	word PC;
	struct flags{
		unsigned C : 1; //shift
		unsigned Z : 1; //zero
		unsigned I : 1; //interrupt allower(if I = 0 -> can interrupt, else no interrupting)
		unsigned D : 1; //BCD mode???
		unsigned B : 1; //interrupt handler
		unsigned   : 1;
		unsigned V : 1; //borrow
		unsigned N : 1; //sign
	} P;

	Memory * memory;
public:
	CPU();
private:
	void executeOpcode(byte opcode);

	//address mode
	inline byte immediate();
	inline byte absolute();
	inline byte absoluteX();
	inline byte absoluteY();
	inline byte indexedInderect();
	inline byte inderectIndexed();
	inline byte zeropage();
	inline void relative();
	inline byte zeropageX();
	inline byte zeropageY();
	inline word indirect();

	//commands
	inline void ORA(byte &operand);
	inline void ASL(byte &operand);
	inline void PHP();
	inline void CLC();
	inline void JSR();
	inline void AND(byte &operand);
	inline void BIT(byte &operand);
	inline void ROL(byte &operand);
	inline void PLP();
	inline void BMI();
	inline void SEC();
	inline void RTI();
	inline void EOR(byte &operand);
	inline void LSR(byte &operand);
	inline void PHA();
	inline void JMP(word &operand);
	inline void BVC();
	inline void CLI();
	inline void RTS();
	inline void ADC(byte &operand);
	inline void ROR(byte &operand);
	inline void PLA();
	inline void BVS();
	inline void SEI();
	inline void STA(byte &operand);
	inline void STY(byte &operand);
	inline void STX(byte &operand);
	inline void DEY();
	inline void TXA();
	inline void BCC();
	inline void TYA();
	inline void TXS();
	inline void LDY(byte &operand);
	inline void LDA(byte &operand);
	inline void LDX(byte &operand);
	inline void TAY();
	inline void TAX();
	inline void BCS();
	inline void CLV();
	inline void TSX();
	inline void CPY(byte &operand);
	inline void CMP(byte &operand);
	inline void DEC(byte &operand);
	inline void INY();
	inline void DEX();
	inline void BNE();
	inline void CLD();
	inline void CPX(byte &operand);
	inline void SBC(byte &operand);
	inline void INC(byte &operand);
	inline void INX();
	inline void BEQ();
	inline void SED();

	//check flags
	inline byte convertFlags();
	inline void setFlags(byte b);
	inline void setCarryFlag(byte oldValue, byte newValue);
	inline void setNegativeStatusFlag(byte value);
	inline void setOverflowFlag(byte value1, byte value2);
	inline void setZeroFlag(byte value);
	inline void setInterruptAllowerFlag(byte value);
	inline void setInterruptHandlerFlag(byte value);
	inline void setBCDFlag(byte value);
};

