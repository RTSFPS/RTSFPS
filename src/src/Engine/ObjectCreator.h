#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <string>

using namespace std;

class ObjectCreator
{
public:
	
	struct Vertex
	{
		float x,y,z;
		float nx,ny,nz;
		float r,g,b;
		float u,v;
	};

	bool VertexPosition;
	bool VertexNormals;
	bool VertexColor;
	bool VertexUV;

	Vertex* Vertices;
	unsigned int numVertex;



	float* Points;
	unsigned int numPoints;

	float* Normals;
	unsigned int numNormals;

	float* UVs;
	unsigned int numUVs;

	float* Colors;
	unsigned int numColors;



	string ObjectName;

	int matNumber;
	int DrawMode;

	void FreeMemory();

	void createSphere(int nRings, int nSegments, float Radius);
	void createBox(float x, float y, float z);

	void createTriangle();

	void createScreenSpaceQuad();

};










