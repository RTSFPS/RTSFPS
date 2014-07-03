#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0
#include <glew.h>
#include <SDL.h>
#include "InputHandler.h"
#include "../tools.h"
#include "../EventMessages/EventInput.h"
#include "../EventMessages/EventSystemMessages.h"


void InputHandler::handleEvent(Event* e)
{
	InputEvent* inputEvent = (InputEvent*)e;

	if(inputEvent->keyState[SDL_SCANCODE_ESCAPE])
	{
		SystemEvent* sysEvent = new SystemEvent();
		sysEvent->type = systemevent;
		sysEvent->systemEventType = terminateapplication;
		sender->sendEvent(sysEvent);
	}
}
