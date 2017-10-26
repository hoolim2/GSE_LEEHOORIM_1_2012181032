#pragma once
#include "Object.h"
#define MAX_OBJECTS_COUNT 50

class SceneMngr
{
public:
	SceneMngr();
	~SceneMngr();
	Object m_objects[MAX_OBJECTS_COUNT];

	void Add(Object a[], int index, float x, float y);
	void Collide();

};
