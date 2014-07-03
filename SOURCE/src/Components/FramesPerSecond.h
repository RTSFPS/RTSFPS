#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0
#include <glew.h>
#include <glm.hpp>
#include <ext.hpp>
#include <string>
#include "../EntitySystem/Component.h"
#include "../EntitySystem/Entity.h"

using namespace glm;
using namespace std;

class FramesPerSecond : public Component<Entity>
{
public:
	unsigned int frames;
	unsigned int currentTime;
	unsigned int lastUpdateTime;
	unsigned int elapsedTime;
	string theFPS;
	FramesPerSecond();
	void calculateFps();
};
