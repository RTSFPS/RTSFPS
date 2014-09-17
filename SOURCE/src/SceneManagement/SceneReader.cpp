#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include "../tools.h"
#include "SceneReader.h"

using namespace std;

Section* Scene::getSection(string name)
{
	for(unsigned int i = 0; i < this->sections.size(); i++)
	{
		if(this->sections[i]->name == name)
		{
			return this->sections[i];
		}
	}

	error("Section "+name+" not found.");
	return NULL;
}

Property* Section::getProperty(string name)
{
	for(unsigned int i = 0; i < this->properties.size(); i++)
	{
		if(this->properties[i]->name == name)
		{
			return this->properties[i];
		}
	}

	error("Property "+name+" not found.");
	return NULL;
}

Attribute* Property::getAttribute(string name)
{
	for(unsigned int i = 0; i < this->attributes.size(); i++)
	{
		if(this->attributes[i]->name == name)
		{
			return this->attributes[i];
		}
	}

	error("Attribute "+name+" not found.");
	return NULL;
}

Key* Attribute::getKey(string name)
{
	for(unsigned int i = 0; i < this->keys.size(); i++)
	{
		if(this->keys[i]->name == name)
		{
			return this->keys[i];
		}
	}
	error("Key "+name+" not found.");
	return NULL;
}

SceneReader::SceneReader(void)
{
}


SceneReader::~SceneReader(void)
{
}

Scene::Scene(string name)
{
	this->name = name;
}

Section::Section(string name)
{
	this->name = name;
}

Property::Property(string name)
{
	this->name = name;
}

Attribute::Attribute(string name)
{
	this->name = name;
}

Key::Key(string name)
{
	this->name = name;
}

void Scene::registerSection(Section* section)
{
	this->sections.push_back(section);
}

vector<string> splitKeyValue(string s)
{
	string temp1 = "";
	string temp2 = "";
	bool temp = false;
	vector<string> tempVec;

	for(unsigned int i = 0; i < s.size(); i++)
	{
		if(s[i] == '=')
		{
			temp = true;
		}
		if(!temp)
		{
			temp1.push_back(s[i]);
		}
		else
		{
			if(s[i] != '=')
			{
				temp2.push_back(s[i]);
			}
		}
	}

	tempVec.push_back(temp1);
	tempVec.push_back(temp2);
	return tempVec;
}

string getRidOfSpecialSigns(string s)
{
	string temp = "";

	for(unsigned int i= 0; i < s.size(); i++)
	{
		if(s[i] != '[' && s[i] != ']'  && s[i] != '('  && s[i] != ')'  && s[i] != '<'  && s[i] != '>'  && s[i] != '+'  && s[i] != '{'  && s[i] != '}' && s[i] != ' ')
		{
			temp.push_back(s[i]);
		}
	}

	return temp;
}

void SceneReader::handleString(string s)
{
	string temp = "";
	switch(s[0])
	{
	case '[':
		propertyCounter = -1;
		sectionCounter++;
		this->activeScene->registerSection(new Section(getRidOfSpecialSigns(s)));
		//cout << testScene->sections.size() << endl;
		break;
	case'(':
		attributeCounter = -1;
		propertyCounter++;
		this->activeScene->sections[sectionCounter]->registerProperty(new Property(getRidOfSpecialSigns(s)));
		//cout << testScene->sections[sectionCounter]->properties.size();
		break;
	case '<':
		keyCounter = -1;
		attributeCounter++;
		this->activeScene->sections[sectionCounter]->properties[propertyCounter]->registerAttribute(new Attribute(getRidOfSpecialSigns(s)));
		break;
	case '+':
		keyCounter++;
		this->activeScene->sections[sectionCounter]->properties[propertyCounter]->attributes[attributeCounter]->registerKey(new Key(getRidOfSpecialSigns(s)));
		break;
	case '{':
		temp = getRidOfSpecialSigns(s);
		this->activeScene->sections[sectionCounter]->properties[propertyCounter]->attributes[attributeCounter]->keys[keyCounter]->registerValue(splitKeyValue(temp)[0], splitKeyValue(temp)[1]);
		break;
	default:
		break;
	}
}

void SceneReader::readFile(string filename)
{
	sectionCounter = -1;
	this->activeScene = new Scene(filename);

	ifstream stream;
	stream.open(filename);
	if(stream.is_open())
	{
		while(!stream.eof())
		{
			char* str = new char[256];
			stream.getline(str, 256);
			handleString(str);
		}
	}

	//cout << testScene->sections[1]->name;
}

void SceneReader::loadScene(string name)
{
	readFile(name);
}

void Section::registerProperty(Property* propertyToRegister)
{
	this->properties.push_back(propertyToRegister);
}

void Property::registerAttribute(Attribute* attribute)
{
	this->attributes.push_back(attribute);
}

void Attribute::registerKey(Key* key)
{
	this->keys.push_back(key);
}

void Key::registerValue(string key, string value)
{
	this->values.push_back(std::pair<string, string>(key, value));
}


SceneReader* SceneReader::instance = 0;

SceneReader* SceneReader::exemplar()
{
	if(SceneReader::instance == 0)
	{
		SceneReader::instance = new SceneReader();
	}
	return SceneReader::instance;
}
