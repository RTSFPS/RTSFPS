#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0


#include "RenderManager.h"
#include "TextRenderer.h"
#include "MeshRenderer.h"
#include "SkyBoxRenderer.h"
#include "Material.h"
#include "Camera.h"


void RenderManager::registerTextRenderer(TextRenderer* textRenderer)
{
	this->textRenderers.push_back(textRenderer);
}


void RenderManager::registerMeshRenderer(MeshRenderer* renderer)
{
	this->meshRenderers.push_back(renderer);
}


void RenderManager::registerSkyBoxRenderer(SkyBoxRenderer* renderer)
{
	this->skyboxRenderer=renderer;
}

void RenderManager::draw()
{
	skyboxRenderer->draw(this->camera->cameraProjectionMatrix * this->camera->cameraRotateMatrix);

	for(unsigned int i = 0; i < this->meshRenderers.size(); i++)
	{
		meshRenderers[i]->draw(this->camera->cameraProjectionMatrix * this->camera->cameraRotateMatrix * this->camera->cameraTranslateMatrix);
	}

	for(unsigned int i = 0; i < this->textRenderers.size(); i++)
	{
		this->textRenderers[i]->draw();
	}

	
	camera->update();

}

void RenderManager::registerCamera(Camera* camera)
{
	this->camera = camera;
}