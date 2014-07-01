#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <vector>
#include <string>
#include <glm.hpp>
#include <ext.hpp>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>


using namespace std;
using namespace glm;


class PhysicsManager
{
public:

	btBroadphaseInterface* Broadphase;
	btCollisionConfiguration* CollisionConfiguration;
	btCollisionDispatcher* CollisionDispatcher;
	btConstraintSolver* ConstraintSolver;
	btDynamicsWorld* DynamicsWorld;

	vector<btRigidBody*> RigitBodies;

	PhysicsManager();
   ~PhysicsManager();

   void addRigidBody(btRigidBody* rigidBody);
};