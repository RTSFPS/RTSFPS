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
	this->scale = vec3(0,0,0);
}

vec3 Transform::getDirection()
{
	vec3 res;
	float cP = (float) deg2rad(rotation.x);
	float cY = (float) deg2rad(rotation.y);
	res.x=-cos(cP)*sin(cY);
	res.y=sin(cP);
	res.z=-cos(cP)*cos(cY);
	normalize(res);
	return res;
}