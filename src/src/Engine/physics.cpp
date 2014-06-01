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

#include "../Engine/shader.h"
#include "../Engine/GLstuff.h"
#include "../Engine/SDLgraph.h"
#include "../Engine/OBJparser.h"
#include "../Engine/skybox.h"
#include "../Engine/freecam.h"
#include "../Engine/renderer.h"
#include "../Engine/ObjectCreator.h"
#include "../Engine/keys.h"
#include "../tools.h"
#include "physics.h"




using namespace std;



physics::physics()
{
	CollisionConfiguration = new btDefaultCollisionConfiguration();
	CollisionDispatcher = new btCollisionDispatcher(CollisionConfiguration);
	Broadphase = new btDbvtBroadphase();
	ConstraintSolver = new btSequentialImpulseConstraintSolver();
	DynamicsWorld = new btDiscreteDynamicsWorld(CollisionDispatcher,Broadphase,ConstraintSolver,CollisionConfiguration);
	DynamicsWorld->setGravity(btVector3(0,-10,0));

		


}


physics::~physics()
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









btRigidBody* physics::addSphere(vec3 xyz, float rad, float mass)
{
		btTransform t;
		t.setIdentity();
		t.setOrigin(btVector3(xyz.x,xyz.y,xyz.z));
		btSphereShape* mySphere = new btSphereShape(rad); // radius
		btVector3 inertia(0,0,0);
		mySphere->calculateLocalInertia(mass,inertia); 

		btMotionState* mySphereMotionState = new btDefaultMotionState(t);
		btRigidBody::btRigidBodyConstructionInfo sphereinfo(mass,mySphereMotionState,mySphere);
		btRigidBody* mySphereBody = new btRigidBody(sphereinfo);

		DynamicsWorld->addRigidBody(mySphereBody);

		RigitBodies.push_back(mySphereBody);

		return mySphereBody;
}


btRigidBody* physics::addBox(vec3 center, vec3 whd, float mass)
{
		btTransform t;
		t.setIdentity();
		t.setOrigin(btVector3(center.x,center.y,center.z));
		btBoxShape* myBox = new btBoxShape(btVector3(whd.x,whd.y,whd.z));


		btVector3 inertia(0,0,0);
		myBox->calculateLocalInertia(mass,inertia); 

		btMotionState* myBoxMotionState = new btDefaultMotionState(t);
		btRigidBody::btRigidBodyConstructionInfo boxinfo(mass,myBoxMotionState,myBox);
		btRigidBody* myBoxBody = new btRigidBody(boxinfo);

		DynamicsWorld->addRigidBody(myBoxBody);

		RigitBodies.push_back(myBoxBody);

		return myBoxBody;
}



btRigidBody* physics::addPlain(vec3 center, vec3 up, float mass)
{
		btTransform t;
		t.setIdentity();
		t.setOrigin(btVector3(center.x, center.y,center.z));
		btStaticPlaneShape* myPlane = new btStaticPlaneShape(btVector3(up.x,up.y,up.z),0);
		btMotionState* myPlainMotionState = new btDefaultMotionState();
		btRigidBody::btRigidBodyConstructionInfo plaininfo(0,myPlainMotionState,myPlane);
		btRigidBody* myPlainBody = new btRigidBody(plaininfo);

		DynamicsWorld->addRigidBody(myPlainBody);

		RigitBodies.push_back(myPlainBody);

		return myPlainBody;
}