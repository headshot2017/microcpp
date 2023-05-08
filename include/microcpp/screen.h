/*
*
*/

#ifndef MICROCPP_SCREEN_H
#define MICROCPP_SCREEN_H

#include <microcpp/vars.h>

namespace screen
{
	void init();
	void Switch();
	void toggleDualScreen();
	bool getDualScreen();
	void blit(int scrn, int x, int y, UL_IMAGE* img, int sourcex=-1, int sourcey=-1, int width=-1, int height=-1);
	bool getMainLcd();
	void startDrawing2D();
	void endDrawing();
	void waitForVBL();
	void render();
	int getLayer();
	int getAlphaLevel();
	void setAlpha(int level, int group=0);
	void print(int scrn, int x, int y, const char* text, int color=RGB15(31,31,31));
	void printFont(int scrn, int x, int y, const char* text, UL_FONT* font, int color=RGB15(31,31,31));
	void drawLine(int scrn, int x0, int y0, int x1, int y1, int color=RGB15(31,31,31));
	void drawPoint(int scrn, int x, int y, int color=RGB15(31,31,31));
	void drawRect(int scrn, int x0, int y0, int x1, int y1, int color=RGB15(31,31,31));
	void drawFillRect(int scrn, int x0, int y0, int x1, int y1, int color=RGB15(31,31,31));
	void drawGradientRect(int scrn, int x0, int y0, int x1, int y1, int color1, int color2, int color3, int color4);
	void drawTextBox(int scrn, int x0, int y0, int x1, int y1, const char* text, int color=RGB15(31,31,31));
	void drawTextBoxFont(int scrn, int x0, int y0, int x1, int y1, const char* text, UL_FONT* font, int color=RGB15(31,31,31));
	void setSpaceBetweenScreens(int space);
	void drawTexturedQuad(int scrn, int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, UL_IMAGE* img, int color=RGB15(31,31,31), int sourcex=-1, int sourcey=-1, int width=-1, int height=-1);
	void drawTexturedTriangle(int scrn, int x0, int y0, int x1, int y1, int x2, int y2, UL_IMAGE* img, int color=RGB15(31,31,31), int sourcex=-1, int sourcey=-1, int width=-1, int height=-1);
	void drawQuad(int scrn, int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, int color1=RGB15(31,31,31), int color2=RGB15(31,31,31), int color3=RGB15(31,31,31), int color4=RGB15(31,31,31));
	void drawTriangle(int scrn, int x0, int y0, int x1, int y1, int x2, int y2, int color1=RGB15(31,31,31), int color2=RGB15(31,31,31), int color3=RGB15(31,31,31));
	void setDrawingWindow(int scrn, int x0, int y0, int x1, int y1);
	void setScreenClipping(int scrn, int x0, int y0, int x1, int y1);
	void resetClipping();
	void resetView();
	void moveView(int scrn, int x, int y);
	void scaleView(int scrn, float scaleX, float scaleY);
	void rotateView(int scrn, int angle);
}

#endif
