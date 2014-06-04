#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include "../EntitySystem/Entity.h"

class Node:
	public Entity

{
public:


	virtual void update(void *data) = 0;
	virtual void render() = 0;
};