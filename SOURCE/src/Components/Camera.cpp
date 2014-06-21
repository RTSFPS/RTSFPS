#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <glm.hpp>
#include <ext.hpp>

#include "../conf.h"
#include "Transform.h"
#include "Camera.h"
#include "../tools.h"

using namespace glm;

Camera::Camera()
{
	cameraRotateMatrix = mat4(1);
	cameraTranslateMatrix = mat4(1);

	cameraProjectionMatrix = perspective(45.0f, (float) screenwidth / screenheight, 0.01f, 1000.0f);
}


void Camera::update()
{

	Transform* transform = this->parent->getComponent<Transform>();

	cameraRotateMatrix = mat4(1);
    cameraTranslateMatrix = mat4(1);
 
		cameraRotateMatrix = rotate(cameraRotateMatrix, -transform->rotation.x, vec3(1.0f, 0.0f, 0.0f));
		cameraRotateMatrix = rotate(cameraRotateMatrix, -transform->rotation.y, vec3(0.0f, 1.0f, 0.0f));
		cameraRotateMatrix = rotate(cameraRotateMatrix, -transform->rotation.z, vec3(0.0f, 0.0f, 1.0f));


	cameraTranslateMatrix = translate(cameraTranslateMatrix, -transform->position);

}