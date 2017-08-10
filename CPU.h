#pragma once
#include "Memory.h"

class CPU
{
	byte A, X, Y;
	word PC, SP;
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
	inline void indirect();

	//commands
	inline void ORA(byte &operand);
	inline void ASL(byte &operand);
	inline void PHP();
	inline void CLC();
	inline void JSR();
	inline void AND(byte &operand);
	inline void BIT(byte &operand);

	//check flags
	inline void setCarryFlag(byte value);
	inline void setNegativeStatusFlag(byte value);
	inline void setOverflowFlag(byte value1, byte value2, bool sign);
	inline void setZeroFlag(byte value);
	inline void setInterruptAllowerFlag(byte value);
	inline void setInterruptHandlerFlag(byte value);
	inline void setBCDFlag(byte value);
};

