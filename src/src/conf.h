#pragma once
#define NO_SDL_GLEXT

// #define OS_WIN
//#define OS_OSX
#define OS_LIN

#include <string>



using namespace std;



extern int screenwidth;
extern int screenheight;

extern string DATAfolder;

extern int how2showFPS;

extern bool screenFullScreen;


void GetEngineStartupConfig();
