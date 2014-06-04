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
	template<class T>
	void addComponent(){
		T* t = new T();
		//Component<Entity>* c = t;
		t->addParent(this);
		//cout << t->parent << endl;
		components.push_back(t);
		
	}
public:
	//Entity(void){};
	~Entity(void){
		
	};
	template<class T>
	T* getComponent(){
		for(int i = 0; i < components.size(); i++){
			if(dynamic_cast<T*>(components[i]) != 0){
				return dynamic_cast<T*>(components[i]);
			}
		}
		addComponent<T>();
		return getComponent<T>();
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

