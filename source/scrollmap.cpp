#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <string.h>
#include <math.h>

#include <ulib/ulib.h>

#include <microcpp/scrollmap.h>
#include <microcpp/vars.h>

namespace ScrollMap
{
	UL_MAP* New(UL_IMAGE* image, const char* filename, int width, int height, int tileWidth, int tileHeight)
	{
		// Load map from file
		int filesize;
		struct stat file_status;
		if(stat(filename, &file_status) != 0) return 0;
		filesize = file_status.st_size;

		unsigned short * table = new unsigned short[width*height];

		FILE * f = fopen(filename, "r");
		char* buffer = new char[filesize];
		fread(buffer, 1, filesize, f);
		fclose(f);
		// (Now buffer contains the map file)
		int counter = 0;
		char * token;
		unsigned short tile;
		const char delimiters[] = "|";
		token = strtok(buffer, delimiters);
		tile = (unsigned short)atof(token);
		table[counter] = tile;
		counter++;
		while(token != NULL){
			token = strtok(NULL, delimiters);
			if(token != NULL){
				tile = (unsigned short)atof(token);
				table[counter] = tile;
			}
			counter++;
		}
		delete[] buffer;

		UL_MAP * map = ulCreateMap(image, (void*)table, tileWidth, tileHeight, width, height, UL_MF_U16);
		return map;
	}

	void destroy(UL_MAP* map)
	{
		// or just call ulDeleteMap on your own
		ulDeleteMap(map);
	}

	void draw(int screen, UL_MAP* map)
	{
		if (canDraw(screen)) ulDrawMap(map);
	}

	void scroll(UL_MAP* map, int x, int y)
	{
		map->scrollX = x;
		map->scrollY = y;
	}

	void setTile(UL_MAP* map, int x, int y, u16 tile)
	{
		unsigned short* t = (unsigned short*)map->map;
		t[y*map->mapSizeX+x] = tile;
	}

	u16 getTile(UL_MAP* map, int x, int y)
	{
		unsigned short* t = (unsigned short*)map->map;
		return t[y*map->mapSizeX+x];
	}
}
