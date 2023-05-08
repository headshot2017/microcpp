/*
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <ulib/ulib.h>

#include <microcpp/screen.h>
#include <microcpp/vars.h>

int alphaLevel = 100;
bool modifiedScreen = false;
int alphaGroup = 1;
int SCREEN_UP_DISPLAY = 0;
int SCREEN_DOWN_DISPLAY = 1;
int spaceBetweenScreens = 0;
bool dualScreen = false;
bool lcdSwapped = false;

bool canDraw(int scrn) {return !dualScreen || (scrn == SCREEN_UP_DISPLAY && ulGetMainLcd()) || (scrn == SCREEN_DOWN_DISPLAY && !ulGetMainLcd());}

namespace screen
{
	void init()
	{
		screen::startDrawing2D();
	}

	void Switch()
	{
		if (!dualScreen)
		{
			lcdSwap();
			lcdSwapped = !lcdSwapped;
		}
		else
		{
			int tmp = SCREEN_UP_DISPLAY;
			SCREEN_UP_DISPLAY = SCREEN_DOWN_DISPLAY;
			SCREEN_DOWN_DISPLAY = tmp;
		}
	}

	void toggleDualScreen()
	{
		dualScreen = !dualScreen;
		int banks = UL_BANK_A | UL_BANK_B;
		int banksize = 256;
		if (dualScreen)
		{
			if (lcdSwapped) screen::Switch();
			ulInitDualScreenMode();
			lcdSwapped = false;
		}
		else
		{
			ulStopDualScreenMode();
			if (!ulGetMainLcd()) ulSetMainLcd(1);
			banks |= UL_BANK_B | UL_BANK_C;
			banksize += 256;
		}

		ulSetTexVramParameters(banks, VRAM_A, (banksize) << 10);
	}

	bool getDualScreen()
	{
		return dualScreen;
	}

	void blit(int scrn, int x, int y, UL_IMAGE* img, int sourcex, int sourcey, int width, int height)
	{
		if (canDraw(scrn))
		{
			if(height != -1) ulSetImageTile(img, sourcex, sourcey, sourcex+width, sourcey+height);
			else if(sourcey != -1) ulSetImageTile(img, sourcex, sourcey, img->sizeX, img->sizeY);
			ulDrawImageXY(img, x+img->centerX, y+img->centerY);
			//ulResetImageTile(img);
		}
	}

	bool getMainLcd() {
		return ulGetMainLcd();
	}

	void startDrawing2D() {
		ulStartDrawing2D();
	}

	void endDrawing() {
		ulEndDrawing();
	}

	void waitForVBL() {
		ulSyncFrame();
		modifiedScreen = false;
	}

	void render() {
		screen::endDrawing();
		screen::waitForVBL();
		screen::startDrawing2D();
	}

	int getLayer() {
		return alphaGroup;
	}

	int getAlphaLevel() {
		return alphaLevel;
	}

	void setAlpha(int level, int group) {
		if (level == 100) {
			ulSetAlpha(UL_FX_DEFAULT, 0, 0);
			alphaGroup = 1;
			alphaLevel = 100;
		} else {
			if (group < 1) group = alphaGroup;
			level = floor(level * 31 / 99);         // level must actually be between 1 and 31 (0 = wireframe)
			if (level == 0) level = 1;
			ulSetAlpha(UL_FX_ALPHA, level, group);
			if (alphaLevel != level) {
				alphaGroup = group + 1;
				alphaLevel = level;
			}
		}
	}

	void print(int scrn, int x, int y, const char* text, int color) {
		//int color = RGB15(31, 31, 31);
		if (canDraw(scrn)){
			ulSetTextColor(color);
			ulDrawString(x, y, text);
		}
	}

	void printFont(int scrn, int x, int y, const char* text, UL_FONT* font, int color) {
		if (canDraw(scrn)){
			ulSetFont(font);
			ulSetTextColor(color);
			ulDrawString(x, y, text);
			ulSetFont(ul_lcdFont);
		}
	}

	void drawLine(int scrn, int x0, int y0, int x1, int y1, int color) {
		if (canDraw(scrn)){
			ulDrawLine(x0, y0, x1, y1, color);
		}
	}

	void drawPoint(int scrn, int x, int y, int color) {
		if (canDraw(scrn)) ulDrawLine(x, y, x, y, color);
	}

	void drawRect(int scrn, int x0, int y0, int x1, int y1, int color) {
		if (canDraw(scrn))
			ulDrawRect(x0, y0, x1, y1, color);
	}

	void drawFillRect(int scrn, int x0, int y0, int x1, int y1, int color) {
		if (canDraw(scrn))
			ulDrawFillRect(x0, y0, x1, y1, color);
	}

	void drawGradientRect(int scrn, int x0, int y0, int x1, int y1, int color1, int color2, int color3, int color4) {
		if (canDraw(scrn))
			ulDrawGradientRect(x0, y0, x1, y1, color1, color2, color3, color4);
	}

	void drawTextBox(int scrn, int x0, int y0, int x1, int y1, const char* text, int color) {
		ulSetTextColor(color);
		if (canDraw(scrn))
			ulDrawTextBox(x0, y0, x1, y1, text, UL_PF_PAL8);
	}

	void drawTextBoxFont(int scrn, int x0, int y0, int x1, int y1, const char* text, UL_FONT* font, int color) {
		ulSetTextColor(color);
		if (canDraw(scrn)){
			ulSetFont(font);
			ulDrawTextBox(x0, y0, x1, y1, text, UL_PF_PAL8);
			ulSetFont(ul_lcdFont);
		}
	}

	void setSpaceBetweenScreens(int space) {
		spaceBetweenScreens = space;
	}

	void drawTexturedQuad(int scrn, int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, UL_IMAGE* img, int color, int sourcex, int sourcey, int width, int height){
		if (canDraw(scrn)){
			if(height != -1) ulSetImageTile(img, sourcex, sourcey, sourcex+width, sourcey+height);
			else{
				if(sourcey != -1) ulSetImageTile(img, sourcex, sourcey, img->sizeX, img->sizeY);
			}

			ulSetTexture(img);

			//Begins drawing quadliterals
			ulVertexBegin(GL_QUADS);

			//Drawing order for a quad is: top-left, bottom-left, bottom-right, top-right.
			ulVertexColor(color);
			ulVertexUVXY(img->offsetX0, img->offsetY0, x0, y0);
			ulVertexUVXY(img->offsetX0, img->offsetY1, x1, y1);
			ulVertexUVXY(img->offsetX1, img->offsetY1, x2, y2);
			ulVertexUVXY(img->offsetX1, img->offsetY0, x3, y3);

			//End there. You could also continue and draw other quads (issue 4 new vertex commands)
			ulVertexEnd();

			//Auto-increment depth
			ulVertexHandleDepth();

			ulResetImageTile(img);
		}
	}

	void drawTexturedTriangle(int scrn, int x0, int y0, int x1, int y1, int x2, int y2, UL_IMAGE* img, int color, int sourcex, int sourcey, int width, int height){
		if (canDraw(scrn)){
			if(height != -1) ulSetImageTile(img, sourcex, sourcey, sourcex+width, sourcey+height);
			else{
				if(sourcey != -1) ulSetImageTile(img, sourcex, sourcey, img->sizeX, img->sizeY);
			}

			ulSetTexture(img);

			ulVertexBegin(GL_TRIANGLES);

			// Triangle order: top, bottom left, bottom right
			ulVertexColor(color);
			ulVertexUVXY(img->offsetX0, img->offsetY0, x0, y0);
			ulVertexUVXY(img->offsetX0, img->offsetY1, x1, y1);
			ulVertexUVXY(img->offsetX1, img->offsetY1, x2, y2);

			//End there. You could also continue and draw other quads (issue 4 new vertex commands)
			ulVertexEnd();

			//Auto-increment depth
			ulVertexHandleDepth();

			ulResetImageTile(img);
		}
	}

	void drawQuad(int scrn, int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, int color1, int color2, int color3, int color4){
		if (canDraw(scrn)){
			ulDisableTexture();
			
			//Begins drawing quadliterals
			ulVertexBegin(GL_QUADS);

			//Drawing order for a quad is: top-left, bottom-left, bottom-right, top-right.
			ulVertexColor(color1);
			ulVertexXY(x0, y0);
			ulVertexColor(color2);
			ulVertexXY(x1, y1);
			ulVertexColor(color3);
			ulVertexXY(x2, y2);
			ulVertexColor(color4);
			ulVertexXY(x3, y3);

			//End there. You could also continue and draw other quads (issue 4 new vertex commands)
			ulVertexEnd();

			//Auto-increment depth
			ulVertexHandleDepth();
		}
	}

	void drawTriangle(int scrn, int x0, int y0, int x1, int y1, int x2, int y2, int color1, int color2, int color3){
		if (canDraw(scrn)){
			ulDisableTexture();
			
			ulVertexBegin(GL_TRIANGLES);

			// Triangle order: top, bottom left, bottom right
			ulVertexColor(color1);
			ulVertexXY(x0, y0);
			ulVertexColor(color2);
			ulVertexXY(x1, y1);
			ulVertexColor(color3);
			ulVertexXY(x2, y2);

			//End drawing
			ulVertexEnd();

			//Auto-increment depth
			ulVertexHandleDepth();
		}
	}

	void setDrawingWindow(int scrn, int x0, int y0, int x1, int y1)
	{
		if (canDraw(scrn))
			ulSetScreenWindow(x0, y0, x1, y1);
		else if (!modifiedScreen)
			ulResetScreenClipping();

		modifiedScreen = true;
	}

	void setScreenClipping(int scrn, int x0, int y0, int x1, int y1)
	{
		if (canDraw(scrn))
			ulSetScreenClipping(x0, y0, x1, y1);
		else if (!modifiedScreen)
			ulResetScreenClipping();

		modifiedScreen = true;
	}

	void resetClipping()
	{
		ulResetScreenClipping();
	}

	void resetView()
	{
		ulResetScreenClipping();
	}

	void moveView(int scrn, int x, int y)
	{
		if (canDraw(scrn))
			ulMoveScreenView(x, y);
		else if (!modifiedScreen)
			ulResetScreenView();

		modifiedScreen = true;
	}

	void scaleView(int scrn, float scaleX, float scaleY)
	{
		if (canDraw(scrn))
			ulScaleScreenView(floattof32(scaleX), floattof32(scaleY));
		else if (!modifiedScreen)
			ulResetScreenView();

		modifiedScreen = true;
	}

	void rotateView(int scrn, int angle)
	{
		if (canDraw(scrn))
			ulRotateScreenView(angle);
		else if (!modifiedScreen)
			ulResetScreenView();

		modifiedScreen = true;
	}
}
