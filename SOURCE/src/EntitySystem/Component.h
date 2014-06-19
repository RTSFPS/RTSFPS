#pragma once
#define NO_SDL_GLEXT
#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

template<class T>
class Component
{
public:
	T* parent;
	void addParent(T* tt){
		parent = tt;
	}

	virtual ~Component(void)
	{
	}
};

