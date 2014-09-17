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

#include "GraphicTools/Shader.h"
#include "GraphicTools/GLstuff.h"
#include "GraphicTools/SDLgraph.h"

#include "SceneManagement\SceneReader.h"

#include "SceneManagement\ClassRegistration.h"
#include "EntityComponentSystem\Component.h"
#include "EntityComponentSystem\Entity.h"
#include "SceneManagement\SceneBuilder.h"
#include "Components\Transform.h"
#include "Managers\RenderManager.h"
#include "Managers\ContentManager.h"
#include "Components\MeshRenderer.h"

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
	
		ContentManager* myContentManagerTest=ContentManager::exemplar();


		string name=DATAfolder+"Scene/cube.obj";

		myContentManagerTest->loadMesh(name);

		MeshRenderer* myMeshRenderer = new MeshRenderer();
		myMeshRenderer->mesh2draw = myContentManagerTest->meshes[name];

		Shader* myShader = new Shader(DATAfolder+"shader/texture");
		
		myMeshRenderer->testShaderID = myShader->prog;


		myMeshRenderer->testTextureID = loadTexture(DATAfolder+"graph/checker.jpg");


		RenderManager::exemplar()->registerMeshRenderer(myMeshRenderer);
	
		
	//////////////////////////////////////////////////////////////////////////////////////


	SDL_ShowCursor(showMouse);


	unsigned int progEnterTime=0;

	SDL_Event event;
	progEnterTime=SDL_GetTicks();
	//Event polling
	bool running = true;

	SceneReader::exemplar()->loadScene("ExampleScene2.scn");


	Registrator::registerClasses();

	SceneBuilder* builder = new SceneBuilder();
	builder->buildScene();


	builder->entitys[2]->addComponent<MeshRenderer>(myMeshRenderer);




	while(running)
	{
		while (SDL_PollEvent(&event))
		{
				switch(event.type)
				{
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						running = false;
						break;
					default:
						break;
					}
					break;
					default: break;
				}
		}


		curTimeStamp=SDL_GetTicks()-progEnterTime;

		// Update
		builder->update();
		// Draw

		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		RenderManager::exemplar()->draw();

		SDL_GL_SwapWindow(SDLwindow);
	}

	TTF_Quit();
	IMG_Quit();
	SDL_GL_DeleteContext(SDLopenGLcontext);
	SDL_DestroyWindow(SDLwindow);
	SDL_Quit();
	log("normal Exit");
	return 0;
}
