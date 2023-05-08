#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <string.h>

#include <ulib/ulib.h>

#include <microcpp/image.h>
#include <microcpp/vars.h>

namespace Image
{
	UL_IMAGE* load(const char* filename, int dest)
	{
		int filesize;
		struct stat file_status;
		if (stat(filename, &file_status) != 0) return 0;
		filesize = file_status.st_size;

		FILE * f = fopen(filename, "r");
		char* buffer = new char[filesize];
		fread(buffer, 1, filesize, f);
		fclose(f);

		UL_IMAGE * img = NULL;
		char* ext = strlwr((char*)(filename+strlen(filename)-4));
		if (!strcmp(ext, ".png"))
			img = ulLoadImageFilePNG(buffer, filesize, (!dest) ? UL_IN_RAM : UL_IN_VRAM, UL_PF_PAL8);
		else if (!strcmp(ext, ".gif"))
			img = ulLoadImageFileGIF(buffer, filesize, (!dest) ? UL_IN_RAM : UL_IN_VRAM, UL_PF_PAL8);
		else if (!strcmp(ext, ".jpg") || !strcmp(ext, "jpeg"))
			img = ulLoadImageFileJPG(buffer, filesize, (!dest) ? UL_IN_RAM : UL_IN_VRAM, UL_PF_5550);

		delete[] buffer;
		return img;
	}

	void destroy(UL_IMAGE* img)
	{
		if(img->imgState == UL_STATE_VRAM) ulUnrealizeImage(img);
		ulDeleteImage(img);
	}

	int width(UL_IMAGE* img)
	{
		// or just use img->sizeX on your own
		return img->sizeX;
	}

	int height(UL_IMAGE* img)
	{
		// or just use img->sizeY on your own
		return img->sizeY;
	}

	void scale(UL_IMAGE* img, int width, int height)
	{
		img->stretchX = width;
		img->stretchY = height;
	}

	void rotate(UL_IMAGE* img, int angle, int cx, int cy)
	{
		img->centerX = cx;
		img->centerY = cy;
		img->angle = (32700 * angle) / 511;
	}

	void rotateDegree(UL_IMAGE* img, int angle, int cx, int cy)
	{
		img->centerX = cx;
		img->centerY = cy;
		img->angle = (32700 * angle) / 360;
	}

	void mirrorH(UL_IMAGE* img, bool yes)
	{
		// or just use ulMirrorImageH on your own
		ulMirrorImageH(img, yes);
	}

	void mirrorV(UL_IMAGE* img, bool yes)
	{
		// or just use ulMirrorImageV on your own
		ulMirrorImageV(img, yes);
	}

	void setTint(UL_IMAGE* img, int color)
	{
		// or just use ulSetImageTint on your own
		ulSetImageTint(img, color);
	}

	bool realize(UL_IMAGE* img)
	{
		bool result = (img->imgState != UL_STATE_VRAM);
		if (result) ulRealizeImage(img);
		return result;
	}

	bool unrealize(UL_IMAGE* img)
	{
		bool result = (img->imgState == UL_STATE_VRAM);
		if (result) ulUnrealizeImage(img);
		return result;
	}
}
