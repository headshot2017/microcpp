#include <stdlib.h>
#include <stdio.h>

#include <ulib/ulib.h>

#include <microcpp/controls.h>
#include <microcpp/vars.h>

KEYS Key;
STYLUS Stylus;

namespace Controls
{
	void read()
	{
		ulReadKeys(0);

		Stylus.X = ul_keys.touch.x;
		Stylus.Y = ul_keys.touch.y;
		Stylus.held = ul_keys.touch.held;
		Stylus.released = ul_keys.touch.released;
		Stylus.doubleClick = ul_keys.touch.doubleClick;
		Stylus.deltaX = ul_keys.touch.deltaX;
		Stylus.deltaY = ul_keys.touch.deltaY;
		Stylus.newPress = ul_keys.touch.click;

		Key.held.A = ul_keys.held.A;
		Key.held.B = ul_keys.held.B;
		Key.held.X = ul_keys.held.X;
		Key.held.Y = ul_keys.held.Y;
		Key.held.L = ul_keys.held.L;
		Key.held.R = ul_keys.held.R;
		Key.held.Up = ul_keys.held.up;
		Key.held.Down = ul_keys.held.down;
		Key.held.Left = ul_keys.held.left;
		Key.held.Right = ul_keys.held.right;
		Key.held.Start = ul_keys.held.start;
		Key.held.Select = ul_keys.held.select;
		Key.held.Lid = ul_keys.held.lid;
		Key.held.Current = ul_keys.held.value;

		Key.released.A = ul_keys.released.A;
		Key.released.B = ul_keys.released.B;
		Key.released.X = ul_keys.released.X;
		Key.released.Y = ul_keys.released.Y;
		Key.released.L = ul_keys.released.L;
		Key.released.R = ul_keys.released.R;
		Key.released.Up = ul_keys.released.up;
		Key.released.Down = ul_keys.released.down;
		Key.released.Left = ul_keys.released.left;
		Key.released.Right = ul_keys.released.right;
		Key.released.Start = ul_keys.released.start;
		Key.released.Select = ul_keys.released.select;
		Key.released.Lid = ul_keys.released.lid;
		Key.released.Current = ul_keys.released.value;

		Key.newPress.A = ul_keys.pressed.A;
		Key.newPress.B = ul_keys.pressed.B;
		Key.newPress.X = ul_keys.pressed.X;
		Key.newPress.Y = ul_keys.pressed.Y;
		Key.newPress.L = ul_keys.pressed.L;
		Key.newPress.R = ul_keys.pressed.R;
		Key.newPress.Up = ul_keys.pressed.up;
		Key.newPress.Down = ul_keys.pressed.down;
		Key.newPress.Left = ul_keys.pressed.left;
		Key.newPress.Right = ul_keys.pressed.right;
		Key.newPress.Start = ul_keys.pressed.start;
		Key.newPress.Select = ul_keys.pressed.select;
		Key.newPress.Lid = ul_keys.pressed.lid;
		Key.newPress.Current = ul_keys.pressed.value;
	}

	void setStylusDblcFreq(s8 tempo)
	{
		// or just use ulSetTouchpadDoubleClickDelay yourself
		ulSetTouchpadDoubleClickDelay(tempo);
	}
}
