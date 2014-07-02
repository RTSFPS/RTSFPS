#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <glm.hpp>
#include <ext.hpp>
#include "Transform.h"
#include "../tools.h"

using namespace glm;

Transform::Transform(vec3 position, vec3 rotation, vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

Transform::Transform(vec3 position)
{
	this->position = position;
	this->rotation = vec3(0,0,0);
	this->scale = vec3(1,1,1);
}

mat4 Transform::getDirection()
{
    mat4 orientation = mat4(1);
	///orientation = rotate(orientation, rotation.z, vec3(0,0,1));
    orientation = rotate(orientation, rotation.y, vec3(0,1,0));
	orientation = rotate(orientation, rotation.x, vec3(1,0,0));
	return orientation;
}