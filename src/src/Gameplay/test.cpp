#define NO_SDL_GLEXT

#include "../conf.h"

#ifdef OS_WIN
#include <Windows.h>
#endif
#include <glew.h>
#ifdef OS_WIN
#include <gl/GL.h>
#include <gl/GLU.h>
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


using namespace std;
using namespace glm;

#include "../Engine/shader.h"
#include "../Engine/GLstuff.h"
#include "../Engine/GLgraph.h"
#include "../Engine/SDLgraph.h"
#include "../Engine/OBJparser.h"
#include "../Engine/skybox.h"
#include "../Engine/freecam.h"
#include "../Engine/renderer.h"
#include "../tools.h"
#include "test.h"




using namespace std;


Test::Test()
{
	
	myFreecam = new freecam();



	mySkybox = new skybox();
	mySkybox->initSkyBox(10);



   // OBJ 

		myObj = new OBJparser(DATAfolder+"scene/cube.obj");
		textureID = loadTexture(DATAfolder+"graph/checker.jpg");



   // Setup OpenGL

		myShader = new shader(DATAfolder+"shader/texture.vert", DATAfolder+"shader/texture.frag");

		myRenderer = new renderer(GL_STATIC_DRAW, GL_TRIANGLES, myShader->prog);

		myRenderer->setNumVertex(myObj->numVertex);
		myRenderer->LoadPoints(myObj->PositionBuffer,myObj->numPositions);
		myRenderer->LoadTextCoords(myObj->TextureCoordBuffer,myObj->numTextureCoords);

}


Test::~Test()
{
	delete myFreecam;
	mySkybox->closeSkyBox();
	delete mySkybox;
	delete myObj;
}


void Test::Draw()
{

	
	glUseProgram(0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,screenwidth / screenheight, 0.01, 10000);


		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

	myFreecam->cameraMatrix = mat4(1);
    myFreecam->CameraControl();

		glLoadMatrixf(value_ptr(myFreecam->cameraMatrix));

			 mySkybox->renderSkyBox();

		myFreecam->CameraTranslate();




		
		glLoadMatrixf(value_ptr(myFreecam->cameraMatrix));




		
	glUseProgram(myShader->prog);

	
		mat4 ProjMatrix = mat4(1);
		ProjMatrix = perspective(45.0f, (float) screenwidth / screenheight, 0.01f, 10000.0f);


		mat4 matrix = ProjMatrix*myFreecam->cameraMatrix;
		int matrix_location = glGetUniformLocation (myShader->prog, "matrix");
		glUniformMatrix4fv (matrix_location, 1, GL_FALSE, value_ptr(matrix));


	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);


	

	glBindTexture(GL_TEXTURE_2D,textureID);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glGenerateMipmap(GL_TEXTURE_2D);
    
    
   

	myRenderer->Render();

		glBindTexture(GL_TEXTURE_2D,0);

 }
