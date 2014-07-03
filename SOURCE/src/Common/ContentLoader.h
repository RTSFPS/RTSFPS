#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0


#include <string>
#include "../Components/Mesh.h"
#include "../Components/Material.h"
#include "../Factories/MeshFactory.h"


using namespace std;





class ContentLoader
{
public:

	static ContentLoader* getInstance();

	void loadContent(string levelFileName);
	void freeContent();

	Mesh* Cubus;
	Mesh* sphere;

	Mesh* plane;

	Material* checkerMaterial;
	Material* greenMaterial;
	Material* planeMaterial;


	Material* skyboxMaterial;

private:
	static ContentLoader* instance;

	ContentLoader();

	Material* loadMaterial(string shaderName, string diffuseTexture);
	Material* loadSkyBoxMaterial(string shaderName, string skyboxPath);

	void loadMeshes();
	void loadShaders();
	void loadMaterials();
};
