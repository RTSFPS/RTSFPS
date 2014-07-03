#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0
#include <glew.h>
#include <string>
#include <SDL.h>

#include "Renderer.h"
#include "../GraphicTools/DrawFont.h"
#include "../EntitySystem/Component.h"
#include "../EntitySystem/Entity.h"

using namespace std;


class TextRenderer : public Renderer
{
public:
	TextRenderer(Component* renderManager,string fontFileName, int size, Uint32 color);
	void changeText(string text);
	void draw();
private:
	DrawFont* font;
	Uint32 color;
	string text;
};
