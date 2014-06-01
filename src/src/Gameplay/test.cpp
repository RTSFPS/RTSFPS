#define NO_SDL_GLEXT

#include "../conf.h"

#ifdef OS_WIN
#include <Windows.h>
#endif
#include <glew.h>
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


using namespace std;
using namespace glm;

#include "../Engine/shader.h"
#include "../Engine/GLstuff.h"
#include "../Engine/SDLgraph.h"
#include "../Engine/OBJparser.h"
#include "../Engine/skybox.h"
#include "../Engine/freecam.h"
#include "../Engine/renderer.h"
#include "../Engine/ObjectCreator.h"
#include "../tools.h"
#include "test.h"




using namespace std;


Test::Test()
{
	
	myFreecam = new freecam();

	mySkybox = new skybox(10);



   // OBJ 

		myObj = new OBJparser(DATAfolder+"scene/cube.obj");
		textureID = loadTexture(DATAfolder+"graph/checker.jpg");
		myShader = new shader(DATAfolder+"shader/texture");
		myRenderer = new renderer(GL_STATIC_DRAW, GL_TRIANGLES, myShader->prog);
		myRenderer->setNumVertex(myObj->numVertex);
		myRenderer->LoadPoints(myObj->PositionBuffer,myObj->numPositions);
		myRenderer->LoadTextCoords(myObj->TextureCoordBuffer,myObj->numTextureCoords);


	// Sphere

		mySphere = new ObjectCreator();
		mySphere->createSphere(30,30,1);
		mySphereRenderer = new renderer(GL_STATIC_DRAW, GL_TRIANGLES, myShader->prog);
		
		mySphereRenderer->setNumVertex(mySphere->numVertex);
		mySphereRenderer->LoadPoints(mySphere->Points,mySphere->numPoints);
		mySphereRenderer->LoadTextCoords(mySphere->UVs,mySphere->numUVs);

}


Test::~Test()
{

	mySphere->FreeMemory();

	delete myFreecam;
	delete mySkybox;
	delete myObj;
}


void Test::Draw()
{

		mat4 ProjMatrix = mat4(1);
		ProjMatrix = perspective(45.0f, (float) screenwidth / screenheight, 0.01f, 10000.0f);

	



			myFreecam->cameraMatrix = mat4(1);
			myFreecam->CameraControl();

	//	 mySkybox->renderSkyBox(ProjMatrix*myFreecam->cameraMatrix);
		
		myFreecam->CameraTranslate();









	glUseProgram(myShader->prog);

	
		ProjMatrix = mat4(1);
		ProjMatrix = perspective(45.0f, (float) screenwidth / screenheight, 0.01f, 10000.0f);


		mat4x4 matrix = ProjMatrix*myFreecam->cameraMatrix;
		
		uint		 matrix_location = glGetUniformLocation (myShader->prog, "matrix");
		glUniformMatrix4fv (matrix_location, 1, GL_FALSE, value_ptr(matrix));


	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);


	

	glBindTexture(GL_TEXTURE_2D,textureID);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glGenerateMipmap(GL_TEXTURE_2D);
    
    
   

//	myRenderer->Render();

	mySphereRenderer->Render();

		glBindTexture(GL_TEXTURE_2D,0);

 }
