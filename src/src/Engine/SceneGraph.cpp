#include "SceneGraph.h"

//#include "main.h"

#include <list>
#include "Entitys/Node.h"


bool SceneGraph::addNode(Node *n)
{
	Nodes.push_back(n);
	return true;
}



void SceneGraph::render()
{
	list<Node*>::iterator it;

	for (it = Nodes.begin(); it != Nodes.end(); it++)
	{
		(*it)->render();
	}
}

void SceneGraph::update(void *data)
{
	list<Node*>::iterator it;

	for (it = Nodes.begin(); it != Nodes.end(); it++)
	{
		(*it)->update(data);
	}
}


void SceneGraph::deleteNode(Node* n)
{
	Nodes.remove(n);
	n->~Node();
}


SceneGraph::~SceneGraph()
{
    
  	list<Node*>::iterator it;
    
	for (it = Nodes.begin(); it != Nodes.end(); it++)
	{
		(*it)->~Node();
	}
    
    Nodes.clear();
}

