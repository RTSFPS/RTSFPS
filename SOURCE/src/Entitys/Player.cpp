#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <SDL.h>
#include <glm.hpp>
#include <ext.hpp>

#include "Player.h"
#include "../tools.h"
#include "../EventMessages/EventInput.h"
#include "../Components/TextRenderer.h"

using namespace glm;

void Player::handleEvent(Event* e)
{
	InputEvent* inputEvent = (InputEvent*)e;
	if(inputEvent->inputtype == keydown)
	{
		if(inputEvent->keyCode == SDLK_SPACE && inputEvent->inputtype == keydown)	makeMessage("player Jumped");
	}
	
	if(inputEvent->inputtype == mousemotion)
	{
	}
}
