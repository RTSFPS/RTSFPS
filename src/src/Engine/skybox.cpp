#define NO_SDL_GLEXT

#include "../conf.h"

#ifdef OS_WIN
#include <Windows.h>
#endif
#include <glew.h>
#ifdef OS_WIN
#include <gl/GL.h>
#endif

#include <string>
#include <stdlib.h>
#include <list>


#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <SDL_opengl.h>

#include <glm.hpp>
#include <ext.hpp>

using namespace glm;
using namespace std;


#include "../tools.h"
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






skybox::skybox(float size)
{
	skyboxtextures[SKY_LEFT] = skybox::loadTexture(DATAfolder+"graph/skybox/left.bmp");
	skyboxtextures[SKY_BACK] = skybox::loadTexture(DATAfolder+"graph/skybox/back.bmp");
	skyboxtextures[SKY_RIGHT] = skybox::loadTexture(DATAfolder+"graph/skybox/right.bmp");
	skyboxtextures[SKY_FRONT] = skybox::loadTexture(DATAfolder+"graph/skybox/front.bmp");
	skyboxtextures[SKY_TOP] = skybox::loadTexture(DATAfolder+"graph/skybox/top.bmp");
	skyboxtextures[SKY_BOTTOM] = skybox::loadTexture(DATAfolder+"graph/skybox/bottom.bmp");

    this->size = size;

	SkyShader = new shader(DATAfolder+"shader/texture");

	vert_back[0] = size / 2;
	vert_back[1] = size / 2;
	vert_back[2] = size / 2;

	vert_back[3] = -size / 2;
	vert_back[4] = size / 2;
	vert_back[5] = size / 2;

	vert_back[6] = -size / 2;
	vert_back[7] = -size / 2;
	vert_back[8] = size / 2;

	vert_back[9] = size / 2;
	vert_back[10] = -size / 2;
	vert_back[11] = size / 2;

	text_back[0] = 0;
	text_back[1] = 0;

	text_back[2] = 1;
	text_back[3] = 0;

	text_back[4] = 1;
	text_back[5] = 1;

	text_back[6] = 0;
	text_back[7] = 1;

	back = new renderer(GL_STATIC_DRAW, GL_TRIANGLE_FAN, SkyShader->prog);
	back->setNumVertex(4);
	back->LoadPoints(vert_back,12);
	back->LoadTextCoords(text_back,8);



	vert_left[0] = -size / 2;
	vert_left[1] = size / 2;
	vert_left[2] = size / 2;

	vert_left[3] = -size / 2;
	vert_left[4] = size / 2;
	vert_left[5] = -size / 2;

	vert_left[6] = -size / 2;
	vert_left[7] = -size / 2;
	vert_left[8] = -size / 2;

	vert_left[9] = -size / 2;
	vert_left[10] = -size / 2;
	vert_left[11] = size / 2;

	text_left[0] = 0;
	text_left[1] = 0;

	text_left[2] = 1;
	text_left[3] = 0;

	text_left[4] = 1;
	text_left[5] = 1;

	text_left[6] = 0;
	text_left[7] = 1;

	left = new renderer(GL_STATIC_DRAW, GL_TRIANGLE_FAN, SkyShader->prog);
	left->setNumVertex(4);
	left->LoadPoints(vert_left,12);
	left->LoadTextCoords(text_left,8);



	vert_front[0] = size / 2;
	vert_front[1] = size / 2;
	vert_front[2] = -size / 2;

	vert_front[3] = -size / 2;
	vert_front[4] = size / 2;
	vert_front[5] = -size / 2;

	vert_front[6] = -size / 2;
	vert_front[7] = -size / 2;
	vert_front[8] = -size / 2;

	vert_front[9] = size / 2;
	vert_front[10] = -size / 2;
	vert_front[11] = -size / 2;

	text_front[0] = 1;
	text_front[1] = 0;

	text_front[2] = 0;
	text_front[3] = 0;

	text_front[4] = 0;
	text_front[5] = 1;

	text_front[6] = 1;
	text_front[7] = 1;


	front = new renderer(GL_STATIC_DRAW, GL_TRIANGLE_FAN, SkyShader->prog);
	front->setNumVertex(4);
	front->LoadPoints(vert_front,12);
	front->LoadTextCoords(text_front,8);




	vert_right[0] = size / 2;
	vert_right[1] = size / 2;
	vert_right[2] = -size / 2;

	vert_right[3] = size / 2;
	vert_right[4] = size / 2;
	vert_right[5] = size / 2;

	vert_right[6] = size / 2;
	vert_right[7] = -size / 2;
	vert_right[8] = size / 2;

	vert_right[9] = size / 2;
	vert_right[10] = -size / 2;
	vert_right[11] = -size / 2;

	text_right[0] = 0;
	text_right[1] = 0;

	text_right[2] = 1;
	text_right[3] = 0;

	text_right[4] = 1;
	text_right[5] = 1;

	text_right[6] = 0;
	text_right[7] = 1;

	right = new renderer(GL_STATIC_DRAW, GL_TRIANGLE_FAN, SkyShader->prog);
	right->setNumVertex(4);
	right->LoadPoints(vert_right,12);
	right->LoadTextCoords(text_right,8);



	

	vert_top[0] = size / 2;
	vert_top[1] = size / 2;
	vert_top[2] = size / 2;

	vert_top[3] = -size / 2;
	vert_top[4] = size / 2;
	vert_top[5] = size / 2;

	vert_top[6] = -size / 2;
	vert_top[7] = size / 2;
	vert_top[8] = -size / 2;

	vert_top[9] = size / 2;
	vert_top[10] = size / 2;
	vert_top[11] = -size / 2;

	text_top[0] = 1;
	text_top[1] = 0;

	text_top[2] = 0;
	text_top[3] = 0;

	text_top[4] = 0;
	text_top[5] = 1;

	text_top[6] = 1;
	text_top[7] = 1;

	top = new renderer(GL_STATIC_DRAW, GL_TRIANGLE_FAN, SkyShader->prog);
	top->setNumVertex(4);
	top->LoadPoints(vert_top,12);
	top->LoadTextCoords(text_top,8);



	

	vert_bottom[0] = size / 2;
	vert_bottom[1] = -size / 2;
	vert_bottom[2] = size / 2;

	vert_bottom[3] = -size / 2;
	vert_bottom[4] = -size / 2;
	vert_bottom[5] = size / 2;

	vert_bottom[6] = -size / 2;
	vert_bottom[7] = -size / 2;
	vert_bottom[8] = -size / 2;

	vert_bottom[9] = size / 2;
	vert_bottom[10] = -size / 2;
	vert_bottom[11] = -size / 2;

	text_bottom[0] = 1;
	text_bottom[1] = 1;

	text_bottom[2] = 0;
	text_bottom[3] = 1;

	text_bottom[4] = 0;
	text_bottom[5] = 0;

	text_bottom[6] = 1;
	text_bottom[7] = 0;

	bottom = new renderer(GL_STATIC_DRAW, GL_TRIANGLE_FAN, SkyShader->prog);
	bottom->setNumVertex(4);
	bottom->LoadPoints(vert_bottom,12);
	bottom->LoadTextCoords(text_bottom,8);


}


skybox::~skybox()
{
	glDeleteTextures(6,&skyboxtextures[0]);

	delete SkyShader;
	delete back;
	delete left;
	delete front;
	delete right;
	delete top;
	delete bottom;
}


void skybox::renderSkyBox(mat4x4 m)
{
	
	glUseProgram(SkyShader->prog);

		int matrix_location = glGetUniformLocation (SkyShader->prog, "matrix");
		glUniformMatrix4fv (matrix_location, 1, GL_FALSE, value_ptr(m));


	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	
	glBindTexture(GL_TEXTURE_2D,skyboxtextures[SKY_BACK]);
	back->Render();

	glBindTexture(GL_TEXTURE_2D,skyboxtextures[SKY_LEFT]);
	left->Render();

	
	glBindTexture(GL_TEXTURE_2D,skyboxtextures[SKY_FRONT]);
	front->Render();


	glBindTexture(GL_TEXTURE_2D,skyboxtextures[SKY_RIGHT]);
	right->Render();


		
	glBindTexture(GL_TEXTURE_2D,skyboxtextures[SKY_TOP]);
	top->Render();



	glBindTexture(GL_TEXTURE_2D,skyboxtextures[SKY_BOTTOM]);
	bottom->Render();

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}
