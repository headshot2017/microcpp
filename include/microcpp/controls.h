#ifndef MICROCPP_CONTROLS_H
#define MICROCPP_CONTROLS_H

#include <ulib/ulib.h>
#include <microcpp/vars.h>

typedef struct
{
	bool A, B, X, Y, Left, Up, Right, Down, L, R, Select, Start, Lid;
	u16 Current;

} KEYLIST;

extern struct KEYS
{
	KEYLIST held;
	KEYLIST released;
	KEYLIST newPress;

} Key;

extern struct STYLUS
{
	s16 X, Y, deltaX, deltaY;
	bool newPress, held, released, doubleClick;
} Stylus;


namespace Controls
{
	void read();
	void setStylusDblcFreq(s8 tempo);
}

#endif
