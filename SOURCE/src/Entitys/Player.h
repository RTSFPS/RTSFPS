#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0


#include "EventHandler.h"

class Player :  public EventHandler
{
public:
	void handleEvent(Event* e);
};