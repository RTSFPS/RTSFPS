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

#include "../GraphicTools/GLstuff.h"
#include "../tools.h"
#include "../EntitySystem/Component.h"
#include "../EntitySystem/Entity.h"
#include "RenderManager.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Transform.h"
#include "SkyBox.h"
#include "Renderer.h"

using namespace std;
using namespace glm;



MeshRenderer::MeshRenderer(Component* renderManager)
{

	RenderManager* renderM = (RenderManager*) renderManager;

	renderM->registerMeshRenderer(this);

	numVertex = 0;
	numPositions = 0;
	numUV = 0;
	numIndices = 0;
}



void MeshRenderer::load()
{

	Mesh* mesh = this->parent->getComponent<Mesh>();

	this->numVertex = mesh->numVertex;
	this->triangleType = mesh->triangleType;

	 glGenVertexArrays(1, &vao);

	loadPositionsFromVertexBuffer(mesh->verticies,mesh->numVertex);
	loadTextCoordsFromVertexBuffer(mesh->verticies,mesh->numVertex);
	
}



MeshRenderer::~MeshRenderer()
{
	glDeleteBuffers(1,&positionVBO);
	if (uvVBO)	glDeleteBuffers(1,&uvVBO);
    glDeleteVertexArrays(1,&vao);
}





void MeshRenderer::draw(mat4 matrix)
{


	if (numIndices==0)
	{

		static float f=0;

	
		Material* material = this->parent->getComponent<Material>();

		unsigned int shaderID = material->shaderID;
		unsigned int textureID = material->textureID;

	
		mat4 ProjMatrix = mat4(1);
		ProjMatrix = perspective(45.0f, (float) screenwidth / screenheight, 0.01f, 100.0f);
	
		mat4 ModelViewMatrix= matrix; 


		f++;
		mat4 rotationMatrix = mat4(1.0f);
		rotationMatrix*=rotate(f,vec3(1.0f,1.0f,1.0f));



		vec3 pos = this->parent->getComponent<Transform>()->position;
		mat4 translationMatrix = mat4(1);
		translationMatrix = translate (pos);

		mat4x4 finalmatrix = ProjMatrix * ModelViewMatrix * translationMatrix * rotationMatrix;

				
		glUseProgram(shaderID);
		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,textureID);

		uint matrix_location = glGetUniformLocation (shaderID, "matrix");
		glUniformMatrix4fv (matrix_location, 1, GL_FALSE, value_ptr(finalmatrix));


		glBindVertexArray(vao);
		glDrawArrays (triangleType, 0, numVertex);


	}


	if (numIndices!=0)
	{
		Material* material = this->parent->getComponent<Material>();

		unsigned int shaderID = material->shaderID;
		unsigned int textureID = material->textureID;


		mat4 Projection = perspective(45.0f, (float) screenwidth / screenheight, 0.01f, 100.0f);
		mat4 View       = mat4(1.0f);
		mat4 Model      = scale(glm::mat4(1.0f),glm::vec3(50,50,50));

		mat4x4 matrix = Projection * View * Model;

				
		glUseProgram(shaderID);
		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_CUBE_MAP);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		uint matrix_location = glGetUniformLocation (shaderID, "matrix");
		glUniformMatrix4fv (matrix_location, 1, GL_FALSE, value_ptr(matrix));


		glBindVertexArray(vao);
		glDrawElements(GL_QUADS, 24*sizeof(unsigned int), GL_UNSIGNED_INT, 0);

	}
	
}