#pragma once
#include <SDL.h>


struct glImage
{
	int width;
	int height;
	unsigned char *pixels;
};

bool CreateImage(int ww, int hh, glImage &myImage);
void FreeImage(glImage &myImage);
void FlipFromSDL(SDL_Surface* mySDLimage, glImage theImage);


void glputpixel32(int x, int y, unsigned int color, glImage myImage);
unsigned int glgetpixel32(int x, int y, glImage myImage);

void putStaticSprite(int x, int y, glImage myImage);


class glTexturedImage
{
public:

	unsigned int GLtextureID;
	unsigned int w;
	unsigned int h;


//	void BuidFontSprite(const char *c, int numchars, int relativesize);


	void KillTexture();
	


	void createSprite(glImage myImage);
	void FreeImage(glImage &myImage);

	void putSprite(int x, int y);
	void putSpriteRotated(int x, int y, float angle);
	void putSpriteScaledRotated(int x, int y, float angle, float scalefactor);
};

