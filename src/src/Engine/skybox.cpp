#define NO_SDL_GLEXT

#include "../conf.h"

#include <Windows.h>
#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <string>
#include <stdlib.h>
#include <list>


#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <SDL_opengl.h>


using namespace std;


#include "../Tools.h"
#include "skybox.h"
#include "../main.h"


unsigned int skybox::loadTexture(string filename)
{

   unsigned int num=0;


   SDL_Surface *img=IMG_Load(filename.c_str());
   

   if (!img) error("[loadTexture] file "+filename+" load failed!");


   Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

   SDL_Surface *img3 = SDL_CreateRGBSurface(0, 10, 10, 32,
                                   rmask, gmask, bmask, amask);


   SDL_PixelFormat *fmt = img3->format;

   SDL_Surface *img2=SDL_ConvertSurface(img,fmt,0);


   if (!img2) error("[loadTexture] file "+filename+" convertion failed!");

   

   
   glGenTextures(1,&num);

   glBindTexture(GL_TEXTURE_2D,num);

   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);



  
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img2->w, img2->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img2->pixels);

   SDL_FreeSurface(img);
   SDL_FreeSurface(img2);

   return num;
}






void skybox::initSkyBox()
{
	skyboxtextures[SKY_LEFT] = skybox::loadTexture(DATAfolder+"graph/skybox/left.bmp");
	skyboxtextures[SKY_BACK] = skybox::loadTexture(DATAfolder+"graph/skybox/back.bmp");
	skyboxtextures[SKY_RIGHT] = skybox::loadTexture(DATAfolder+"graph/skybox/right.bmp");
	skyboxtextures[SKY_FRONT] = skybox::loadTexture(DATAfolder+"graph/skybox/front.bmp");
	skyboxtextures[SKY_TOP] = skybox::loadTexture(DATAfolder+"graph/skybox/top.bmp");
	skyboxtextures[SKY_BOTTOM] = skybox::loadTexture(DATAfolder+"graph/skybox/bottom.bmp");
}


void skybox::closeSkyBox()
{
	glDeleteTextures(6,&skyboxtextures[0]);
}


void skybox::renderSkyBox(float size)
{
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D,skyboxtextures[SKY_BACK]);

	glColor4f(1.0,1.0,1.0,1.0);

	glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(size/2,size/2,size/2);
		glTexCoord2f(1,0);
		glVertex3f(-size/2,size/2,size/2);
		glTexCoord2f(1,1);
		glVertex3f(-size/2,-size/2,size/2);
		glTexCoord2f(0,1);
		glVertex3f(size/2,-size/2,size/2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,skyboxtextures[SKY_LEFT]);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(-size/2,size/2,size/2);
		glTexCoord2f(1,0);
		glVertex3f(-size/2,size/2,-size/2);
		glTexCoord2f(1,1);
		glVertex3f(-size/2,-size/2,-size/2);
		glTexCoord2f(0,1);
		glVertex3f(-size/2,-size/2,size/2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,skyboxtextures[SKY_FRONT]);
	glBegin(GL_QUADS);
		glTexCoord2f(1,0);
		glVertex3f(size/2,size/2,-size/2);
		glTexCoord2f(0,0);
		glVertex3f(-size/2,size/2,-size/2);
		glTexCoord2f(0,1);
		glVertex3f(-size/2,-size/2,-size/2);
		glTexCoord2f(1,1);
		glVertex3f(size/2,-size/2,-size/2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,skyboxtextures[SKY_RIGHT]);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(size/2,size/2,-size/2);
		glTexCoord2f(1,0);
		glVertex3f(size/2,size/2,size/2);
		glTexCoord2f(1,1);
		glVertex3f(size/2,-size/2,size/2);
		glTexCoord2f(0,1);
		glVertex3f(size/2,-size/2,-size/2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,skyboxtextures[SKY_TOP]);
	glBegin(GL_QUADS);
		glTexCoord2f(1,0);
		glVertex3f(size/2,size/2,size/2);
		glTexCoord2f(0,0);
		glVertex3f(-size/2,size/2,size/2);
		glTexCoord2f(0,1);
		glVertex3f(-size/2,size/2,-size/2);
		glTexCoord2f(1,1);
		glVertex3f(size/2,size/2,-size/2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,skyboxtextures[SKY_BOTTOM]);
	glBegin(GL_QUADS);
		glTexCoord2f(1,1);
		glVertex3f(size/2,-size/2,size/2);
		glTexCoord2f(0,1);
		glVertex3f(-size/2,-size/2,size/2);
		glTexCoord2f(0,0);
		glVertex3f(-size/2,-size/2,-size/2);
		glTexCoord2f(1,0);
		glVertex3f(size/2,-size/2,-size/2);
	glEnd();

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}