#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0
#include <glew.h>
#include <vector>
#include <SDL.h>
#include <glm.hpp>
#include <ext.hpp>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include "../EntitySystem/Component.h"
#include "../EntitySystem/Entity.h"
#include "../Components/Transform.h"
#include "SkyBoxRenderer.h"
#include "TextRenderer.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "../Managers/PhysicsManager.h"

using namespace std;
using namespace glm;

class RigidBody : public Component<Entity>
{
public:

	void setSphere(float rad, float mass);
	void setPlane(vec3 up, float mass);
	void setBox(vec3 whd, float mass);
	void update();
	void updateT();
	btRigidBody* rigidBody;
	Transform* transform;
	PhysicsManager* physicsManager;
	RigidBody(PhysicsManager* physicsManager);
	~RigidBody();
};
