#pragma once


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



	string ObjectName;

	int matNumber;
	int DrawMode;

	void FreeMemory();

	void createSphere(int nRings, int nSegments, float Radius);
	void createTriangle();

	void createScreenSpaceQuad();

};










