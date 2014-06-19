#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0


#include "EventHandler.h"
#include "../EventSystem/EventSystem.h"

class InputHandler :  public EventHandler
{
public:
	EventSender* sender;
	void handleEvent(Event* e);
};