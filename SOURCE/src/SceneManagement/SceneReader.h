#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0


#include <vector>
#include <map>
#include <string>

using namespace std;

class Key
{
public:
	string name;
	vector<pair<string, string>> values;
	Key(string name);
	void registerValue(string key, string value);
	string getValue(string name);
};

class Attribute
{
public:
	string name;
	vector<Key*> keys;
	Attribute(string name);
	void registerKey(Key* key);
	Key* getKey(string name);
};

class Property
{
public:
	string name;
	vector<Attribute*> attributes;
	Property(string name);
	void registerAttribute(Attribute* attribute);
	Attribute* getAttribute(string name);
};

class Section
{
public:
	string name;
	vector<Property*> properties;
	Section(string name);
	void registerProperty(Property* propertyToRegister);
	Property* getProperty(string name);
};

class Scene
{
public:
	vector<Section*> sections;
	string name;
	Scene(string name);
	void registerSection(Section* section);
	Section* getSection(string name);
};

class SceneReader
{
public:
	static SceneReader* exemplar();
	Scene* activeScene;
	int sectionCounter;
	int propertyCounter;
	int keyCounter;
	int attributeCounter;
	SceneReader(void);
	void readFile(string filename);
	void handleString(string s);
	void loadScene(string name);
	~SceneReader(void);

private:
	static SceneReader* instance;

};