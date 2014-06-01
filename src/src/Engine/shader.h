#pragma once
#define NO_SDL_GLEXT

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
