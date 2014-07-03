#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0
#include <glew.h>
#include "../EventSystem/EventSystem.h"
#include "../SystemTools/INIparser.h"
#include "../EventSystem/EventSystem.h"

enum inputeventtype
{
	mousebuttondown,
	mousebuttonup,
	mousemotion,
};

class InputEvent : public Event
{
public:
	InputEvent();
	Uint8 buttonCode;
	inputeventtype inputtype;

	Uint8* keyState;
	int MouseX;
	int MouseY;
};

class InputProcessor : public EventListener
{
public:
	EventSender* sender;
	InputProcessor(EventBus* eventBus, EventSender* sender);
	~InputProcessor();
	void call(Event* e);
	void registerInEventBus(EventBus* eventBus);
};
