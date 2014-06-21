#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <string>
#include <SDL.h>
#include <glm.hpp>
#include <ext.hpp>

#include "Renderer.h"
#include "../EntitySystem/Component.h"
#include "../EntitySystem/Entity.h"

using namespace std;
using namespace glm;


class SkyBoxRenderer : public Renderer
{
public:

	SkyBoxRenderer(Component* renderManager);
	virtual ~SkyBoxRenderer();


	void draw(mat4 matrix);
};