#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <string>
#include <glm.hpp>
#include <ext.hpp>
#include "../EntitySystem/Entity.h"
#include "../Components/RenderManager.h"

using namespace glm;
using namespace std;

Entity* createFramesPerSecondContainer(RenderManager* renderManager,string fontFileName, int size, uint32 color, vec3 position);
Entity* createRenderManagerContainer();
