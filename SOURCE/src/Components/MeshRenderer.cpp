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
		Material* material = this->parent->getComponent<Material>();

		unsigned int shaderID = material->shaderID;
		unsigned int textureID = material->textureID;
	
		mat4 finalMatrix = matrix;

		Transform* transform = this->parent->getComponent<Transform>();

		
		finalMatrix = translate (finalMatrix,transform->position);

		vec3 rot = transform->rotation;
		finalMatrix=rotate(finalMatrix,rot.x,vec3(1.0f,0.0f,0.0f));
		finalMatrix=rotate(finalMatrix,rot.y,vec3(0.0f,1.0f,0.0f));
		finalMatrix=rotate(finalMatrix,rot.z,vec3(0.0f,0.0f,1.0f));

		finalMatrix = scale(finalMatrix,transform->scale);

		
		glUseProgram(shaderID);
		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,textureID);

		uint matrix_location = glGetUniformLocation (shaderID, "matrix");
		glUniformMatrix4fv (matrix_location, 1, GL_FALSE, value_ptr(finalMatrix));


		glBindVertexArray(vao);


	if (numIndices==0) glDrawArrays (triangleType, 0, numVertex);

	if (numIndices!=0) glDrawElements(GL_QUADS, 24*sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	
}