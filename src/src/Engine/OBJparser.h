#pragma once


#include <string>



using namespace std;

class OBJparser
{
public:

	struct Face
	{
		float x1,y1,z1;
		float u1,v1;
		float nx1,ny1,nz1;

		float x2,y2,z2;
		float u2,v2;
		float nx2,ny2,nz2;

		float x3,y3,z3;
		float u3,v3;
		float nx3,ny3,nz3;		
	};


	struct Vertex
	{
		float x,y,z;
		float nx,ny,nz;
		float u,v;
	};

	Vertex* Vertices;
	unsigned int numVertex;


	int matNumber;


	Face *Faces;
	int numFaces;


	string scenename;

	OBJparser(string filename);
	~OBJparser();

	OBJparser();

	bool LoadOBJfile(std::string filename);

	unsigned int frameNumber;

private:

	

	struct Vector3f
	{ 
		float x,y,z;
	};
	struct Vector2f
	{
		float u,v;
	};
	struct FaceType
	{
		int vIndex1, vIndex2, vIndex3;
		int tIndex1, tIndex2, tIndex3;
		int nIndex1, nIndex2, nIndex3;
	};

	int vertexCount;
	int textureCount;
	int normalCount;
	int faceCount;


	Vector3f *vertices, *normals;
	Vector2f *texcoords;
	FaceType *faces;


	int filesize;
	int filepos;
	char *theFile;

	string getafloat();
	string getaint();
};