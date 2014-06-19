#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <string>
#include <SDL.h>
#include "../GraphicTools/drawfont.h"
#include "Transform.h"
#include "RenderManager.h"
#include "TextRenderer.h"
#include "../EntitySystem/Component.h"

using namespace std;


TextRenderer::TextRenderer(Component* renderManager,string fontFileName, int size, Uint32 color)
{
	
	this->font = new drawfont(fontFileName, size);
	this->color = color;
	RenderManager* rManager = (RenderManager*)renderManager;
	rManager->registerTextRenderer(this);
	
}

void TextRenderer::draw()
{
	Transform* transform = this->parent->getComponent<Transform>();
	int x = (int)transform->position.x;
	int y = (int)transform->position.y;
	this->font->glTextOut(x, y, this->text, this->color);
	
}

void TextRenderer::changeText(string text)
{
	this->text = text;
}

