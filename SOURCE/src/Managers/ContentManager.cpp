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

#include "../GraphicTools/GLstuff.h"
#include "ContentManager.h"
#include "../SystemTools/OBJparser.h"

using namespace glm;
using namespace std;

ContentManager* ContentManager::instance = 0;


ContentManager* ContentManager::exemplar()
{
	if(instance == 0)
	{
		instance = new ContentManager();
	}
	return instance;
}

void ContentManager::loadTexture(string textureName)
{

}

void ContentManager::loadShader(string ShaderName)
{
}

void ContentManager::loadSkyBoxTexture(string filePath)
{
}

void ContentManager::loadMesh(string filename)
{
	string meshName=filename;   // Extract the Filename from globalfilename without Extention and Path      !!! TO DO !!!

	Mesh* tempMesh = new Mesh();


	string s=getExtentionfromFileName(filename);

	if (s=="obj") 
	{
		OBJparser* parser = new OBJparser(filename);
		// tempMesh->materialName = parser->materialname;


		tempMesh->NumVertices=parser->numVertex;
		tempMesh->Vertices = new vec4[tempMesh->NumVertices];
		tempMesh->Normals = new vec3[tempMesh->NumVertices];
		tempMesh->TexCoords = new vec2[tempMesh->NumVertices];

		for (unsigned int i=0; i<tempMesh->NumVertices;i++)
		{
			tempMesh->Vertices[i] = vec4(parser->Vertices[i].x,parser->Vertices[i].y,parser->Vertices[i].z,1);
			tempMesh->Normals[i] = vec3(parser->Vertices[i].nx,parser->Vertices[i].ny,parser->Vertices[i].nz);
			tempMesh->TexCoords[i] = vec2(parser->Vertices[i].u,parser->Vertices[i].v);
		}

		tempMesh->NumFrames = 0; // Static Mesh
		tempMesh->NumFaces = 0; // Mesh is not Indexed
		tempMesh->triangleType = GL_TRIANGLES;



		glGenBuffers (1, &tempMesh->PointsVBO);
		glBindBuffer (GL_ARRAY_BUFFER, tempMesh->PointsVBO);
		glBufferData (GL_ARRAY_BUFFER,  tempMesh->NumVertices * sizeof (vec4), tempMesh->Vertices, GL_STATIC_DRAW);

		glGenBuffers (1, &tempMesh->NormalsVBO);
		glBindBuffer (GL_ARRAY_BUFFER, tempMesh->NormalsVBO);
		glBufferData (GL_ARRAY_BUFFER,  tempMesh->NumVertices * sizeof (vec3), tempMesh->Normals, GL_STATIC_DRAW);

		glGenBuffers (1, &tempMesh->TexCoordsVBO);
		glBindBuffer (GL_ARRAY_BUFFER, tempMesh->TexCoordsVBO);
		glBufferData (GL_ARRAY_BUFFER,  tempMesh->NumVertices * sizeof (vec2), tempMesh->TexCoords, GL_STATIC_DRAW);


		glGenVertexArrays (1, &tempMesh->vao);
		glBindVertexArray (tempMesh->vao);

		glBindBuffer (GL_ARRAY_BUFFER, tempMesh->PointsVBO);
		glVertexAttribPointer (0, 4, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

		glBindBuffer (GL_ARRAY_BUFFER, tempMesh->NormalsVBO);
		glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

		glBindBuffer (GL_ARRAY_BUFFER, tempMesh->TexCoordsVBO);
		glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

		glEnableVertexAttribArray (0);
		glEnableVertexAttribArray (1);
		glEnableVertexAttribArray (2);

		tempMesh->BoneIndicesVBO = 0;
		tempMesh->BoneWeightsVBO = 0;

		tempMesh->BoneIndices = NULL;
		tempMesh->BoneWeights = NULL;
		tempMesh->Indices = NULL;
		tempMesh->Matrices = NULL;
		tempMesh->Sequenzies = NULL;

		
	}
	



	this->meshes[meshName] = tempMesh;

}




void ContentManager::deleteMesh(string name)
{
	
	
	glDeleteBuffers(1,&meshes[name]->PointsVBO);
	glDeleteBuffers(1,&meshes[name]->NormalsVBO);
	glDeleteBuffers(1,&meshes[name]->TexCoordsVBO);

	if (meshes[name]->BoneWeightsVBO) glDeleteBuffers(1,&meshes[name]->BoneWeightsVBO);
	if (meshes[name]->BoneIndicesVBO) glDeleteBuffers(1,&meshes[name]->BoneIndicesVBO);

	glDeleteVertexArrays(1,&meshes[name]->vao);


	delete [] meshes[name]->Vertices;
	delete [] meshes[name]->Normals;
	delete [] meshes[name]->TexCoords;

	if (meshes[name]->BoneWeights) delete [] meshes[name]->BoneWeights;
	if (meshes[name]->BoneIndices) delete [] meshes[name]->BoneIndices;

	if(meshes[name]->Indices) delete [] meshes[name]->Indices;

	if (meshes[name]->Matrices) delete [] meshes[name]->Matrices; // ?? kann sein dass hier ein Memoryleek is!!!!!

	if (meshes[name]->Sequenzies)
	{
		for (unsigned int i=0;i<meshes[name]->numSequenzies; i++)
		{
			delete[] meshes[name]->Sequenzies[i].Name;
			meshes[name]->Sequenzies[i].Name = NULL;
		}
		delete[] meshes[name]->Sequenzies;
		meshes[name]->Sequenzies = NULL;
		meshes[name]->numSequenzies = 0;		
	}




	meshes.erase(name);
}