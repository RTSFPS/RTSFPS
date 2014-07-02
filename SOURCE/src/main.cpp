#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include "conf.h"

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


#include "main.h"

#include "tools.h"
#include "GraphicTools/shader.h"
#include "GraphicTools/GLstuff.h"
#include "GraphicTools/SDLgraph.h"
#include "EventSystem/EventSystem.h"
#include "EventMessages/EventInput.h"
#include "EventMessages/EventSystemMessages.h"
#include "Factories/EntityFactory.h"
#include "Components/RenderManager.h"
#include "EntitySystem/Entity.h"
#include "Components/FramesPerSecond.h"
#include "Entitys/Player.h"
#include "Common/ContentLoader.h"
#include "Components/Material.h"
#include "Components/Transform.h"
#include "Entitys/InputHandler.h"
#include "Components/SkyBoxRenderer.h"
#include "Components/Camera.h"
#include "SystemTools/ObjectCreator.h"
#include "Managers/PhysicsManager.h"
#include "Components/RigidBody.h"
#include "Components/CharacterController.h"

using namespace std;
using namespace glm;

bool showMouse = true;
int MouseX=0;
int MouseY=0;


unsigned int curTimeStamp=0;


string absoluteExecutablePath="";


#ifdef OS_WIN
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
#endif
#ifdef OS_OSX
int main(int argc, char** argv)
#endif
#ifdef OS_LIN
int main(int argc, char** argv)
#endif
{

#ifdef OS_WIN
	absoluteExecutablePath = "";
#else
	absoluteExecutablePath = getPathFromFullFileName(pcharstring(argv[0]))+"/";
#endif
    
    CreateLogFile();

	GetEngineStartupConfig();
    
      DATAfolder=absoluteExecutablePath+DATAfolder;
	
	srand((unsigned int) time(NULL));
	

	
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) error("Unable to initialize SDL2: " + (string) SDL_GetError());
	
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	
	

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	
	SDL_Window *SDLwindow = NULL;
	unsigned int WindowFlags;

	if (screenFullScreen) WindowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN; else WindowFlags = SDL_WINDOW_OPENGL;

	SDLwindow = SDL_CreateWindow("RTSFPS ver.2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenwidth,screenheight, WindowFlags);
	if (!SDLwindow) error("SDL_CreateWindow: "+ (string) SDL_GetError());

	
    SDL_GLContext SDLopenGLcontext = SDL_GL_CreateContext(SDLwindow);
	
  
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if( glewError != GLEW_OK ) error("Unable to init GLew: "+constpcharstr(glewGetErrorString(glewError)));


	glGetError();
 
	const GLubyte* glRenderer = glGetString (GL_RENDERER); 
	const GLubyte *glVersion= glGetString(GL_VERSION);
	log("OpenGL renderer "+pcharstr((unsigned char*)glRenderer));
	log("OpenGL version "+pcharstr((unsigned char*)glVersion));


		
	int flags=IMG_INIT_JPG | IMG_INIT_PNG;
	int initted=IMG_Init(flags);
	if((initted & flags) != flags) error("Unable to initialize SDL2_Image: "+ (string) SDL_GetError());



	if (TTF_Init() < 0) error("TTF_Init fails: " + (string) SDL_GetError());  



	
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
		

	

	//////////////////////////////////////////////////////////////////////////////////////
	PhysicsManager* physicsManager = new PhysicsManager();


	EventEngine* eventEngine = new EventEngine();
	EventSender* sender = new EventSender(eventEngine);

	EventBus* eventBus = new EventBus(input, eventEngine);
	InputEvent* inputEvent = new InputEvent();


	EventBus* systemEventBus = new EventBus(systemevent, eventEngine);
	SystemListener* systemListener = new SystemListener(systemEventBus);
	SystemEvent* systemEvent = new SystemEvent();

	Entity* renderManagerContainer = createRenderManagerContainer();
	RenderManager* renderManager = renderManagerContainer->getComponent<RenderManager>();
	Entity* framesPerScondContainer = createFramesPerSecondContainer(renderManager, DATAfolder+"font/arial.ttf", 24, 0xffffffff, vec3(10, 10,0) );
	
	Player* player = new Player();
	player->addComponent<Transform>(new Transform(vec3(300, 100,0)));
	player->addComponent<InputProcessor>(new InputProcessor(eventBus, sender));
//	player->addComponent<RigidBody>(new RigidBody(physicsManager));
//	player->getComponent<RigidBody>()->setSphere(1,1000);
	//player->getComponent<RigidBody>()->setBox(vec3(2,2,2), 10);
//	player->addComponent<CharacterController>();
	player->addComponent<Camera>();
	renderManager->registerCamera(player->getComponent<Camera>());
	

	ContentLoader* contentLoader = ContentLoader::getInstance();
	contentLoader->loadContent("");

	Entity* cubus = new Entity();
	cubus->addComponent<Mesh>(contentLoader->Cubus);
	cubus->addComponent<Material>(contentLoader->checkerMaterial);
	cubus->addComponent<Transform>(new Transform(vec3(5,0,0)));
	cubus->addComponent<MeshRenderer>(new MeshRenderer(renderManager));
	cubus->getComponent<MeshRenderer>()->load();
	cubus->addComponent<RigidBody>(new RigidBody(physicsManager));
	cubus->getComponent<RigidBody>()->setBox(vec3(2,2,2), 1000);




	Entity* sphere = new Entity();
	sphere->addComponent<Mesh>(contentLoader->sphere);
	sphere->addComponent<Material>(contentLoader->greenMaterial);
	sphere->addComponent<Transform>(new Transform(vec3(0,0,0)));
	sphere->addComponent<MeshRenderer>(new MeshRenderer(renderManager));
	sphere->getComponent<MeshRenderer>()->load();
	

	InputHandler* handler = new InputHandler();
	handler->addComponent(new InputProcessor(eventBus, sender));
	handler->sender = sender;

	vector<Entity*> cubusses;

/*
	FreeCam* freecam = new FreeCam();
	freecam->addComponent<Transform>(new Transform(vec3(0,0,10)));
	freecam->addComponent<InputProcessor>(new InputProcessor(eventBus, sender));
	freecam->addComponent<Camera>();
	renderManager->registerCamera(freecam->getComponent<Camera>());
*/
	
	Entity* skybox = new Entity();
	skybox->addComponent<Material>(contentLoader->skyboxMaterial);
	skybox->addComponent<Transform>(new Transform(vec3(0,0,0),vec3(0,0,0),vec3(500,500,500)));
	skybox->addComponent<SkyBoxRenderer>(new SkyBoxRenderer(renderManager));
	
	Entity* plane = new Entity();
	plane->addComponent<Mesh>(contentLoader->plane);
	plane->addComponent<Material>(contentLoader->planeMaterial);
	plane->addComponent<Transform>(new Transform(vec3(0,-100,0)));
	plane->addComponent<MeshRenderer>(new MeshRenderer(renderManager));
	plane->getComponent<MeshRenderer>()->load();
	plane->addComponent<RigidBody>(new RigidBody(physicsManager));
	plane->getComponent<RigidBody>()->setBox(vec3(1000,1,1000), 0);


	//////////////////////////////////////////////////////////////////////////////////////


	SDL_ShowCursor(showMouse);


	unsigned int progEnterTime=0;

	SDL_Event event;
	progEnterTime=SDL_GetTicks();
	while (systemListener->sysEventType != terminateapplication)
	{
		//Event polling
		while (SDL_PollEvent(&event))
		{
			switch(event.type) 
			{
				case SDL_MOUSEBUTTONDOWN:
					{
						inputEvent->buttonCode = event.button.button;
						inputEvent->inputtype = mousebuttondown;
						sender->sendEvent(inputEvent);
					} break;
				case SDL_MOUSEBUTTONUP:
					{
						inputEvent->buttonCode = event.button.button;
						inputEvent->inputtype = mousebuttonup;
						sender->sendEvent(inputEvent);
					} break;
				case SDL_MOUSEMOTION:
					{
						inputEvent->MouseX=event.motion.x;
						inputEvent->MouseY=event.motion.y;
						inputEvent->inputtype = mousemotion;
						sender->sendEvent(inputEvent);
					} break;
				case SDL_QUIT: {systemEvent->systemEventType = terminateapplication; sender->sendEvent(systemEvent); } break;
				case SDL_APP_TERMINATING: { systemEvent->systemEventType = terminateapplication; sender->sendEvent(systemEvent); } break;
				case SDL_WINDOWEVENT_CLOSE: { systemEvent->systemEventType = terminateapplication; sender->sendEvent(systemEvent); } break;
				
				case SDL_KEYDOWN: 
					{
					if(event.key.keysym.sym == SDLK_SPACE)
						{
							for(int i = 0; i < cubusses.size(); i++)
							{
								cubusses[i]->getComponent<CharacterController>()->move(vec3(0,10,0));
							}
						}

					} break;
				case SDL_KEYUP: 
					{

					} break;
			
				default: break;
			}
		}

		if (inputEvent->keyState) sender->sendEvent(inputEvent);


		curTimeStamp=SDL_GetTicks()-progEnterTime;

		// Update
		
		SDL_WarpMouseInWindow(SDLwindow,screenwidth / 2,screenheight / 2);
		physicsManager->DynamicsWorld->stepSimulation(1.0f/60.0f);
		cubus->getComponent<RigidBody>()->update();
		//player->getComponent<RigidBody>()->update();
		// rotate cube
		/*
		static float f=0;
		f++;
		cubus->getComponent<Transform>()->rotation.x = f;
		cubus->getComponent<Transform>()->rotation.y = f;
		cubus->getComponent<Transform>()->rotation.z = f;
		*/

		int e = randomRange(0,10);

		if(e > 5 && cubusses.size() < 250)
		{
		Entity* e = new Entity();
		e->addComponent<Mesh>(contentLoader->sphere);
		e->addComponent<Material>(contentLoader->checkerMaterial);
		e->addComponent<Transform>(new Transform(vec3(randomRange(-500,500),randomRange(0,100),randomRange(-500,500))));
		e->addComponent<MeshRenderer>(new MeshRenderer(renderManager));
		e->getComponent<MeshRenderer>()->load();
		e->addComponent<RigidBody>(new RigidBody(physicsManager));
		e->getComponent<RigidBody>()->setBox(vec3(2,2,2), 1000);
		e->addComponent<CharacterController>();
		cubusses.push_back(e);
		}

		framesPerScondContainer->getComponent<FramesPerSecond>()->calculateFps();

		for(int i = 0; i < cubusses.size(); i++)
		{
			cubusses[i]->getComponent<RigidBody>()->update();
		}

		// Draw
		
		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
			
		renderManager->draw();


		SDL_GL_SwapWindow(SDLwindow);
		  
	}


	//////////////////////////////////////////////////////////////////////////////////////	

	delete eventEngine;
	delete eventBus;
	delete sender;
	delete inputEvent;
	delete systemEventBus;
	delete systemListener;
	delete systemEvent;
	delete renderManagerContainer;
	delete renderManager;
	delete framesPerScondContainer;
	delete physicsManager;

	contentLoader->freeContent();

	//////////////////////////////////////////////////////////////////////////////////////	








	TTF_Quit();
	IMG_Quit();
	SDL_GL_DeleteContext(SDLopenGLcontext);
	SDL_DestroyWindow(SDLwindow);
	SDL_Quit();
	log("normal Exit");
	return 0;
}
