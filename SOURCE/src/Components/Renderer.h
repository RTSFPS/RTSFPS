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

class Renderer : public Component<Entity>
{
public:

	virtual ~Renderer();

	unsigned int numVertex;

	unsigned int positionVBO;
	unsigned int numPositions;

	unsigned int uvVBO;
	unsigned int numUV;

	unsigned int vao;

	unsigned int triangleType;

	unsigned int indicesVBO;
	unsigned int numIndices;

	virtual void draw();

	void loadPositionsFromVertexBuffer(void* data,unsigned int numPositions);
	void loadTextCoordsFromVertexBuffer(void* data, unsigned int numUVs);

	void loadPositionsFromFloatBuffer(void* data, unsigned int numPositions);
	void loadIndicesFromFloatBuffer(void* data, unsigned int numIndices);
};