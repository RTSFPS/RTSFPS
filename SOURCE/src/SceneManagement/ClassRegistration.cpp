#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <string>
#include <map>

#include <glm.hpp>
#include <ext.hpp>


#include "../Components/Transform.h"
#include "../Components/TextRenderer.h"
#include "../Components/MeshRenderer.h"
#include "ClassRegistration.h"

using namespace std;
using namespace glm;
 



ClassRegistration::ClassRegistration()
{
}


ClassRegistration::~ClassRegistration(void)
{
}

ClassRegistration* ClassRegistration::instance = 0;

ClassRegistration* ClassRegistration::exemplar()
{
	if(instance == 0)
	{
		instance = new ClassRegistration();
	}

	return instance;
}

void Registrator::registerClasses()
{
	ClassRegistration* classRegistrationInstance = ClassRegistration::exemplar();

	classRegistrationInstance->registerClass<Transform>("Transform");
	classRegistrationInstance->registerClass<TextRenderer>("TextRenderer");
	classRegistrationInstance->registerClass<MeshRenderer>("MeshRenderer");
}