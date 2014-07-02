#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <vector>
#include <SDL.h>
#include <glm.hpp>
#include <ext.hpp>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>


#include "../EntitySystem/Component.h"
#include "../EntitySystem/Entity.h"
#include "SkyBoxRenderer.h"
#include "TextRenderer.h"
#include "MeshRenderer.h"
#include "RigidBody.h"
#include "Transform.h"
#include "../tools.h"

using namespace std;
using namespace glm;


void RigidBody::setSphere(float rad, float mass)
{
		this->transform = this->parent->getComponent<Transform>();
		btTransform t;
		t.setIdentity();
		t.setOrigin(btVector3(transform->position.x, transform->position.y, transform->position.z));
		btSphereShape* mySphere = new btSphereShape(rad); // radius
		btVector3 inertia(0,0,0);
		mySphere->calculateLocalInertia(mass,inertia); 

		btMotionState* mySphereMotionState = new btDefaultMotionState(t);
		btRigidBody::btRigidBodyConstructionInfo sphereinfo(mass,mySphereMotionState,mySphere);
		btRigidBody* mySphereBody = new btRigidBody(sphereinfo);

		this->rigidBody = mySphereBody;
		this->physicsManager->addRigidBody(mySphereBody);
}

void RigidBody::setBox(vec3 whd, float mass)
{
		this->transform = this->parent->getComponent<Transform>();
		btTransform t;
		t.setIdentity();
		t.setOrigin(btVector3(transform->position.x, transform->position.y, transform->position.z));
		btBoxShape* myBox = new btBoxShape(btVector3(whd.x,whd.y,whd.z));

		//makeMessage(numstr(t.getOrigin().getY()));
		btVector3 inertia(0,0,0);
		myBox->calculateLocalInertia(mass,inertia); 

		btMotionState* myBoxMotionState = new btDefaultMotionState(t);
		btRigidBody::btRigidBodyConstructionInfo boxinfo(mass,myBoxMotionState,myBox);
		btRigidBody* myBoxBody = new btRigidBody(boxinfo);

		this->rigidBody = myBoxBody;
		this->physicsManager->addRigidBody(this->rigidBody);
}



void RigidBody::setPlane(vec3 up, float mass)
{
		this->transform = this->parent->getComponent<Transform>();
		btTransform t;
		t.setIdentity();
		t.setOrigin(btVector3(transform->position.x, transform->position.y, transform->position.z));
		btStaticPlaneShape* myPlane = new btStaticPlaneShape(btVector3(up.x,up.y,up.z),0);
		btMotionState* myPlainMotionState = new btDefaultMotionState();
		btRigidBody::btRigidBodyConstructionInfo plaininfo(0,myPlainMotionState,myPlane);
		btRigidBody* myPlainBody = new btRigidBody(plaininfo);

		this->rigidBody = myPlainBody;
		this->physicsManager->addRigidBody(this->rigidBody);
}

RigidBody::RigidBody(PhysicsManager* physicsManager)
{
	this->physicsManager = physicsManager;
}

void RigidBody::update()
{
	btTransform t;
	t.setIdentity();
	rigidBody->getMotionState()->getWorldTransform(t);
	this->parent->getComponent<Transform>()->position = vec3(t.getOrigin().getX(),t.getOrigin().getY(),t.getOrigin().getZ());
}

void RigidBody::updateT()
{
	btTransform t;
	t.setIdentity();
	rigidBody->getMotionState()->getWorldTransform(t);
//	this->parent->getComponent<Transform>()->position = vec3(t.getOrigin().getX(),t.getOrigin().getY(),t.getOrigin().getZ());
	t.setOrigin(btVector3(this->parent->getComponent<Transform>()->position.x, this->parent->getComponent<Transform>()->position.y, this->parent->getComponent<Transform>()->position.z));
}

RigidBody::~RigidBody()
{

}

