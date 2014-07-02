#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0


#include <glm.hpp>
#include <ext.hpp>

#include "../SystemTools/OBJparser.h"
#include "Mesh.h"

using namespace glm;


Mesh::Mesh()
{
	verticies=NULL;
	numVertex=0;
}


