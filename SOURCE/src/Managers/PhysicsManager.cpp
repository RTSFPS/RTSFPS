#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include "../conf.h"

#ifdef OS_WIN
#include <Windows.h>
#endif
#include <glew.h>
#ifdef OS_WIN
#include <gl/GL.h>
#include <gl/GLU.h>
#endif
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <map>

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <glm.hpp>
#include <ext.hpp>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>


using namespace std;
using namespace glm;

#include "PhysicsManager.h"




using namespace std;



PhysicsManager::PhysicsManager()
{
	CollisionConfiguration = new btDefaultCollisionConfiguration();
	CollisionDispatcher = new btCollisionDispatcher(CollisionConfiguration);
	Broadphase = new btDbvtBroadphase();
	ConstraintSolver = new btSequentialImpulseConstraintSolver();
	DynamicsWorld = new btDiscreteDynamicsWorld(CollisionDispatcher,Broadphase,ConstraintSolver,CollisionConfiguration);
	DynamicsWorld->setGravity(btVector3(0,-100,0));

}

PhysicsManager::~PhysicsManager()
{
	for(unsigned int i=0;i<RigitBodies.size();i++)
	{
		DynamicsWorld->removeCollisionObject(RigitBodies[i]);
		btMotionState* motionState=RigitBodies[i]->getMotionState();
		btCollisionShape* shape=RigitBodies[i]->getCollisionShape();
		delete RigitBodies[i];
		delete shape;
		delete motionState;
	}

	delete DynamicsWorld;
	delete ConstraintSolver;
	delete Broadphase;
	delete CollisionDispatcher;
	delete CollisionConfiguration;
}

void PhysicsManager::addRigidBody(btRigidBody* rigidBody)
{
	DynamicsWorld->addRigidBody(rigidBody);
	RigitBodies.push_back(rigidBody);
}



