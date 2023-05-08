#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <string.h>
#include <math.h>

#include <ulib/ulib.h>

#include <microcpp/map.h>
#include <microcpp/vars.h>

void blitTile(int x, int y, UL_IMAGE * img, int sourcex, int sourcey, int width, int height)
{
    ulSetImageTile(img, sourcex, sourcey, sourcex+width, sourcey+height);
    ulDrawImageXY(img, x, y);
    ulResetImageTile(img);
}

namespace Map
{
	MapObj* New(UL_IMAGE* image, const char* filename, int width, int height, int tileWidth, int tileHeight)
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
		tile = atoi(token);
		table[counter] = tile;
		counter++;
		while(token != NULL){
			token = strtok(NULL, delimiters);
			if(token != NULL){
				tile = atoi(token);
				table[counter] = tile;
			}
			counter++;
		}
		free(token);
		delete[] buffer;

		MapObj * map = new MapObj;
		//map = malloc(sizeof(image) + sizeof(table) + 8*sizeof(int));
		map->width = width;
		map->height = height;
		map->tileWidth = tileWidth;
		map->tileHeight = tileHeight;
		map->scrollX = 0;
		map->scrollY = 0;
		map->spaceX = 0;
		map->spaceY = 0;
		map->image = image;
		map->table = table;
		return map;
	}

	void draw(int scrn, MapObj* map, int x, int y, int width, int height)
	{
		if(!canDraw(scrn))
			return;

		int i, j;
		int xx, yy;
		unsigned short tile;
		int spaceX, spaceY;
		for(i=map->scrollY;i<map->scrollY+height;i++){ // Y
			for(j=map->scrollX;j<map->scrollX+width;j++){ // X
				//tile = map->table[i*map->height+j]; // quote half life scientist "my god, what are you doing?"
				tile = map->table[i*map->width+j];
				
				xx = tile % (map->image->sizeX / map->tileWidth);
				yy = tile / (map->image->sizeX / map->tileWidth);
				spaceX = 0;
				spaceY = 0;
				if(j != map->scrollX) spaceX = map->spaceX;
				if(i != map->scrollY) spaceY = map->spaceY;
				if(i >= 0 && i < map->height && j >= 0 && j < map->width){
					blitTile(x+(j-map->scrollX)*(map->tileWidth+spaceX), y+(i-map->scrollY)*(map->tileHeight+spaceY),
						map->image, xx * map->tileWidth, yy * map->tileHeight,
						map->tileWidth, map->tileHeight);
				}
			}
		}
	}

	void destroy(MapObj* map)
	{
		delete[] map->table;
		delete map;
	}

	void scroll(MapObj* map, int x, int y)
	{
		map->scrollX = x;
		map->scrollY = y;
	}

	void space(MapObj* map, int x, int y)
	{
		map->spaceX = x;
		map->spaceY = y;
	}

	void setTile(MapObj* map, int x, int y, int tile)
	{
		map->table[y*map->width+x] = tile;
	}

	u16 getTile(MapObj* map, int x, int y)
	{
		return map->table[y*map->width+x];
	}
}
