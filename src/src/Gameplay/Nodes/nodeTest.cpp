#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include "../../conf.h"

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

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>



#include "../../Engine/shader.h"
#include "../../Engine/GLstuff.h"
#include "../../Engine/SDLgraph.h"
#include "../../Engine/OBJparser.h"
#include "../../Engine/skybox.h"
#include "../../Engine/freecam.h"
#include "../../Engine/renderer.h"
#include "../../Engine/ObjectCreator.h"
#include "../../Engine/keys.h"
#include "../../Engine/physics.h"
#include "../../Engine/SceneGraph.h"
#include "../../tools.h"
#include "nodeTest.h"



using namespace std;
using namespace glm;

nodeTest::nodeTest()
{
	

	textureID = loadTexture(DATAfolder+"graph/checker.jpg");

	myFreecam = new freecam();

	mySkybox = new skybox(10);

	myPhysic = new physics();






	// Sphere

		mySphereShader = new shader(DATAfolder+"shader/texture");
		mySphere = new ObjectCreator();
		mySphere->createSphere(30,30,1);
		mySphereRenderer = new renderer(GL_STATIC_DRAW, GL_TRIANGLES, mySphereShader->prog);
		
		mySphereRenderer->setNumVertex(mySphere->numVertex);
		mySphereRenderer->LoadPoints(mySphere->Points,mySphere->numPoints);
		mySphereRenderer->LoadTextCoords(mySphere->UVs,mySphere->numUVs);
		mySphere->FreeMemory();


	// Box
		myBoxShader = new shader(DATAfolder+"shader/flat");
		myBox = new ObjectCreator();
		myBox->createBox(1,1,1);
		myBoxRenderer = new renderer(GL_STATIC_DRAW, GL_TRIANGLES, myBoxShader->prog);
		
		myBoxRenderer->setNumVertex(myBox->numVertex);
		myBoxRenderer->LoadPoints(myBox->Points,myBox->numPoints);
		myBoxRenderer->LoadColors(myBox->Colors,myBox->numColors);
		//myBoxRenderer->LoadTextCoords(myBox->UVs,myBox->numUVs);
		myBox->FreeMemory();


	// BULLET

	
		myPhysic->addSphere(vec3(0,20,0),1,1);
		myPhysic->addBox(vec3(0,100,0),vec3(1,1,1),1);
		myPhysic->addPlain(vec3(0,0,0),vec3(0,1,0),0);


}


nodeTest::~nodeTest()
{

	
	delete myFreecam;
	delete mySkybox;
	delete myPhysic;

//	delete myObj;

	glDeleteTextures( 1, &textureID );

}


void nodeTest::update(void* data)
{



}


void nodeTest::render()
{

	myPhysic->DynamicsWorld->stepSimulation(1/60.0f);



	if (keys::SPACEpressed)
	{
			btRigidBody* sphere=myPhysic->addSphere(vec3(myFreecam->getCamPos().x,myFreecam->getCamPos().y,myFreecam->getCamPos().z),1,1);
			vec3 look=myFreecam->getCameraDirection();
			look *= 200;
			sphere->setLinearVelocity(btVector3(look.x,look.y,look.z));
	}






		mat4 ProjMatrix = mat4(1);
		ProjMatrix = perspective(45.0f, (float) screenwidth / screenheight, 0.01f, 10000.0f);

	



		myFreecam->cameraMatrix = mat4(1);
		myFreecam->CameraControl();

		 mySkybox->renderSkyBox(ProjMatrix*myFreecam->cameraMatrix);
		
		myFreecam->CameraTranslate();

	
					

		for(unsigned int i=0;i<myPhysic->RigitBodies.size();i++)
		{
			btTransform t;
			t.setIdentity();
			btRigidBody* body;
			body = myPhysic->RigitBodies[i];
			if (body->getCollisionShape()->getShapeType()==SPHERE_SHAPE_PROXYTYPE)
			{
				body->getMotionState()->getWorldTransform(t);
				mat4x4 matSphere;
				t.getOpenGLMatrix(value_ptr(matSphere));

				mat4x4 matrix = ProjMatrix*myFreecam->cameraMatrix*matSphere;

				
				glUseProgram(mySphereShader->prog);
				glDisable(GL_LIGHTING);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,textureID);
		
				uint matrix_location = glGetUniformLocation (mySphereShader->prog, "matrix");
				glUniformMatrix4fv (matrix_location, 1, GL_FALSE, value_ptr(matrix));

				mySphereRenderer->Render();
			}
			else if (body->getCollisionShape()->getShapeType()==BOX_SHAPE_PROXYTYPE)
			{
				btVector3 extent=((btBoxShape*)body->getCollisionShape())->getHalfExtentsWithoutMargin();

				body->getMotionState()->getWorldTransform(t);
				mat4x4 matSphere;
				t.getOpenGLMatrix(value_ptr(matSphere));

				
				glUseProgram(myBoxShader->prog);
				glDisable(GL_LIGHTING);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,textureID);
				mat4x4 matrix = ProjMatrix*myFreecam->cameraMatrix*matSphere;
		
				uint matrix_location = glGetUniformLocation (myBoxShader->prog, "matrix");
				glUniformMatrix4fv (matrix_location, 1, GL_FALSE, value_ptr(matrix));

				myBoxRenderer->Render();
			}
			else if (body->getCollisionShape()->getShapeType()== STATIC_PLANE_PROXYTYPE)
			{
				
						glUseProgram(0);

						glMatrixMode(GL_PROJECTION);
						glLoadIdentity();
						gluPerspective(45,screenwidth/screenheight,0.01,10000);

						glMatrixMode(GL_MODELVIEW);
						//glLoadIdentity();

						t.setIdentity();
						body->getMotionState()->getWorldTransform(t);
						mat4x4 matPlain;
						t.getOpenGLMatrix(value_ptr(matPlain));


						glLoadMatrixf(value_ptr(matPlain*myFreecam->cameraMatrix));

						glBegin(GL_QUADS);
		
						glColor3f(0,0,1);

							glVertex3f(-1000,0,1000);
							glVertex3f(-1000,0,-1000);
							glVertex3f(1000,0,-1000);
							glVertex3f(1000,0,1000);
						glEnd();
			}

			
		}

		





// PLAIN





		glBindTexture(GL_TEXTURE_2D,0);

}
