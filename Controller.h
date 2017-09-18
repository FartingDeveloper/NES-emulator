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

	byte strobe;
	byte offset;
public:
	Controller();

	void setButton(byte button, byte value);
	void write(byte s);
	byte read();
private:
	byte convertButtons();
};

