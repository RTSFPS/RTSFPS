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
#include "../tools.h"
#include "test.h"




using namespace std;


Test::Test()
{
	
	myFreecam = new freecam();



	mySkybox = new skybox();
	mySkybox->initSkyBox(1000);



   // OBJ 

		myObj = new OBJparser(DATAfolder+"scene/cube.obj");
		textureID = loadTexture(DATAfolder+"graph/checker.jpg");



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







	glColor4f(1.0,1.0,1.0,1.0);

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);


	

	glBindTexture(GL_TEXTURE_2D,textureID);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glGenerateMipmap(GL_TEXTURE_2D);
    
    
    
    
    

	glBegin(GL_TRIANGLES);


		for (unsigned int i=0;i<myObj->numVertex;i+=3)
		{

			glTexCoord2f(myObj->Vertices[i+0].u, myObj->Vertices[i+0].v);
			glNormal3f(myObj->Vertices[i+0].nx, myObj->Vertices[i+0].ny,myObj->Vertices[i+0].nz);
			glVertex3f(myObj->Vertices[i+0].x, myObj->Vertices[i+0].y,myObj->Vertices[i+0].z);
		
			glTexCoord2f(myObj->Vertices[i+1].u, myObj->Vertices[i+1].v);
			glNormal3f(myObj->Vertices[i+1].nx, myObj->Vertices[i+1].ny,myObj->Vertices[i+1].nz);
			glVertex3f(myObj->Vertices[i+1].x, myObj->Vertices[i+1].y,myObj->Vertices[i+1].z);
			
			glTexCoord2f(myObj->Vertices[i+2].u, myObj->Vertices[i+2].v);
			glNormal3f(myObj->Vertices[i+2].nx, myObj->Vertices[i+2].ny,myObj->Vertices[i+2].nz);
			glVertex3f(myObj->Vertices[i+2].x, myObj->Vertices[i+2].y,myObj->Vertices[i+2].z);
			
			
		}



	glEnd();

		glBindTexture(GL_TEXTURE_2D,0);

 }
