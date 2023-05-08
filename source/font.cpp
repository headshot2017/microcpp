#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/dir.h>

#include <ulib/ulib.h>

#include <microcpp/font.h>
#include <microcpp/vars.h>

namespace Font
{
	UL_FONT* load(const char* filename)
	{
		int filesize;
		struct stat file_status;
		if(stat(filename, &file_status) != 0){ // file doesn't exist
			return 0;
		}
		filesize = file_status.st_size;

		FILE * f = fopen(filename, "r");
		char* buffer = new char[filesize];
		fread(buffer, 1, filesize, f);
		fclose(f);

		UL_FONT * font;
		font = ulLoadFontFile(buffer, filesize);
		delete[] buffer;

		if(font == NULL){
			return 0;
		}

		return font;
	}

	int getStringWidth(UL_FONT* font, const char* text)
	{
		if(font != NULL) ulSetFont(font);
		int width = ulGetStringWidth(text);
		if(font != NULL) ulSetFont(ul_lcdFont);
		return width;
	}

	int getCharHeight(UL_FONT* font)
	{
		// OR you can just simply use font->charHeight and avoid this MicroLua-like function
		return font->charHeight;
	}

	void destroy(UL_FONT* font)
	{
		if (font->img->imgState == UL_STATE_VRAM) ulUnrealizeImage(font->img);
		ulDeleteImage(font->img);
		free(font);
	}
}
