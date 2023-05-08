#ifndef MICROCPP_COLOR_H
#define MICROCPP_COLOR_H

#include <inttypes.h>

namespace Color
{
	int new256(uint8_t r, uint8_t g, uint8_t b);
	int newHSL(float h, float s, float l);
}

#endif
