#pragma once

#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include "../EventSystem/EventSystem.h"

enum systemeventtype
{
	noevent,
	terminateapplication
};

class SystemEvent : public Event
{
public:
	SystemEvent();
	systemeventtype systemEventType;
};

class SystemListener : public EventListener
{
public:
	systemeventtype sysEventType;
	SystemListener(EventBus* eventBus);
	void call(Event* e);
	void registerInEventBus(EventBus* eventBus);
};