#define NO_SDL_GLEXT

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
#include "Engine/drawfont.h"
#include "Engine/shader.h"
#include "Engine/GLstuff.h"
#include "Engine/SDLgraph.h"
#include "Engine/keys.h"
#include "Gameplay/test.h"


using namespace std;
using namespace glm;

bool showMouse = true;
int MouseX=0;
int MouseY=0;

drawfont* exStandartFont;

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

	SDLwindow = SDL_CreateWindow("RTSFPS ver.1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenwidth,screenheight, WindowFlags);
	if (!SDLwindow) error("SDL_CreateWindow: "+ (string) SDL_GetError());

	
    SDL_GLContext SDLopenGLcontext = SDL_GL_CreateContext(SDLwindow);
	
  
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
        log("ok");
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


	exStandartFont = new drawfont(DATAfolder+"font/arial.ttf",24);
	
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
		

	mat4 ProjMatrix = perspective(45.0f, (float) screenwidth / screenheight, 0.01f, 10000.0f);


	//////////////////////////////////////////////////////////////////////////////////////

		Test* myTest = new Test();

	//////////////////////////////////////////////////////////////////////////////////////


	SDL_ShowCursor(showMouse);

	unsigned int dwFrames = 0;
	unsigned int dwCurrentTime = 0;
	unsigned int dwLastUpdateTime = 0;
	unsigned int dwElapsedTime = 0;
	string theFPS="";
	unsigned int progEnterTime=0;

	bool quit=false;
	SDL_Event event;
	progEnterTime=SDL_GetTicks();
	while (!quit)
	{

		//Event polling
		while (SDL_PollEvent(&event))
		{
			switch(event.type) 
			{
				case SDL_MOUSEMOTION:
				{
					MouseX=event.motion.x;
					MouseY=event.motion.y;
				} break;
				case SDL_QUIT: { quit = true; } break;
				case SDL_APP_TERMINATING: { quit = true; } break;
				case SDL_WINDOWEVENT_CLOSE: { quit=true; } break;
				case SDL_KEYDOWN: 
					{
						switch (event.key.keysym.sym)
						{
							case SDLK_ESCAPE: {quit = true;} break;
							case SDLK_RIGHT: { keys::RIGHTpressed = true;} break;
							case SDLK_LEFT: { keys::LEFTpressed = true; } break;	
							case SDLK_UP: { keys::UPpressed = true; } break;	
							case SDLK_DOWN: { keys::DOWNpressed = true; } break;	
							case SDLK_SPACE: { keys::SPACEpressed = true; } break;	
							default: break;
						}
					} break;
				case SDL_KEYUP: 
					{
						switch (event.key.keysym.sym)
						{
							case SDLK_RIGHT: { keys::RIGHTpressed = false;} break;
							case SDLK_LEFT: { keys::LEFTpressed = false; } break;	
							case SDLK_UP: { keys::UPpressed = false; } break;	
							case SDLK_DOWN: { keys::DOWNpressed = false; } break;	
							case SDLK_SPACE: { keys::SPACEpressed = false; } break;	
							default: break;
						}
					} break;
				default: break;
			}
		}
		
		curTimeStamp=SDL_GetTicks()-progEnterTime;

		// Update





		// Draw
		
		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		
	//////////////////////////////////////////////////////////////////////////////////////		
	
	SDL_WarpMouseInWindow(SDLwindow,screenwidth / 2,screenheight / 2);
		myTest->Draw();



	//////////////////////////////////////////////////////////////////////////////////////		

		dwFrames++;
		dwCurrentTime = SDL_GetTicks();
		dwElapsedTime = dwCurrentTime - dwLastUpdateTime;
		
		if(dwElapsedTime >= 1000)
		{
			string fps = "fps";
			if (how2showFPS==0 || how2showFPS==1) theFPS = floatstr((float) dwFrames * 1000.0f / dwElapsedTime).append(fps);
			dwFrames = 0;
			dwLastUpdateTime = dwCurrentTime;
		}
		

		

		if ((how2showFPS==0)&&(theFPS!="")) exStandartFont->glTextOut(10, 10 , theFPS, 0xffffffff);
		if (how2showFPS==1) SDL_SetWindowTitle(SDLwindow,theFPS.c_str());


		SDL_GL_SwapWindow(SDLwindow);
		  
	}


	//////////////////////////////////////////////////////////////////////////////////////	

		myTest->~Test();
		

	//////////////////////////////////////////////////////////////////////////////////////	








	TTF_Quit();
	IMG_Quit();
	SDL_GL_DeleteContext(SDLopenGLcontext);
	SDL_DestroyWindow(SDLwindow);
	SDL_Quit();
	log("normal Exit");
	return 0;
}
