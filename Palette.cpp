#include "Palette.h"

Palette::Palette()
{
	for (int i = 0; i < 64; i++) {
		byte r = colors[i] >> 16;
		byte g = colors[i] >> 8;
		byte b = colors[i];
		rgb[i] = RGB(r, g, b);
	}
}

COLORREF Palette::transform(byte value)
{
	return rgb[value];
}
