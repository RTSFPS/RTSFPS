#pragma once

#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <vector>
#include <SDL.h>
#include "../EntitySystem/Component.h"
#include "../EntitySystem/Entity.h"

using namespace std;

enum eventtype
{
	input,
	systemevent
};

class Event
{
public:
	eventtype type;
};

/*
__interface IEventHandler
{
	void handleEvent(Event* e);
};
*/

class EventBus;

class EventListener : public Component<Entity>
{
public:
	void registerInEventBus(EventBus* eventBus);
	virtual void call(Event* e) = 0;
};

class EventEngine;

class EventSender : public Component<Entity>
{
public:
	EventEngine* eventEngine;
	EventSender(EventEngine* eventEngine);
	void sendEvent(Event* e);
};


class EventBus : public Component<Entity>
{
public:
	vector<EventListener*> listeners;
	eventtype type;
	EventBus(eventtype type, EventEngine* eventEngine);
	void registerListener(EventListener* listener);
	void sendEventToListeners(Event* e);
};

class EventEngine
{
public:
	vector<EventBus*> busses;
	void registerEventBus(EventBus* eventBus);
	void sendEventToRightBus(Event* e);
};






