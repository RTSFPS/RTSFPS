#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0


#include "EventHandler.h"

class Player :  public EventHandler
{
public:
	
	float mouseSpeed;
	float keyboardSpeed;

	void handleEvent(Event* e);

	Player();
};