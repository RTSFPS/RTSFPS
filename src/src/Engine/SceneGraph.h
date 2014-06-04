#pragma once 
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <list>
#include "Entitys/Node.h"

using namespace std;

class SceneGraph
{
public:
	list<Node*> Nodes; 
	 

	bool addNode(Node *n);
	void deleteNode(Node *n);
	
	~SceneGraph();
	
	void update(void *data);
	void render();
};


