#include "Controller.h"



Controller::Controller()
{
}

byte Controller::read()
{

}

void Controller::write(byte value)
{
	switch (value)
	{
	case 0:
		buttons.A = 1;
		break;
	case 1:
		buttons.B = 1;
		break;
	case 2:
		buttons.select = 1;
		break;
	case 3:
		buttons.start = 1;
		break;
	case 4:
		buttons.up = 1;
		break;
	case 5:
		buttons.down = 1;
		break;
	case 6:
		buttons.left = 1;
		break;
	case 7:
		buttons.right = 1;
		break;
	default:
		break;
	}
}
