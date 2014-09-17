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

#include "../tools.h"
#include "../GraphicTools/GLstuff.h"
#include "../EntityComponentSystem/Component.h"
#include "../EntityComponentSystem/Entity.h"
#include "../Managers/RenderManager.h"
#include "Transform.h"

#include "MeshRenderer.h"


using namespace std;
using namespace glm;



void MeshRenderer::construct(vector<void*> values)
{
	RenderManager::exemplar()->registerMeshRenderer(this);
}



void MeshRenderer::draw()
{

	glUseProgram(testShaderID);
	glDisable(GL_LIGHTING);
			
	static float r=0;

	r+=1;

		mat4 myProjectionMatrix = glm::perspective(45.0f, (GLfloat) screenwidth / (GLfloat) screenheight, 0.01f, 100.0f);
		mat4 myViewMatrix = glm::lookAt(vec3(0,5,50), glm::vec3(0.0f, 5, 0.0f), vec3(0.0f, 1.0f, 0.0f));
		mat4 myModelMatrix = mat4(1); 

		myModelMatrix =rotate(myModelMatrix,r,vec3(1,1,1));
		mat4 myMatrix = myProjectionMatrix * myViewMatrix * myModelMatrix;

		
		// glUniformMatrix4fv(glGetUniformLocation(testShaderID,"projectionMatrix"), 1, GL_FALSE, glm::value_ptr(myProjectionMatrix));
		// glUniformMatrix4fv(glGetUniformLocation(testShaderID,"viewMatrix"), 1, GL_FALSE, glm::value_ptr(myViewMatrix));
		// glUniformMatrix4fv(glGetUniformLocation(testShaderID,"modelMatrix"), 1, GL_FALSE, glm::value_ptr(myModelMatrix));
		
		glUniformMatrix4fv(glGetUniformLocation(testShaderID,"matrix"), 1, GL_FALSE, glm::value_ptr(myMatrix));


    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,testTextureID);
	Uint32 texture = glGetUniformLocation(testShaderID,"texture0");
	if (!texture) error("Texture Uniform Error");
	glUniform1i(texture,0);


	glBindVertexArray(mesh2draw->vao);
	

	if (!mesh2draw->NumFaces) glDrawArrays (mesh2draw->triangleType, 0, mesh2draw->NumVertices);
	//if (mesh2draw->NumFaces) glDrawElements(GL_TRIANGLES, 24*sizeof(unsigned int), GL_UNSIGNED_INT, 0);

}


