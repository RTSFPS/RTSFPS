#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0
#include <glew.h>
#include <vector>
#include "EventSystem.h"
#include "../tools.h"

using namespace std;

EventBus::EventBus(eventtype type, EventEngine* eventEngine)
{
	eventEngine->registerEventBus(this);
	this->type = type;
}

void EventBus::registerListener(EventListener* listener)
{
	listeners.push_back(listener);
}

void EventBus::sendEventToListeners(Event* e)
{
	for(unsigned int i = 0; i < listeners.size(); i++)
	{
		listeners[i]->call(e);
	}
}

void EventEngine::registerEventBus(EventBus* eventBus)
{
	busses.push_back(eventBus);
}

void EventEngine::sendEventToRightBus(Event* e)
{
	for(unsigned int i = 0; i < busses.size(); i++)
	{
		if(e->type == busses[i]->type)
		{
			busses[i]->sendEventToListeners(e);
			break;
		}
	}
}

EventSender::EventSender(EventEngine* eventEngine)
{
	this->eventEngine = eventEngine;
}

void EventSender::sendEvent(Event* e)
{
	this->eventEngine->sendEventToRightBus(e);
}
