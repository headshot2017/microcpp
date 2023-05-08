/*
*
*/

#ifndef MICROCPP_VARS_H
#define MICROCPP_VARS_H

#include <nds.h>
#include <ulib/ulib.h>

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 192

#define TO_RAM  0
#define TO_VRAM  1

#define SCREEN_UP 1
#define SCREEN_DOWN 0

#define ALPHA_RESET 100

#define LED_ON PM_LED_ON
#define LED_SLEEP PM_LED_SLEEP
#define LED_BLINK PM_LED_BLINK

#define PLAY_LOOP 0
#define PLAY_ONCE 1

#define KEY_A 0x1
#define KEY_B 0x2
#define KEY_SELECT 0x4
#define KEY_START 0x8
#define KEY_RIGHT 0x10
#define KEY_LEFT 0x20
#define KEY_UP 0x40
#define KEY_DOWN 0x80
#define KEY_R 0x100
#define KEY_L 0x200
#define KEY_X 0x400
#define KEY_Y 0x800
#define KEY_TOUCH 0x1000
#define KEY_LID 0x2000

extern bool canDraw(int scrn);

typedef struct mapObj{
    UL_IMAGE * image;
    unsigned short * table;
    int width, height;
    int tileWidth, tileHeight;
    int scrollX, scrollY;
    int spaceX, spaceY;
} MapObj;

#endif
