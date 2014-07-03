#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0
#include <glew.h>
#include <string>
#include <glm.hpp>
#include <ext.hpp>
#include "../EntitySystem/Entity.h"
#include "../Components/RenderManager.h"
#include "../Components/TextRenderer.h"
#include "../Components/Transform.h"
#include "../Components/FramesPerSecond.h"
#include "../SystemTools/OBJparser.h"
#include "../conf.h"
#include "MeshFactory.h"
#include "../tools.h"
#include "../SystemTools/ObjectCreator.h"

using namespace glm;

Mesh* loadObj(string fileName)
{
	Mesh* tempMesh = new Mesh();

	OBJparser* parser = new OBJparser(DATAfolder+fileName);
	tempMesh->materialName = parser->materialname;


	tempMesh->numVertex=parser->numVertex;
	tempMesh->verticies = new Vertex[tempMesh->numVertex];
	
	for (unsigned int i=0; i<tempMesh->numVertex;i++)
	{
		tempMesh->verticies[i].position = vec3(parser->Vertices[i].x,parser->Vertices[i].y,parser->Vertices[i].z);
		tempMesh->verticies[i].normal = vec3(parser->Vertices[i].nx,parser->Vertices[i].ny,parser->Vertices[i].nz);
		tempMesh->verticies[i].textcoord = vec2(parser->Vertices[i].u,parser->Vertices[i].v);
	}
	
	tempMesh->triangleType = GL_TRIANGLES;	

	return tempMesh;
}



Mesh* createMesh(filetype type, string fileName)
{
	if(type == obj)
	{
		return loadObj(fileName);
	}
	return NULL;
}


Mesh* createPrimitive(primitivetype type)
{
	Mesh* tempMesh = new Mesh();


	if (type==plane)
	{
		ObjectCreator* objCreator = new ObjectCreator();
		objCreator->createPlane(1000);


		tempMesh->numVertex=objCreator->numVertex;
		tempMesh->verticies = new Vertex[tempMesh->numVertex];
	
		for (unsigned int i=0; i<tempMesh->numVertex;i++)
		{
			tempMesh->verticies[i].position = vec3(objCreator->Vertices[i].x,objCreator->Vertices[i].y,objCreator->Vertices[i].z);
			tempMesh->verticies[i].normal = vec3(objCreator->Vertices[i].nx,objCreator->Vertices[i].ny,objCreator->Vertices[i].nz);
			tempMesh->verticies[i].textcoord = vec2(objCreator->Vertices[i].u,objCreator->Vertices[i].v);
		}
	
		tempMesh->triangleType = objCreator->DrawMode;	
	}


	return tempMesh;
}
