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

class Material : public Component<Entity>
{
public:
	string materialID;
	unsigned int shaderID;
	unsigned int textureID;

	Material(string materialID, unsigned int shaderID, unsigned int textureID);
	virtual ~Material();
};
