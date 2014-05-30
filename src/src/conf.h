#pragma once
#define NO_SDL_GLEXT

#define OS_WIN
// #define OS_OSX
// #define OS_LIN

// if APPLE
#if defined(__APPLE__)

#include "AvailabilityMacros.h"
#include "TargetConditionals.h"

#if TARGET_OS_IPHONE
#define OS_iOS
#else
#define OS_OSX
#endif

#endif


#ifdef OS_OSX
#undef OS_WIN
#undef OS_LIN
#endif

#ifdef OS_LIN
#undef OS_WIN
#endif



#include <string>



using namespace std;



extern int screenwidth;
extern int screenheight;

extern string DATAfolder;

extern int how2showFPS;

extern bool screenFullScreen;


void GetEngineStartupConfig();
