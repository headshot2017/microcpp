#ifndef MICROCPP_MAP_H
#define MICROCPP_MAP_H

#include "vars.h"

namespace Map
{
	MapObj* New(UL_IMAGE* image, const char* filename, int width, int height, int tileWidth, int tileHeight);
	void draw(int scrn, MapObj* map, int x, int y, int width, int height);
	void destroy(MapObj* map);
	void scroll(MapObj* map, int x, int y);
	void space(MapObj* map, int x, int y);
	void setTile(MapObj* map, int x, int y, int tile);
	u16 getTile(MapObj* map, int x, int y);
}

#endif
