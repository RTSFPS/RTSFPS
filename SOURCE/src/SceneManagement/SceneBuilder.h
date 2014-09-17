#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <vector>
#include "ClassRegistration.h"
#include "../EntityComponentSystem/Entity.h"
#include "SceneReader.h"


class SceneBuilder
{
public:
	vector<Entity*> entitys;

	int entitycounter;
	int componentcounter;

	SceneBuilder();
	~SceneBuilder();

	void buildScene();

	void update();
};