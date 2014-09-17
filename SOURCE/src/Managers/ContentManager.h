#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include "../conf.h"

#ifdef OS_WIN
#include <Windows.h>
#endif
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
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <glm.hpp>
#include <ext.hpp>

#include "../Containers/Mesh.h"

using namespace std;
using namespace glm;

class ContentManager
{
public:
	static ContentManager* exemplar();
	void loadTexture(string textureName);
	void loadShader(string shaderName);
	void loadSkyBoxTexture(string filePath);
	void loadMesh(string filename);

	void deleteMesh(string name);

	static ContentManager* instance;
	map<string, unsigned int> shaderIds;
	map<string, unsigned int> textureIds;
	map<string, Mesh*> meshes;
};