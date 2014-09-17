#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <vector>
#include <map>

#include <glm.hpp>
#include <ext.hpp>


#include "../Components/MeshRenderer.h"
#include "../Components/TextRenderer.h"
#include "RenderManager.h"


using namespace std;
using namespace glm;

RenderManager* RenderManager::instance = 0;

RenderManager* RenderManager::exemplar()
{
	if(instance == 0)
	{
		instance = new RenderManager();
	}

	return instance;
}
/*
void RenderManager::registerSkyBoxRenderer(SkyBoxRenderer* renderer)
{
	this->skyBoxRenderer = renderer;
}
*/

void RenderManager::registerTextRenderer(TextRenderer* renderer)
{
	this->textRenderers.push_back(renderer);
}


void RenderManager::registerMeshRenderer(MeshRenderer* renderer)
{
	this->meshRenderers.push_back(renderer);
}


void RenderManager::draw()
{
	//this->skyBoxRenderer->draw();

	for(unsigned int i = 0; i < this->meshRenderers.size(); i++)
	{
		this->meshRenderers[i]->draw();
	}
	
	
	for(unsigned int i = 0; i < this->textRenderers.size(); i++)
	{
		this->textRenderers[i]->draw();
	}
	
}