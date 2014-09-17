#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include "SceneBuilder.h"
#include "../EntityComponentSystem/Component.h"
#include "../EntityComponentSystem/Entity.h"


SceneBuilder::SceneBuilder()
{
}


SceneBuilder::~SceneBuilder()
{
}

void SceneBuilder::update()
{
	for (unsigned int i = 0; i < this->entitys.size(); i++)
	{
		this->entitys[i]->update();
	}
}


void SceneBuilder::buildScene()
{
	ClassRegistration* r = ClassRegistration::exemplar();
	SceneReader* reader = SceneReader::exemplar();

	this->entitycounter = 0;

	Section* entitySection = reader->activeScene->getSection("Entitys");

	for (unsigned int i = 0; i < entitySection->properties.size(); i++)
	{
		this->entitys.push_back(new Entity());

		Attribute* componentsAttribute = entitySection->properties[i]->getAttribute("Components");

		for (unsigned int i = 0; i < componentsAttribute->keys.size(); i++)
		{
			string className = componentsAttribute->keys[i]->name;
			entitys[entitycounter]->addComponent((Component<Entity>*)r->classes[className]->make(componentsAttribute->keys[i]->values));
		}

		this->entitycounter++;
	}
}
