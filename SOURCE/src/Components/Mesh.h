#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0


#include <glm.hpp>
#include <ext.hpp>
#include <string>

#include "../SystemTools/OBJparser.h"
#include "../EntitySystem/Component.h"
#include "../EntitySystem/Entity.h"

using namespace glm;
using namespace std;



struct Vertex
{
	vec3 position;	
	vec3 normal;
	vec2 textcoord; 
};


class Mesh : public Component<Entity>
{
public:
	Vertex* verticies;
	unsigned int numVertex;

	string materialName;

	unsigned int triangleType;

	Mesh();

};



