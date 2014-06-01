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

	shader* myShader;
	renderer* myRenderer;
	
	ObjectCreator* mySphere;
	renderer* mySphereRenderer;

	btBroadphaseInterface* Broadphase;
	btCollisionConfiguration* CollisionConfiguration;
	btCollisionDispatcher* CollisionDispatcher;
	btConstraintSolver* ConstraintSolver;
	btDynamicsWorld* DynamicsWorld;


	vector<btRigidBody*> bodies;

	btRigidBody* addSphere(vec3 xyz, float rad);

	btRigidBody* myPlainBody;
	btRigidBody* mySphereBody;
};