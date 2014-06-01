#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <vector>
#include <string>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>


#include "../Engine/OBJparser.h"
#include "../Engine/skybox.h"
#include "../Engine/freecam.h"
#include "../Engine/renderer.h"
#include "../Engine/shader.h"
#include "../Engine/ObjectCreator.h"
#include "../Engine/physics.h"


using namespace std;


class Test
{
public:


	Test();
   ~Test();

   void Draw();


    freecam* myFreecam;

	skybox* mySkybox;

	
	unsigned int textureID;
	/*
	OBJparser* myObj;
	shader* myShader;
	renderer* myRenderer;
	*/

	physics* myPhysic;

	shader* mySphereShader;
	ObjectCreator* mySphere;
	renderer* mySphereRenderer;

	shader* myBoxShader;
	ObjectCreator* myBox;
	renderer* myBoxRenderer;
};