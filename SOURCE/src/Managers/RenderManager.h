#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <vector>
#include <map>

#include <glm.hpp>
#include <ext.hpp>

#include "../Components/MeshRenderer.h"
#include "../Components/TextRenderer.h"



using namespace std;
using namespace glm;

class RenderManager
{
public:
	static RenderManager* exemplar();
	void registerTextRenderer(TextRenderer* renderer);
	void registerMeshRenderer(MeshRenderer* renderer);
	//void registerSkyBoxRenderer(SkyBoxRenderer* renderer);
	void draw(); 
private:
	static RenderManager* instance;
	vector<TextRenderer*> textRenderers;
	vector<MeshRenderer*> meshRenderers;
	//SkyBoxRenderer* skyBoxRenderer;
};


