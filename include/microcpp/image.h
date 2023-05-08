#ifndef MICROCPP_IMAGE_H
#define MICROCPP_IMAGE_H

namespace Image
{
	UL_IMAGE* load(const char* filename, int dest);
	void destroy(UL_IMAGE* img);

	int width(UL_IMAGE* img);
	int height(UL_IMAGE* img);

	void scale(UL_IMAGE* img, int width, int height);
	void rotate(UL_IMAGE* img, int angle, int cx=0, int cy=0);
	void rotateDegree(UL_IMAGE* img, int angle, int cx=0, int cy=0);
	void mirrorH(UL_IMAGE* img, bool yes);
	void mirrorV(UL_IMAGE* img, bool yes);
	void setTint(UL_IMAGE* img, int color);

	bool realize(UL_IMAGE* img);
	bool unrealize(UL_IMAGE* img);
}

#endif
