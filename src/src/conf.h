#pragma once

#define OS_WIN


#include <string>



using namespace std;



extern int screenwidth;
extern int screenheight;

extern string DATAfolder;

extern int how2showFPS;

extern bool screenFullScreen;


void GetEngineStartupConfig();