#pragma once


#include <string>

#include "../Engine/OBJparser.h"

using namespace std;



class Test
{
public:


	Test();
   ~Test();

   void Draw();

   	glTexturedImage tx;

	OBJparser* myObj;
	unsigned int textureID;


	float r;
};