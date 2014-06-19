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




Renderer::~Renderer()
{
	
}

void Renderer::draw()
{

}


void Renderer::loadPositionsFromFloatBuffer(void* data, unsigned int numPositions)
{
	this->numPositions = numPositions;
	glBindVertexArray(vao);

	glGenBuffers(1, &positionVBO);
	glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
	glBufferData(GL_ARRAY_BUFFER, numPositions*sizeof(float), data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);	
	
	glEnableVertexAttribArray(0);


}



void Renderer::loadIndicesFromFloatBuffer(void* data, unsigned int numIndices)
{
	this->numIndices = numIndices;
	
	glGenBuffers(1, &indicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices*sizeof(unsigned int), data, GL_STATIC_DRAW);
}



void Renderer::loadPositionsFromVertexBuffer(void* data,unsigned int numPositions)
{

	this->numPositions = numPositions;


	glBindVertexArray(vao);
    
	glGenBuffers (1, &positionVBO);
	glBindBuffer (GL_ARRAY_BUFFER, positionVBO);

	glBufferData (GL_ARRAY_BUFFER,  numPositions * sizeof (Vertex) , data, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex),BUFFER_OFFSET(0));

    glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}


void Renderer::loadTextCoordsFromVertexBuffer(void* data, unsigned int numUVs)
{
	
		this->numUV = numUVs;
    
    
    	glBindVertexArray(vao);
    
    

		glGenBuffers (1, &uvVBO);

		glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
		

		glBufferData (GL_ARRAY_BUFFER,  numUVs * sizeof (Vertex), data, GL_STATIC_DRAW);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(6*4));



        glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		
    
}

