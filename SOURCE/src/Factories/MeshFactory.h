#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <string>
#include <glm.hpp>
#include <ext.hpp>
#include "../Components/Mesh.h"
#include "../Components/RenderManager.h"

using namespace glm;
using namespace std;

enum  filetype
{
	obj
};

enum primitivetype
{
	plane
};


Mesh* createMesh(filetype type, string fileName);


Mesh* loadObj(string fileName);

Mesh* createPrimitive(primitivetype type);