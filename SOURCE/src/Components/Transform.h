#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <glm.hpp>
#include <ext.hpp>
#include "../EntitySystem/Component.h"
#include "../EntitySystem/Entity.h"

using namespace glm;

class Transform : public Component<Entity>
{
public:
	Transform(vec3 position, vec3 rotation, vec3 scale);
	Transform(vec3 position);
	Transform(){};

	vec3 position, rotation, scale;

	vec3 getDirection();
};