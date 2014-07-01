#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <glm.hpp>
#include <ext.hpp>
#include "Transform.h"
#include "../EntitySystem/Component.h"
#include "../EntitySystem/Entity.h"

using namespace glm;

class CharacterController : public Component<Entity>
{
public:

		void move(vec3 pos);
		void rotate(vec3 rot);
};