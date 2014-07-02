#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <SDL.h>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include <glm.hpp>
#include <ext.hpp>

#include "CharacterController.h"
#include "RigidBody.h"
#include "../conf.h"
#include "../tools.h"


using namespace glm;


void CharacterController::move(vec3 pos)
{
	
	Transform* transform = this->parent->getComponent<Transform>();
	RigidBody* rigidBodyComponnent = this->parent->getComponent<RigidBody>();
	btRigidBody* rigidBody = rigidBodyComponnent->rigidBody;


	vec4 lookvec = transform->getDirection()*vec4(pos,1);
	btVector3 vec = btVector3(lookvec.x,lookvec.y,lookvec.z);

	rigidBody->setLinearVelocity(vec);


}


void CharacterController::rotate(vec3 rot)
{
	Transform* transform = this->parent->getComponent<Transform>();
	

	 transform->rotation.y = fmodf(transform->rotation.y, 360.0f);

	if (transform->rotation.y<0) transform->rotation.y += 360.0f;

	if(transform->rotation.x > 90.0f) transform->rotation.x = 90.0f;
    else if(transform->rotation.x < -90.0f) transform->rotation.x = -90.0f;
	
		transform->rotation.x += rot.y;
		transform->rotation.y += rot.x;
		transform->rotation.z += rot.z;
}