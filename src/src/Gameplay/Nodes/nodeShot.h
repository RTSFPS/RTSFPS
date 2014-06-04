#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0


#include "../../Engine/Entitys/Node.h"







class nodeShot : public Node
{
public:

	nodeShot();
   ~nodeShot();


	void update(void* data);
	void render();

private:


};
