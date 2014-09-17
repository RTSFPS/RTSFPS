#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <glew.h>
#include <string>
#include <SDL.h>


#include "../GraphicTools/DrawFont.h"
#include "../EntityComponentSystem/Component.h"
#include "../EntityComponentSystem/Entity.h"


using namespace std;


class TextRenderer : public Component<Entity>
{
public:
	void construct(vector<void*> values);
	void changeText(string text);
	void draw();
private:
	DrawFont* font;
	Uint32 color;
	string text;
};