#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <vector>
#include <iostream>
#include "Component.h"

using namespace std;

class Entity
{
private:
	vector<Component<Entity>*> components;
public:
	//Entity(void){};
	~Entity(void){
		
	};
	template<class T>
	void addComponent(){
		T* t = new T();
		t->addParent(this);
		components.push_back(t);	
	}

	template<class T>
	void addComponent(T* t){
		t->addParent(this);
		components.push_back(t);
		
	}


	template<class T>
	T* getComponent()
	{
		for(unsigned int i = 0; i < components.size(); i++)
		{
			if(dynamic_cast<T*>(components[i]) != 0)
			{
				return dynamic_cast<T*>(components[i]);
			}
		}
		return NULL;
	}

	template<class T>
	bool checkListForComponent(){
		for(int i = 0; i < components.size(); i++){
			if(dynamic_cast<T*>(components[i]) != 0){
				return true;
			}
		}
		return false;
	}
};

