#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0
#include <glew.h>
#include <string>
#include <SDL.h>
#include <glm.hpp>
#include <ext.hpp>
#include "../EntitySystem/Entity.h"
#include "../Components/RenderManager.h"
#include "../Components/TextRenderer.h"
#include "../Components/Transform.h"
#include "../Components/FramesPerSecond.h"
#include "EntityFactory.h"


using namespace std;
using namespace glm;

Entity* createFramesPerSecondContainer(RenderManager* renderManager,string fontFileName, int size, uint32 color, vec3 position)
{
	Entity* temp = new Entity();
	TextRenderer* textRenderer = new TextRenderer(renderManager, fontFileName, size, color);
	Transform* transform = new Transform(position);
	temp->addComponent<TextRenderer>(textRenderer);
	temp->addComponent<Transform>(transform);
	temp->addComponent<FramesPerSecond>();
	return temp;
}

Entity* createRenderManagerContainer()
{
	Entity* temp = new Entity();
	temp->addComponent<RenderManager>();
	return temp;
}
