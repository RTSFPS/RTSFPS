#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <glm.hpp>
#include <ext.hpp>
#include "Material.h"
#include <string>

using namespace glm;
using namespace std;

Material::Material(string materialID, unsigned int shaderID, unsigned int textureID)
{
	this->materialID = materialID;
	this->shaderID = shaderID;
	this->textureID = textureID;
}

Material::~Material()
{


}