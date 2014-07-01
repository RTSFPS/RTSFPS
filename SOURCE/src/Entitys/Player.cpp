#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <SDL.h>
#include <glm.hpp>
#include <ext.hpp>

#include "Player.h"
#include "../tools.h"
#include "../EventMessages/EventInput.h"
#include "../Components/TextRenderer.h"
#include "../Components/CharacterController.h"

using namespace glm;


Player::Player()
{
	mouseSpeed = 0.04f;
	keyboardSpeed = 50;
}


void Player::handleEvent(Event* e)
{
	InputEvent* inputEvent = (InputEvent*)e;


		if(inputEvent->keyCode == SDLK_RIGHT && inputEvent->inputtype == keydown) 
		{
			this->getComponent<CharacterController>()->move(vec3(keyboardSpeed,0,0));
		} 
		if(inputEvent->keyCode == SDLK_RIGHT && inputEvent->inputtype == keyup) 
		{
			this->getComponent<CharacterController>()->move(vec3(0,0,0));
		} 


		if(inputEvent->keyCode == SDLK_LEFT && inputEvent->inputtype == keydown) 
		{
			this->getComponent<CharacterController>()->move(vec3(-keyboardSpeed,0,0));
		} 
		if(inputEvent->keyCode == SDLK_LEFT && inputEvent->inputtype == keyup) 
		{
			this->getComponent<CharacterController>()->move(vec3(0,0,0));
		} 


		if(inputEvent->keyCode == SDLK_UP && inputEvent->inputtype == keydown) 
		{
			this->getComponent<CharacterController>()->move(vec3(0,0,-keyboardSpeed));
		} 
		if(inputEvent->keyCode == SDLK_UP && inputEvent->inputtype == keyup) 
		{
			this->getComponent<CharacterController>()->move(vec3(0,0,0));
		} 

		
		if(inputEvent->keyCode == SDLK_DOWN && inputEvent->inputtype == keydown) 
		{
			this->getComponent<CharacterController>()->move(vec3(0,0,+keyboardSpeed));
		} 
		if(inputEvent->keyCode == SDLK_DOWN && inputEvent->inputtype == keyup) 
		{
			this->getComponent<CharacterController>()->move(vec3(0,0,0));
		} 	


		if(inputEvent->keyCode == SDLK_SPACE && inputEvent->inputtype == keydown) 
		{
			this->getComponent<CharacterController>()->move(vec3(0,+keyboardSpeed,0));
		} 
		if(inputEvent->keyCode == SDLK_SPACE && inputEvent->inputtype == keyup) 
		{
			this->getComponent<CharacterController>()->move(vec3(0,0,0));
		} 	

	if(inputEvent->inputtype == mousemotion)
	{
		this->getComponent<CharacterController>()->rotate(vec3(mouseSpeed*(screenwidth / 2 - inputEvent->MouseX),mouseSpeed*(screenheight / 2 - inputEvent->MouseY),0));
	}
}
