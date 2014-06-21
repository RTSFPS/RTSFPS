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
#include "Camera.h"

using namespace std;



SkyBoxRenderer::SkyBoxRenderer(Component* renderManager)
{

	RenderManager* renderM = (RenderManager*) renderManager;

	renderM->registerSkyBoxRenderer(this);


	float points[] = {
					  -10.0f,  10.0f, -10.0f,
					  -10.0f, -10.0f, -10.0f,
					   10.0f, -10.0f, -10.0f,
					   10.0f, -10.0f, -10.0f,
					   10.0f,  10.0f, -10.0f,
					  -10.0f,  10.0f, -10.0f,
  
					  -10.0f, -10.0f,  10.0f,
					  -10.0f, -10.0f, -10.0f,
					  -10.0f,  10.0f, -10.0f,
					  -10.0f,  10.0f, -10.0f,
					  -10.0f,  10.0f,  10.0f,
					  -10.0f, -10.0f,  10.0f,
  
					   10.0f, -10.0f, -10.0f,
					   10.0f, -10.0f,  10.0f,
					   10.0f,  10.0f,  10.0f,
					   10.0f,  10.0f,  10.0f,
					   10.0f,  10.0f, -10.0f,
					   10.0f, -10.0f, -10.0f,
   
					  -10.0f, -10.0f,  10.0f,
					  -10.0f,  10.0f,  10.0f,
					   10.0f,  10.0f,  10.0f,
					   10.0f,  10.0f,  10.0f,
					   10.0f, -10.0f,  10.0f,
					  -10.0f, -10.0f,  10.0f,
  
					  -10.0f,  10.0f, -10.0f,
					   10.0f,  10.0f, -10.0f,
					   10.0f,  10.0f,  10.0f,
					   10.0f,  10.0f,  10.0f,
					  -10.0f,  10.0f,  10.0f,
					  -10.0f,  10.0f, -10.0f,
  
					  -10.0f, -10.0f, -10.0f,
					  -10.0f, -10.0f,  10.0f,
					   10.0f, -10.0f, -10.0f,
					   10.0f, -10.0f, -10.0f,
					  -10.0f, -10.0f,  10.0f,
					   10.0f, -10.0f,  10.0f
					};


	glGenBuffers (1, &positionVBO);
	glBindBuffer (GL_ARRAY_BUFFER, positionVBO);
	glBufferData (GL_ARRAY_BUFFER, 3 * 36 * sizeof (float), &points, GL_STATIC_DRAW);

	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, positionVBO);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	numVertex = 0;
	numPositions = 0;
	numUV = 0;
	numIndices = 0;

}





SkyBoxRenderer::~SkyBoxRenderer()
{
	glDeleteBuffers(1,&positionVBO);
    glDeleteVertexArrays(1,&vao);
}



void SkyBoxRenderer::draw(mat4 matrix)
{

		Material* material = this->parent->getComponent<Material>();

		unsigned int shaderID = material->shaderID;
		unsigned int textureID = material->textureID;

	
		mat4 finalMatrix = matrix;
		/*
		vec3 scl = this->parent->getComponent<Transform>()->scale;
		finalMatrix = scale(finalMatrix,scl);
		
		vec3 rot = this->parent->getComponent<Transform>()->rotation;
		finalMatrix=rotate(finalMatrix,rot.x,vec3(1.0f,0.0f,0.0f));
		finalMatrix=rotate(finalMatrix,rot.y,vec3(0.0f,1.0f,0.0f));
		finalMatrix=rotate(finalMatrix,rot.z,vec3(0.0f,0.0f,1.0f));

		vec3 pos = this->parent->getComponent<Transform>()->position;
		finalMatrix = translate (finalMatrix,pos);
		*/

		glDepthMask (GL_FALSE);

		glUseProgram(shaderID);
		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glActiveTexture (GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,textureID);

		uint matrix_location = glGetUniformLocation (shaderID, "matrix");
		glUniformMatrix4fv (matrix_location, 1, GL_FALSE, value_ptr(finalMatrix));


		glBindVertexArray(vao);

		glDrawArrays (GL_TRIANGLES, 0, 36);
	
		glDepthMask (GL_TRUE);
}