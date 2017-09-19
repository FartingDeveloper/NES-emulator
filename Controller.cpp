#include "Controller.h"



Controller::Controller()
{
	strobe = 1;
	offset = 0;
}

void Controller::setButton(byte button, bool value)
{
	switch (button)
	{
	case 0:
		buttons.A = value;
		break;
	case 1:
		buttons.B = value;
		break;
	case 2:
		buttons.select = value;
		break;
	case 3:
		buttons.start = value;
		break;
	case 4:
		buttons.up = value;
		break;
	case 5:
		buttons.down = value;
		break;
	case 6:
		buttons.left = value;
		break;
	case 7:
		buttons.right = value;
		break;
	default:
		break;
	}
}

void Controller::write(byte s)
{
	strobe = s & 0x01;
}

byte Controller::read()
{
	byte result = (convertButtons() >> offset) & 0x01;

	if (strobe) offset = 0;
	else offset++;

	return result;
}

byte Controller::convertButtons()
{
	byte res = 0;
	byte shift = 1;
	if (buttons.A) res = shift;
	if (buttons.B) res |= shift << 1;
	if (buttons.select) res |= shift << 2;
	if (buttons.start) res |= shift << 3;
	if (buttons.up) res |= shift << 4;
	if (buttons.down) res |= shift << 5;
	if (buttons.left) res |= shift << 6;
	if (buttons.right) res |= shift << 7;
	return res;
}
