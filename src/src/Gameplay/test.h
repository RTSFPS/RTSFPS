#pragma once
#define NO_SDL_GLEXT


#include <string>

#include "../Engine/OBJparser.h"
#include "../Engine/skybox.h"
#include "../Engine/freecam.h"

using namespace std;



class Test
{
public:


	Test();
   ~Test();

   void Draw();


    freecam* myFreecam;

	skybox* mySkybox;

	OBJparser* myObj;
	unsigned int textureID;


};