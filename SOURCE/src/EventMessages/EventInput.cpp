#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include "EventInput.h"
#include "../EventSystem/EventSystem.h"
#include "EventSystemMessages.h"
#include "../conf.h"
#include "../tools.h"
#include "../Entitys/EventHandler.h"

InputEvent::InputEvent()
{
	this->type = input;
	keyState = const_cast<Uint8*> (SDL_GetKeyboardState(NULL));
}

void InputProcessor::registerInEventBus(EventBus* eventBus)
{
	eventBus->registerListener(this);
}

InputProcessor::InputProcessor(EventBus* eventBus, EventSender* sender)
{
	this->sender = sender;
	registerInEventBus(eventBus);
}

InputProcessor::~InputProcessor(){
}

void InputProcessor::call(Event* e)
{
	EventHandler* eventHandler = (EventHandler*)this->parent;
	eventHandler->handleEvent(e);
}