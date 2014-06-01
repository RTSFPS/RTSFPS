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


class physics
{
public:

	btBroadphaseInterface* Broadphase;
	btCollisionConfiguration* CollisionConfiguration;
	btCollisionDispatcher* CollisionDispatcher;
	btConstraintSolver* ConstraintSolver;
	btDynamicsWorld* DynamicsWorld;

	vector<btRigidBody*> RigitBodies;


	physics();
   ~physics();


   btRigidBody* addSphere(vec3 xyz, float rad, float mass);
   btRigidBody* addBox(vec3 center, vec3 whd, float mass);
   btRigidBody* addPlain(vec3 center, vec3 up, float mass);

};