#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include "../conf.h"
//#ifdef OS_WIN
//#include <Windows.h>
//#endif

#include <glew.h>
#ifdef OS_WIN
#include <gl/GL.h>
#endif
#ifdef OS_OSX
#include <OpenGL/OpenGL.h>
#endif
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

#include "Shader.h"

using namespace std;


class DrawFont
{
	
public:

	DrawFont(string fontfilename, int size);
   	~DrawFont();

	void glTextOut(int x, int y, string txt, Uint32 color);


private:

	
	TTF_Font* curfont;
	GLuint texture;

	Shader* FontShader;


	int doround(double x);
	int nextpoweroftwo(float x);

	
};
