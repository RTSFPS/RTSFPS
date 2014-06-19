#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <SDL.h>

#include <glm.hpp>
#include <ext.hpp>

#include "../Components/Camera.h"
#include "EventHandler.h"
#include "../Components/Camera.h"

using namespace glm;

class FreeCam :  public EventHandler
{
public:
	void handleEvent(Event* e);
};