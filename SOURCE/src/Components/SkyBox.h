#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <string>
#include <glm.hpp>
#include <ext.hpp>
#include "../EntitySystem/Component.h"
#include "../EntitySystem/Entity.h"

using namespace std;
using namespace glm;

class SkyBox : public Component<Entity>
{
public:
	SkyBox();

	float skyboxVertices[24];
	unsigned int  skyboxIndices[24]; 

};