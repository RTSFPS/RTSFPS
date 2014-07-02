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
	keyboardSpeed = 500;
}

void Player::move(vec3 pos)
{
	
	Transform* transform = this->getComponent<Transform>();

	vec4 lookvec = transform->getDirection()*vec4(pos,1);
	
	transform->position += vec3(lookvec);

}


void Player::rotate(vec3 rot)
{
	Transform* transform = getComponent<Transform>();
	

	 transform->rotation.y = fmodf(transform->rotation.y, 360.0f);

	if (transform->rotation.y<0) transform->rotation.y += 360.0f;

	if(transform->rotation.x > 90.0f) transform->rotation.x = 90.0f;
    else if(transform->rotation.x < -90.0f) transform->rotation.x = -90.0f;
	
		transform->rotation.x += rot.y;
		transform->rotation.y += rot.x;
		transform->rotation.z += rot.z;
}

void Player::handleEvent(Event* e)
{
	InputEvent* inputEvent = (InputEvent*)e;
		vec3 movement=vec3(0,0,0);
		if (inputEvent->keyState[SDL_SCANCODE_RIGHT]) { movement.x=keyboardSpeed; } 
		if (inputEvent->keyState[SDL_SCANCODE_LEFT]) { movement.x=-keyboardSpeed; }
		if (inputEvent->keyState[SDL_SCANCODE_UP]) { movement.z=-keyboardSpeed; } 
		if (inputEvent->keyState[SDL_SCANCODE_DOWN]) { movement.z=+keyboardSpeed; } 
		move(movement * 0.004f);


	if(inputEvent->inputtype == mousemotion)
	{
		rotate(vec3(mouseSpeed*(screenwidth / 2 - inputEvent->MouseX),mouseSpeed*(screenheight / 2 - inputEvent->MouseY),0));
		//this->getComponent<Transform>()->rotation += vec3(mouseSpeed*(screenwidth / 2 - inputEvent->MouseX),mouseSpeed*(screenheight / 2 - inputEvent->MouseY),0);
	}
}
