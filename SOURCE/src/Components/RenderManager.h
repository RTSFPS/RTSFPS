#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0
#include <glew.h>
#include <vector>
#include <SDL.h>
#include <glm.hpp>
#include <ext.hpp>

#include "../EntitySystem/Component.h"
#include "../EntitySystem/Entity.h"
#include "SkyBoxRenderer.h"
#include "TextRenderer.h"
#include "MeshRenderer.h"
#include "Camera.h"

using namespace std;
using namespace glm;

class RenderManager : public Component<Entity>
{
public:
	
	vector<MeshRenderer*> meshRenderers;
	vector<TextRenderer*> textRenderers;

	SkyBoxRenderer* skyboxRenderer;

	Camera* camera;

	void registerTextRenderer(TextRenderer* textRenderer);
	void registerMeshRenderer(MeshRenderer* meshRenderer);

	void registerSkyBoxRenderer(SkyBoxRenderer* skyboxRenderer);

	void registerCamera(Camera* camera);

	void addNewShaderSpecificRendererList(unsigned int shaderID);

	void draw();
};
