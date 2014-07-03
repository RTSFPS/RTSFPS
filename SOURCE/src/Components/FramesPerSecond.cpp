#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0
#include <glew.h>
#include <glm.hpp>
#include <ext.hpp>

#include <SDL.h>
#include <string>
#include "FramesPerSecond.h"
#include "../tools.h"
#include "TextRenderer.h"

using namespace glm;
using namespace std;



FramesPerSecond::FramesPerSecond()
{
	this->currentTime = 0;
	this->elapsedTime = 0;
	this->frames = 0;
	this->lastUpdateTime = 0;
	this->theFPS = "";
}

void FramesPerSecond::calculateFps()
{
		frames++;
		currentTime = SDL_GetTicks();
		elapsedTime = currentTime - lastUpdateTime;
		
		if(elapsedTime >= 1000)
		{
			string fps = "fps";
		    theFPS = floatstr((float) frames * 1000.0f / elapsedTime).append(fps);
			frames = 0;
			lastUpdateTime = currentTime;
		}
		this->parent->getComponent<TextRenderer>()->changeText(this->theFPS);
}
