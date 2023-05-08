#ifndef MICROCPP_SCROLLMAP_H
#define MICROCPP_SCROLLMAP_H

namespace ScrollMap
{
	UL_MAP* New(UL_IMAGE* image, const char* filename, int width, int height, int tileWidth, int tileHeight);
	void destroy(UL_MAP* map);
	void draw(int screen, UL_MAP* map);
	void scroll(UL_MAP* map, int x, int y);
	void setTile(UL_MAP* map, int x, int y, u16 tile);
	u16 getTile(UL_MAP* map, int x, int y);
}

#endif
