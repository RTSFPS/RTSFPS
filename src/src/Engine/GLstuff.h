#pragma once
#define NO_SDL_GLEXT

#include <string>

using namespace std;



unsigned int loadTexture(string filename);
unsigned int createTexture(int w,int h, bool isDepth);

void TraceError();
void CheckFramebufferStatus();



