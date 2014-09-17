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

#include <glm.hpp>
#include <ext.hpp>

#include "../tools.h"


using namespace std;
using namespace glm;


#define MAXBONESPERMESH 128 

class Mesh
{
public:

	struct SequenzInfo
	{
		char* Name;
		Uint32 StartingFrame;
		Uint32 EndingFrame;
	};


  vec4* Vertices;
  vec3* Normals;
  vec2* TexCoords;

  vec4* BoneWeights;
  vec4* BoneIndices;

  Uint32*  Indices;

  Uint32 NumFaces;  // if 0 the Mesh is not Indexed
  Uint32 NumVertices;
  Uint32 NumBones;


  Uint32 NumFrames; // if 0 the Mesh is static
  mat4** Matrices;


  vec3 BoundingBoxMin;
  vec3 BoundingBoxMax;

  char* DiffuseTextureName;
  char* NormalTextureName;
  char* SpecularTextureName;

  Uint32 numSequenzies;
  SequenzInfo* Sequenzies;

  unsigned int triangleType;


	Uint32 PointsVBO;
	Uint32 NormalsVBO;
	Uint32 TexCoordsVBO;
	Uint32 BoneWeightsVBO;
	Uint32 BoneIndicesVBO;
	Uint32 vao;
};

