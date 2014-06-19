#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <string>

using namespace std;

class shader
{
public:


   unsigned int prog;

   shader(string shadername); 
  ~shader();

   void useShader();
   void delShader();

private:

	string vsSource;
	string fsSource;
	unsigned int vsID;
	unsigned int fsID;

};
