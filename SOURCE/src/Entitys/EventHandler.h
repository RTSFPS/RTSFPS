#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0
#include <glew.h>
#include "../EntitySystem/Entity.h"
#include "../EventSystem/EventSystem.h"


class EventHandler :  public Entity
{
public:
	virtual void handleEvent(Event* e) = 0;
};
