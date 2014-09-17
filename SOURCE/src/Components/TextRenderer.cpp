#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0
#include <glew.h>
#include <string>
#include <SDL.h>

#include <glm.hpp>
#include <ext.hpp>


#include "../GraphicTools/DrawFont.h"
#include "Transform.h"
#include "../Managers/RenderManager.h"
#include "TextRenderer.h"

using namespace std;
using namespace glm;

void TextRenderer::construct(vector<void*> values)
{
	this->font = new DrawFont(DATAfolder + *(string*)values[0], *(int*)values[1]);
	this->color = *(int*)values[2];
	this->text = *(string*)values[3];
	RenderManager::exemplar()->registerTextRenderer(this);
}

void TextRenderer::draw()
{
	Transform* transform = this->parent->getComponent<Transform>();
	int x = (int)transform->x;
	int y = (int)transform->y;
	this->font->glTextOut(x, y, this->text, this->color);	
}

void TextRenderer::changeText(string text)
{
	this->text = text;
}