#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <string>

#include <glm.hpp>
#include <ext.hpp>

using namespace std;
using namespace glm;



unsigned int loadTexture(string filename);
unsigned int createTexture(int w,int h, bool isDepth);

void TraceError();
void CheckFramebufferStatus();



