#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <glm.hpp>
#include <ext.hpp>
#include "../EntitySystem/Component.h"
#include "../EntitySystem/Entity.h"

using namespace glm;

class Camera : public Component<Entity>
{
public:

	Camera();

	void update();

	mat4 cameraRotateMatrix;
	mat4 cameraTranslateMatrix;


};