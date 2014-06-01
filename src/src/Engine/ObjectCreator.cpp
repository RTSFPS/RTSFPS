#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include "../conf.h"
#ifdef OS_WIN
#include <Windows.h>
#endif
#include <glew.h>
#ifdef OS_WIN
#include <gl/GL.h>
#endif
#include <math.h>
#include <string>
#include <vector>
#include "../tools.h"
#include "ObjectCreator.h"

using namespace std;

#define aPI 3.14159265



void ObjectCreator::createSphere(int nRings, int nSegments, float Radius)
{
	float ring;
	float seg;

	unsigned int vertices = 2 * nRings * (nSegments + 1);

	Vertices = new Vertex[vertices];
	numVertex = vertices;

	float DeltaRingAngle = (float)(aPI / nRings);
	float DeltaSegAngle = (float)(2.0f * aPI / nSegments);

	unsigned int curVert = 0;

	for (ring=0; ring < nRings; ring++)
	{
		float r0 = sinf((float)(ring+0) * DeltaRingAngle);
		float r1 = sinf((float)(ring+1) * DeltaRingAngle);
	
		float y0 = cosf((float)(ring+0) * DeltaRingAngle);
		float y1 = cosf((float)(ring+1) * DeltaRingAngle);
	

		for (seg = 0; seg < (nSegments+1); seg++)
		{
			float x0 = r0 * sinf((float)seg * DeltaSegAngle);
			float z0 = r0 * cosf((float)seg * DeltaSegAngle);
			float x1 = r1 * sinf((float)seg * DeltaSegAngle);
			float z1 = r1 * cosf((float)seg * DeltaSegAngle);


			Vertices[curVert].x = x0*Radius;
			Vertices[curVert].y = y0*Radius;
			Vertices[curVert].z = z0*Radius;

			Vertices[curVert].nx = Vertices[curVert].x;
			Vertices[curVert].ny = Vertices[curVert].y;
			Vertices[curVert].nz = Vertices[curVert].z;

			Vertices[curVert].u = - (float)((float) seg) / nSegments;
			Vertices[curVert].v = (float)(ring+0) / float (nRings);

			curVert++;

			Vertices[curVert].x = x1*Radius;
			Vertices[curVert].y = y1*Radius;
			Vertices[curVert].z = z1*Radius;

			Vertices[curVert].nx = Vertices[curVert].x;
			Vertices[curVert].ny = Vertices[curVert].y;
			Vertices[curVert].nz = Vertices[curVert].z;

			Vertices[curVert].u = -(float)((float) seg) / nSegments;
			Vertices[curVert].v = (float)(ring+1) / float (nRings);

			curVert++;

		}

	
	}

	DrawMode = GL_TRIANGLES;

	ObjectName = "sphere";
	matNumber = 0;
	
	VertexPosition = true;
	VertexNormals = true;
	VertexColor = false;
	VertexUV = true;

	

	vector<Vertex> newVertexBuffer;
	Vertex aVertex;
	unsigned int counter = 0 ;


	for (unsigned int v= 0; v < numVertex-2; v++)
    if (v & 1){
		
		aVertex.x = Vertices[v].x;
		aVertex.y = Vertices[v].y;
		aVertex.z = Vertices[v].z;
		aVertex.nx = Vertices[v].nx;
		aVertex.ny = Vertices[v].ny;
		aVertex.nz = Vertices[v].nz;
		aVertex.u = Vertices[v].u;
		aVertex.v = Vertices[v].v;
		newVertexBuffer.push_back(aVertex);
		counter++;
		aVertex.x = Vertices[v+1].x;
		aVertex.y = Vertices[v+1].y;
		aVertex.z = Vertices[v+1].z;
		aVertex.nx = Vertices[v+1].nx;
		aVertex.ny = Vertices[v+1].ny;
		aVertex.nz = Vertices[v+1].nz;
		aVertex.u = Vertices[v+1].u;
		aVertex.v = Vertices[v+1].v;
		newVertexBuffer.push_back(aVertex);
		counter++;
		aVertex.x = Vertices[v+2].x;
		aVertex.y = Vertices[v+2].y;
		aVertex.z = Vertices[v+2].z;
		aVertex.nx = Vertices[v+2].nx;
		aVertex.ny = Vertices[v+2].ny;
		aVertex.nz = Vertices[v+2].nz;
		aVertex.u = Vertices[v+2].u;
		aVertex.v = Vertices[v+2].v;
		newVertexBuffer.push_back(aVertex);
		counter++;
    }
    else{
		aVertex.x = Vertices[v].x;
		aVertex.y = Vertices[v].y;
		aVertex.z = Vertices[v].z;
		aVertex.nx = Vertices[v].nx;
		aVertex.ny = Vertices[v].ny;
		aVertex.nz = Vertices[v].nz;
		aVertex.u = Vertices[v].u;
		aVertex.v = Vertices[v].v;
		newVertexBuffer.push_back(aVertex);
		counter++;
		aVertex.x = Vertices[v+2].x;
		aVertex.y = Vertices[v+2].y;
		aVertex.z = Vertices[v+2].z;
		aVertex.nx = Vertices[v+2].nx;
		aVertex.ny = Vertices[v+2].ny;
		aVertex.nz = Vertices[v+2].nz;
		aVertex.u = Vertices[v+2].u;
		aVertex.v = Vertices[v+2].v;
		newVertexBuffer.push_back(aVertex);
		counter++;
		aVertex.x = Vertices[v+1].x;
		aVertex.y = Vertices[v+1].y;
		aVertex.z = Vertices[v+1].z;
		aVertex.nx = Vertices[v+1].nx;
		aVertex.ny = Vertices[v+1].ny;
		aVertex.nz = Vertices[v+1].nz;
		aVertex.u = Vertices[v+1].u;
		aVertex.v = Vertices[v+1].v;
		newVertexBuffer.push_back(aVertex);
		counter++;
	}

	delete [] Vertices;
	
	numVertex = counter;

	Vertices = new Vertex[numVertex+1];

	for (unsigned int i=0;i<numVertex;i++)
	{
		Vertices [i] = newVertexBuffer.at(i);
	}

	newVertexBuffer.clear();




	Points = new float[numVertex*3];
	numPoints = numVertex * 3;
	for (unsigned int i=0; i<numVertex; i++)
	{
		Points [i * 3 + 0] = Vertices[i].x;
		Points [i * 3 + 1] = Vertices[i].y;
		Points [i * 3 + 2] = Vertices[i].z;
	}

	Normals = new float[numVertex*3];
	numNormals = numVertex * 3;
	for (unsigned int i=0; i<numVertex; i++)
	{
		Normals [i * 3 + 0] = Vertices[i].nx;
		Normals [i * 3 + 1] = Vertices[i].ny;
		Normals [i * 3 + 2] = Vertices[i].nz;
	}

	counter = 0;
	UVs = new float[numVertex*2];
	numUVs = numVertex * 2;
	for (unsigned int i=0; i<numVertex; i++)
	{
		UVs [counter++] = Vertices[i].u;
		UVs [counter++] = Vertices[i].v;
	}


}



void ObjectCreator::FreeMemory()
{
	delete [] Vertices;

	delete [] Points;
	delete [] Normals;
	delete [] UVs;
}


void ObjectCreator::createTriangle()
{

	unsigned int vertices = 3;

	Vertices = new Vertex[vertices];
	numVertex = vertices;

	
			Vertices[0].x = 0.0f;
			Vertices[0].y = 0.5f;
			Vertices[0].z = 0.0f;
			Vertices[0].nx = 0.0f;
			Vertices[0].ny = 0.5f;
			Vertices[0].nz = 0.0f;
			Vertices[0].r = 1.0f;
			Vertices[0].g = 0.0f;
			Vertices[0].b = 0.0f;
			Vertices[0].u = 0.0f;
			Vertices[0].v = 0.0f;


			Vertices[1].x = 0.5f;
			Vertices[1].y =-0.5f;
			Vertices[1].z =-0.5f;
			Vertices[1].nx = 0.5f;
			Vertices[1].ny =-0.5f;
			Vertices[1].nz =-0.5f;
			Vertices[1].r = 0.0f;
			Vertices[1].g = 1.0f;
			Vertices[1].b = 0.0f;
			Vertices[1].u = 0.0f;
			Vertices[1].v = 1.0f;


			Vertices[2].x = 0.0f;
			Vertices[2].y = 0.0f;
			Vertices[2].z = 0.0f;
			Vertices[2].nx = 0.0f;
			Vertices[2].ny = 1.0f;
			Vertices[2].nz = 0.0f;
			Vertices[2].r = 0.0f;
			Vertices[2].g = 0.0f;
			Vertices[2].b = 1.0f;
			Vertices[2].u = 1.0f;
			Vertices[2].v = 1.0f;

	DrawMode = GL_TRIANGLES;

	ObjectName = "triangle";
	matNumber = 0;

	VertexPosition = true;
	VertexNormals = true;
	VertexColor = true;
	VertexUV = true;



	
	Points = new float[numVertex*3];
	numPoints = numVertex * 3;
	for (unsigned int i=0; i<numVertex; i++)
	{
		Points [i * 3 + 0] = Vertices[i].x;
		Points [i * 3 + 1] = Vertices[i].y;
		Points [i * 3 + 2] = Vertices[i].z;
	}

	Normals = new float[numVertex*3];
	numNormals = numVertex * 3;
	for (unsigned int i=0; i<numVertex; i++)
	{
		Normals [i * 3 + 0] = Vertices[i].nx;
		Normals [i * 3 + 1] = Vertices[i].ny;
		Normals [i * 3 + 2] = Vertices[i].nz;
	}

	unsigned int counter = 0;
	UVs = new float[numVertex*2];
	numUVs = numVertex * 2;
	for (unsigned int i=0; i<numVertex; i++)
	{
		UVs [counter++] = Vertices[i].u;
		UVs [counter++] = Vertices[i].v;
	}

}




void ObjectCreator::createScreenSpaceQuad()
{
	// x,y vertex positions
	float ss_quad_pos[] = {
	  -1.0, -1.0,
	   1.0, -1.0,
	   1.0,  1.0,
	   1.0,  1.0,
	  -1.0,  1.0,
	  -1.0, -1.0
	};
	// per-vertex texture coordinates
	float ss_quad_st[] = {
	  0.0, 0.0,
	  1.0, 0.0,
	  1.0, 1.0,
	  1.0, 1.0,
	  0.0, 1.0,
	  0.0, 0.0
	};

	unsigned int vertices = 6;

	Vertices = new Vertex[vertices];
	numVertex = vertices;

	DrawMode = GL_TRIANGLES;

	ObjectName = "screenquad";
	matNumber = 0;

	VertexPosition = true;
	VertexNormals = true;
	VertexColor = false;
	VertexUV = true;

	Vertices[0].x = ss_quad_pos[0];
	Vertices[0].y = ss_quad_pos[1];
	Vertices[0].z = 0;
	Vertices[0].nx = 0;
	Vertices[0].ny = 0;
	Vertices[0].nz = 1;
	Vertices[0].u = ss_quad_st[0];
	Vertices[0].v = ss_quad_st[1];

	Vertices[1].x = ss_quad_pos[2];
	Vertices[1].y = ss_quad_pos[3];
	Vertices[1].z = 0;
	Vertices[1].nx = 0;
	Vertices[1].ny = 0;
	Vertices[1].nz = 1;
	Vertices[1].u = ss_quad_st[2];
	Vertices[1].v = ss_quad_st[3];


	Vertices[2].x = ss_quad_pos[4];
	Vertices[2].y = ss_quad_pos[5];
	Vertices[2].z = 0;
	Vertices[2].nx = 0;
	Vertices[2].ny = 0;
	Vertices[2].nz = 1;
	Vertices[2].u = ss_quad_st[4];
	Vertices[2].v = ss_quad_st[5];

	Vertices[3].x = ss_quad_pos[6];
	Vertices[3].y = ss_quad_pos[7];
	Vertices[3].z = 0;
	Vertices[3].nx = 0;
	Vertices[3].ny = 0;
	Vertices[3].nz = 1;
	Vertices[3].u = ss_quad_st[6];
	Vertices[3].v = ss_quad_st[7];

	Vertices[4].x = ss_quad_pos[8];
	Vertices[4].y = ss_quad_pos[9];
	Vertices[4].z = 0;
	Vertices[4].nx = 0;
	Vertices[4].ny = 0;
	Vertices[4].nz = 1;
	Vertices[4].u = ss_quad_st[8];
	Vertices[4].v = ss_quad_st[9];

	Vertices[5].x = ss_quad_pos[10];
	Vertices[5].y = ss_quad_pos[11];
	Vertices[5].z = 0;
	Vertices[5].nx = 0;
	Vertices[5].ny = 0;
	Vertices[5].nz = 1;
	Vertices[5].u = ss_quad_st[10];
	Vertices[5].v = ss_quad_st[11];


	
	Points = new float[numVertex*3];
	numPoints = numVertex * 3;
	for (unsigned int i=0; i<numVertex; i++)
	{
		Points [i * 3 + 0] = Vertices[i].x;
		Points [i * 3 + 1] = Vertices[i].y;
		Points [i * 3 + 2] = Vertices[i].z;
	}

	Normals = new float[numVertex*3];
	numNormals = numVertex * 3;
	for (unsigned int i=0; i<numVertex; i++)
	{
		Normals [i * 3 + 0] = Vertices[i].nx;
		Normals [i * 3 + 1] = Vertices[i].ny;
		Normals [i * 3 + 2] = Vertices[i].nz;
	}

	unsigned int counter = 0;
	UVs = new float[numVertex*2];
	numUVs = numVertex * 2;
	for (unsigned int i=0; i<numVertex; i++)
	{
		UVs [counter++] = Vertices[i].u;
		UVs [counter++] = Vertices[i].v;
	}


}




void ObjectCreator::createBox(float x, float y, float z)
{
	static const float vertexbufferdata[] = {
    -x, -y, -z, 
    -x, -y,  z,
    -x,  y,  z, 
     x,  y, -z, 
    -x, -y, -z,
    -x,  y, -z, 
     x, -y,  z,
    -x, -y, -z,
     x, -y, -z,
     x,  y, -z,
     x, -y, -z,
    -x, -y, -z,
    -x, -y, -z,
    -x,  y,  z,
    -x,  y, -z,
     x, -y,  z,
    -x, -y,  z,
    -x, -y, -z,
    -x,  y,  z,
    -x, -y,  z,
     x, -y,  z,
     x,  y,  z,
     x, -y, -z,
     x,  y, -z,
     x, -y, -z,
     x,  y,  z,
     x, -y,  z,
     x,  y,  z,
     x,  y, -z,
    -x,  y, -z,
     x,  y,  z,
    -x,  y, -z,
    -x,  y,  z,
     x,  y,  z,
    -x,  y,  z,
     x, -y,  z };

	float r,g,b;
	r=0;
	g=1;
	b=0;


	unsigned int vertices = 36;

	Vertices = new Vertex[vertices];
	numVertex = vertices;

	DrawMode = GL_TRIANGLES;

	ObjectName = "cube";
	matNumber = 0;

	VertexPosition = true;
	VertexNormals = false;
	VertexColor = true;
	VertexUV = false;

	for (unsigned int i=0; i<numVertex; i++)
	{
		Vertices[i].x = vertexbufferdata[i * 3 + 0];
		Vertices[i].y = vertexbufferdata[i * 3 + 1];
		Vertices[i].z = vertexbufferdata[i * 3 + 2];
		Vertices[i].r = r;
		Vertices[i].g = g;
		Vertices[i].b = b;
	}

	Points = new float[numVertex*3];
	numPoints = numVertex * 3;
	for (unsigned int i=0; i<numVertex; i++)
	{
		Points [i * 3 + 0] = Vertices[i].x;
		Points [i * 3 + 1] = Vertices[i].y;
		Points [i * 3 + 2] = Vertices[i].z;
	}

	Colors = new float[numVertex*3];
	numColors = numVertex * 3;
	for (unsigned int i=0; i<numVertex; i++)
	{
		Colors [i * 3 + 0] = Vertices[i].r;
		Colors [i * 3 + 1] = Vertices[i].g;
		Colors [i * 3 + 2] = Vertices[i].b;
	}
}