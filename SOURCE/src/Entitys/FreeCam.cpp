#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <SDL.h>

#include <glm.hpp>
#include <ext.hpp>

#include "../Components/Camera.h"
#include "../Components/Transform.h"
#include "FreeCam.h"
#include "../tools.h"
#include "../EventMessages/EventInput.h"
#include "EventHandler.h"
#include "../conf.h"
#include "../Components/TextRenderer.h"


using namespace glm;

void FreeCam::handleEvent(Event* e)
{

	float mousevel = 0.02f;
	float keyvel = 1.0f;

	Transform* transform = this->getComponent<Transform>();

	InputEvent* inputEvent = (InputEvent*)e;

	if(inputEvent->inputtype == keydown)
	{
		if (inputEvent->keyCode == SDLK_UP) 
		{ 

			if ((transform->rotation.x!=90) && (transform->rotation.x!=-90))
			{
				
				float dir = 360;
				float rad=(float) deg2rad(transform->rotation.y+dir);
				transform->position.x-=sin(rad)*keyvel;
				transform->position.z-=cos(rad)*keyvel;

				rad=(float) deg2rad(transform->rotation.y+dir);
				transform->position.y+=sin(rad)*keyvel;
			}
		}
		
		if (inputEvent->keyCode == SDLK_DOWN) 
		{ 
			if ((transform->rotation.x!=90) && (transform->rotation.x!=-90))
			{
				float dir = 180;
				float rad=(float) deg2rad(transform->rotation.y+dir);
				transform->position.x-=sin(rad)*keyvel;
				transform->position.z-=cos(rad)*keyvel;

				rad=(float) deg2rad(transform->rotation.y+dir);
				transform->position.y+=sin(rad)*keyvel;
			}
		}
		if (inputEvent->keyCode == SDLK_LEFT) 
		{
				float dir = 90;

				float rad=(float) deg2rad(transform->rotation.y+dir);
				transform->position.x-=sin(rad)*keyvel;
				transform->position.z-=cos(rad)*keyvel;
		}
		if (inputEvent->keyCode == SDLK_RIGHT) 
		{
				float dir = 270;

				float rad=(float) deg2rad(transform->rotation.y+dir);
				transform->position.x-=sin(rad)*keyvel;
				transform->position.z-=cos(rad)*keyvel;
		}
	}
	
	if(inputEvent->inputtype == mousemotion)
	{
		transform->rotation.y+=mousevel*(screenwidth / 2 - inputEvent->MouseX);
		transform->rotation.x+=mousevel*(screenheight / 2 - inputEvent->MouseY);
	 // transform->rotation.z+=mousevel*(screenwidth / 2 - inputEvent->MouseX);
		
		/*
		if (transform->rotation.x>90) transform->rotation.x=90;
		if (transform->rotation.x<-90) transform->rotation.x=-90;
		if (transform->rotation.y<0) transform->rotation.y+=360;
		if (transform->rotation.y>360) transform->rotation.y-=360;
		*/

	}


	this->getComponent<Camera>()->update();

}
