#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0
#include <glew.h>
#include <string>

using namespace std;

class Shader
{
public:


   unsigned int prog;

   Shader(string shadername); 
  ~Shader();

   void useShader();
   void delShader();

private:

	string vsSource;
	string fsSource;
	unsigned int vsID;
	unsigned int fsID;

};
