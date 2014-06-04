#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

template<class T>
class Component
{
public:
	T* t;
	void addParent(T* tt){
		t = tt;
	}

	Component(void)
	{
	}


	virtual ~Component(void)
	{
	}

};

