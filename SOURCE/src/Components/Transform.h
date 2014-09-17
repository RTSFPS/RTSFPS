#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include "../EntityComponentSystem/Entity.h"
#include "../EntityComponentSystem/Component.h"


class Transform : public Component<Entity>
{
public:
	int x, y, z;

	void construct(vector<void*> values)
	{
		this->x = *(int*)values[0];
		this->y = *(int*)values[1];
		this->z = *(int*)values[2];
	}

	void update()
	{
	}
};