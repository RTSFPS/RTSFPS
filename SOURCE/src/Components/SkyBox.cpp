#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <glm.hpp>
#include <ext.hpp>
#include "SkyBox.h"

using namespace glm;

SkyBox::SkyBox()
{
	skyboxVertices[0]  = -1.0;
	skyboxVertices[1]  =  1.0;
	skyboxVertices[2]  =  1.0;
	skyboxVertices[3]  = -1.0;
	skyboxVertices[4]  = -1.0;
	skyboxVertices[5]  =  1.0;
    skyboxVertices[6]  =  1.0;
	skyboxVertices[7]  = -1.0;
	skyboxVertices[8]  =  1.0;
    skyboxVertices[9]  =  1.0;
	skyboxVertices[10] =  1.0;
	skyboxVertices[11] =  1.0;
    skyboxVertices[12] = -1.0;
	skyboxVertices[13] =  1.0;
	skyboxVertices[14] = -1.0;
    skyboxVertices[15] = -1.0;
	skyboxVertices[16] = -1.0;
	skyboxVertices[17] = -1.0;
    skyboxVertices[18] =  1.0;
	skyboxVertices[19] = -1.0;
	skyboxVertices[20] = -1.0;
    skyboxVertices[21] =  1.0;
	skyboxVertices[22] =  1.0;
	skyboxVertices[23] = -1.0;

	skyboxIndices[0]  = 0;
	skyboxIndices[1]  = 1;
	skyboxIndices[2]  = 2;
	skyboxIndices[3]  = 3;
	skyboxIndices[4]  = 3;
	skyboxIndices[5]  = 2;
	skyboxIndices[6]  = 6;
	skyboxIndices[7]  = 7;
    skyboxIndices[8]  = 7;
	skyboxIndices[9]  = 6;
	skyboxIndices[10] = 5;
	skyboxIndices[11] = 4;
    skyboxIndices[12] = 4;
	skyboxIndices[13] = 5;
	skyboxIndices[14] = 1;
	skyboxIndices[15] = 0;
    skyboxIndices[16] = 0;
	skyboxIndices[17] = 3;
	skyboxIndices[18] = 7;
	skyboxIndices[19] = 4;
	skyboxIndices[20] = 1;
	skyboxIndices[21] = 2;
	skyboxIndices[22] = 6;
	skyboxIndices[23] = 5;
};

