#pragma once

#include <string>

using namespace std;

struct Point
{
	float x,y,z;
};

struct Normal
{
	float x,y,z;
};

struct Color
{
	float r,g,b,a;
};

struct UV
{
	float u,v;
};



struct aMesh
{
	Point* Points;
	unsigned int numPoints;

	Normal* Normals;
	unsigned int numNormals;

	Color* Colors;
	unsigned int numColors;

	UV* UVs;
	unsigned int numUVs;

	float posX,posY,posZ;
	float rotX,rotY,rotZ,rotAngle;
	float scalX,scalY,scalZ;

	unsigned int MaterialID;



// animation

	bool animation;

	unsigned int timeStamp;

	bool PointsChanged;
	bool NormalsChanged;
	bool ColorsChanged;
	bool UVsChanged;
	bool PositionChanged;
	

// internal
	
	unsigned int PointsVBO;
	unsigned int NormalsVBO;
	unsigned int ColorsVBO;
	unsigned int UVsVBO;
	unsigned int vao;
};





struct aObject
{

	string ObjectName;

	
	aMesh* Meshes;
	unsigned int numMeshes;
	
};