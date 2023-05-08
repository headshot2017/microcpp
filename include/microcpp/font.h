#ifndef MICROCPP_FONT_H
#define MICROCPP_FONT_H

namespace Font
{
	UL_FONT* load(const char* filename);
	int getStringWidth(UL_FONT* font, const char* text);
	int getCharHeight(UL_FONT* font);
	void destroy(UL_FONT* font);
}

#endif
