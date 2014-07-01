#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "../GraphicTools/GLstuff.h"
#include "../SystemTools/OBJparser.h"
#include "ContentLoader.h"
#include "../conf.h"
#include "../tools.h"
#include "../Factories/MeshFactory.h"
#include "../Components/Material.h"
#include "../GraphicTools/shader.h"
#include "../SystemTools/ObjectCreator.h"

using namespace std;



ContentLoader* ContentLoader::instance = NULL;


ContentLoader::ContentLoader()
{
}


ContentLoader* ContentLoader::getInstance()
{
	if (instance==NULL) 
	{
		instance = new ContentLoader;
	} 

	return instance;
}


void ContentLoader::loadContent(string levelFileName)
{
	
	loadMeshes();
	loadMaterials();
}

void ContentLoader::freeContent()
{
	delete this->instance;

}


Mesh* loadMesh(string filename);

void ContentLoader::loadMeshes()
{
	Cubus = loadMesh("scene/cube.obj");
	sphere = loadMesh("scene/sphere.obj");

	plane = createPrimitive(primitivetype::plane);
}

Material* ContentLoader::loadMaterial(string shaderName, string diffuseTexture)
{
		
	shader* shaderr = new shader(DATAfolder+shaderName);
	unsigned int tempShaderID = shaderr->prog;
	unsigned int tempTextureID = loadTexture(DATAfolder+diffuseTexture);
	Material* m = new Material(Cubus->materialName, tempShaderID ,tempTextureID);

	return m;
}


Material* ContentLoader::loadSkyBoxMaterial(string shaderName, string skyboxPath)
{
	shader* shaderr = new shader(DATAfolder+shaderName);
	unsigned int tempShaderID = shaderr->prog;

	SDL_Surface *xpos = IMG_Load(string(DATAfolder+skyboxPath+"/xpos.jpg").c_str());
	if (!xpos) error("[loadSkyBoxMaterial] xpos.jpg not loaded");
	SDL_Surface *xneg = IMG_Load(string(DATAfolder+skyboxPath+"/xneg.jpg").c_str());
	if (!xneg) error("[loadSkyBoxMaterial] xneg.jpg not loaded");
	SDL_Surface *ypos = IMG_Load(string(DATAfolder+skyboxPath+"/ypos.jpg").c_str()); 
	if (!ypos) error("[loadSkyBoxMaterial] ypos.jpg not loaded");
	SDL_Surface *yneg = IMG_Load(string(DATAfolder+skyboxPath+"/yneg.jpg").c_str());
	if (!yneg) error("[loadSkyBoxMaterial] yneg.jpg not loaded");
	SDL_Surface *zpos = IMG_Load(string(DATAfolder+skyboxPath+"/zpos.jpg").c_str()); 
	if (!zpos) error("[loadSkyBoxMaterial] zpos.jpg not loaded");
	SDL_Surface *zneg = IMG_Load(string(DATAfolder+skyboxPath+"/zneg.jpg").c_str());
	if (!zneg) error("[loadSkyBoxMaterial] zneg.jpg not loaded");

	unsigned int cubemap_texture;

	glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_CUBE_MAP);
    glGenTextures(1, &cubemap_texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, xpos->w, xpos->h, 0, xpos->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, xpos->pixels);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, xneg->w, xneg->h, 0, xneg->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, xneg->pixels);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, ypos->w, ypos->h, 0, ypos->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, ypos->pixels);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, yneg->w, yneg->h, 0, yneg->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, yneg->pixels);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, zpos->w, zpos->h, 0, zpos->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, zpos->pixels);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, zneg->w, zneg->h, 0, zneg->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, zneg->pixels);

	SDL_FreeSurface(xneg);  
	SDL_FreeSurface(xpos);
	SDL_FreeSurface(yneg);  
	SDL_FreeSurface(ypos);
	SDL_FreeSurface(zneg);  
	SDL_FreeSurface(zpos);
	
	Material* m = new Material("skybox Material", tempShaderID ,cubemap_texture);

	return m;
}


void ContentLoader::loadMaterials()
{
	checkerMaterial = loadMaterial("shader/texture","graph/checker.jpg");
	greenMaterial = loadMaterial("shader/texture","graph/green.jpg");
	skyboxMaterial = loadSkyBoxMaterial("shader/skybox","graph/skybox");
	planeMaterial = loadMaterial("shader/texture","graph/floor.jpg");
}


Mesh* loadMesh(string filename)
{
	Mesh* tempMesh = createMesh(obj, filename);
	return tempMesh;
}