#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include "../conf.h"

#include <glew.h>
#ifdef OS_OSX
#include <OpenGL/OpenGL.h>
#endif
#ifdef OS_WIN
#include <gl/GL.h>
#endif

#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <map>

#include <SDL.h>
#include <SDL_opengl.h>

#include <glm.hpp>
#include <ext.hpp>

#include "../EntityComponentSystem/Component.h"
#include "../EntityComponentSystem/Entity.h"
#include "../Containers/Mesh.h"



using namespace std;
using namespace glm;


class MeshRenderer : public Component<Entity>
{
public:
	void construct(vector<void*> values);
	void draw();


	Mesh* mesh2draw;

	Uint32 testTextureID;
	Uint32 testShaderID;




};
