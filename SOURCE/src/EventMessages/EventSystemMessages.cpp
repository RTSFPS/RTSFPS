#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include "../EventSystem/EventSystem.h"
#include "EventSystemMessages.h"

#include "../tools.h"

SystemEvent::SystemEvent()
{
	systemEventType = noevent;
	this->type = systemevent;
}

void SystemListener::call(Event* e)
{
	this->sysEventType = terminateapplication;
}

void SystemListener::registerInEventBus(EventBus* eventBus)
{
	eventBus->registerListener(this);
}

SystemListener::SystemListener(EventBus* eventBus)
{
	registerInEventBus(eventBus);
}
