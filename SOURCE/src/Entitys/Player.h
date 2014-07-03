#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0
#include <glew.h>
#include <glm.hpp>
#include <ext.hpp>
#include "EventHandler.h"

using namespace glm;

class Player :  public EventHandler
{
public:
	
	float mouseSpeed;
	float keyboardSpeed;

	void handleEvent(Event* e);
	void move(vec3 pos);
	void rotate(vec3 rot);

	Player();
};
