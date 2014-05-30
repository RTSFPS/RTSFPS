#pragma once
#define NO_SDL_GLEXT

#include <string>

#include <glm.hpp>
#include <ext.hpp>

using namespace std;
using namespace glm;



unsigned int loadTexture(string filename);
unsigned int createTexture(int w,int h, bool isDepth);

void TraceError();
void CheckFramebufferStatus();



