#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0
#include "../conf.h"

#ifdef OS_WIN
#include <Windows.h>
#endif
#include <glew.h>
#ifdef OS_OSX
#include <OpenGL/OpenGL.h>
#endif
#ifdef OS_WIN
#include <gl/GL.h>
#endif
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <map>
#include <iostream>
#include <type_traits>


#include <SDL.h>
#include <SDL_opengl.h>

#include <glm.hpp>
#include <ext.hpp>

#include "../tools.h"

using namespace std;
using namespace glm;
 
class Registrator
{
public:
	static void registerClasses();
};

class Base
{
public:
	virtual void update() = 0;

	void construct(vector<void*> values)
	{

	}
};


class Builder
{
public:
	virtual Base* make(vector<pair<string, string>> values) = 0;
};

template<class T> class ConcreteBuilder: public Builder
{
public:
	T* make(vector<pair<string, string>> values){

		T* temp = new T();
		vector<void*> abstractValues;

		for (unsigned int i = 0; i < values.size(); i++)
		{
			if (values[i].first == "int")
			{
				int a = strnum(values[i].second);
				abstractValues.push_back(new int(a));
			}

			else if (values[i].first == "float")
			{

			}

			else if(values[i].first == "string")
			{
				abstractValues.push_back(new string(values[i].second));
			}
		}

		temp->construct(abstractValues);

		return temp;
	}
};

class ClassRegistration
{
public:
	ClassRegistration();
	~ClassRegistration(void);

	map<string, Builder*> classes;

	static ClassRegistration* exemplar();

	template<class T>
	void registerClass(string name)
	{
		classes[name] = new ConcreteBuilder<T>();
	}


private:
	static ClassRegistration* instance;
};
