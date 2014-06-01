#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

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

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>


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
#include "../Engine/keys.h"
#include "../tools.h"
#include "test.h"




using namespace std;


btRigidBody* Test::addSphere(vec3 xyz, float rad)
{
			
		float mass=1;


		btTransform t;
		t.setIdentity();
		t.setIdentity();
		t.setOrigin(btVector3(xyz.x,xyz.y,xyz.z));
		btSphereShape* mySphere = new btSphereShape(1); // radius
		btVector3 inertia(0,0,0);
		mySphere->calculateLocalInertia(mass,inertia); 

		btMotionState* mySphereMotionState = new btDefaultMotionState(t);
		btRigidBody::btRigidBodyConstructionInfo sphereinfo(mass,mySphereMotionState,mySphere);
		btRigidBody* mySphereBody = new btRigidBody(sphereinfo);

		DynamicsWorld->addRigidBody(mySphereBody);

		bodies.push_back(mySphereBody);

		return mySphereBody;


}





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


	// BULLET

		
	CollisionConfiguration = new btDefaultCollisionConfiguration();
	CollisionDispatcher = new btCollisionDispatcher(CollisionConfiguration);
	Broadphase = new btDbvtBroadphase();
	ConstraintSolver = new btSequentialImpulseConstraintSolver();
	DynamicsWorld = new btDiscreteDynamicsWorld(CollisionDispatcher,Broadphase,ConstraintSolver,CollisionConfiguration);
	DynamicsWorld->setGravity(btVector3(0,-10,0));

		


	
		addSphere(vec3(0,20,0),1);


	//plain
		btTransform t;
		t.setIdentity();
		t.setOrigin(btVector3(0.0f, 0.0f, 0.0f));
		btStaticPlaneShape* myPlane = new btStaticPlaneShape(btVector3(0,1,0),0);
		btMotionState* myPlainMotionState = new btDefaultMotionState();
		btRigidBody::btRigidBodyConstructionInfo plaininfo(0,myPlainMotionState,myPlane);
		myPlainBody = new btRigidBody(plaininfo);

		DynamicsWorld->addRigidBody(myPlainBody);

}






Test::~Test()
{

	mySphere->FreeMemory();

	delete myFreecam;
	delete mySkybox;
	delete myObj;


	for(unsigned int i=0;i<bodies.size();i++)
	{
		DynamicsWorld->removeCollisionObject(bodies[i]);
		btMotionState* motionState=bodies[i]->getMotionState();
		btCollisionShape* shape=bodies[i]->getCollisionShape();
		delete bodies[i];
		delete shape;
		delete motionState;
	}

		DynamicsWorld->removeCollisionObject(myPlainBody);
		btMotionState* motionState=myPlainBody->getMotionState();
		btCollisionShape* shape=myPlainBody->getCollisionShape();
		delete myPlainBody;
		delete shape;
		delete motionState;


	delete DynamicsWorld;
	delete ConstraintSolver;
	delete Broadphase;
	delete CollisionDispatcher;
	delete CollisionConfiguration;
}


void Test::Draw()
{
	
	DynamicsWorld->stepSimulation(1/60.0f);



	if (keys::SPACEpressed)
	{
			btRigidBody* sphere=addSphere(vec3(myFreecam->getCamPos().x,myFreecam->getCamPos().y,myFreecam->getCamPos().z),1);
			vec3 look=myFreecam->getCameraDirection();
			look *= 20;
			sphere->setLinearVelocity(btVector3(look.x,look.y,look.z));
	}






		mat4 ProjMatrix = mat4(1);
		ProjMatrix = perspective(45.0f, (float) screenwidth / screenheight, 0.01f, 10000.0f);

	



			myFreecam->cameraMatrix = mat4(1);
			myFreecam->CameraControl();

		 mySkybox->renderSkyBox(ProjMatrix*myFreecam->cameraMatrix);
		
		myFreecam->CameraTranslate();









	glUseProgram(myShader->prog);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,textureID);
	
					btTransform t;
					
		for(unsigned int i=0;i<bodies.size();i++)
		{
	

			t.setIdentity();
			btRigidBody* body;
			body = bodies[i];
			body->getMotionState()->getWorldTransform(t);
			mat4x4 matSphere;
			t.getOpenGLMatrix(value_ptr(matSphere));

			mat4x4 matrix = ProjMatrix*myFreecam->cameraMatrix*matSphere;
		
			uint		 matrix_location = glGetUniformLocation (myShader->prog, "matrix");
			glUniformMatrix4fv (matrix_location, 1, GL_FALSE, value_ptr(matrix));

			mySphereRenderer->Render();
		}

		





// PLAIN


		glUseProgram(0);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45,screenwidth/screenheight,0.01,10000);

		glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();

				t.setIdentity();
		myPlainBody->getMotionState()->getWorldTransform(t);
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


		glBindTexture(GL_TEXTURE_2D,0);

 }
