#pragma once
#include "types.h"

class Controller
{
	struct {
		unsigned A : 1;
		unsigned B : 1;
		unsigned select : 1;
		unsigned start : 1;
		unsigned up : 1;
		unsigned down : 1;
		unsigned left : 1;
		unsigned right : 1;
	} buttons;
public:
	Controller();

	void write(byte value);
	byte read();
};

