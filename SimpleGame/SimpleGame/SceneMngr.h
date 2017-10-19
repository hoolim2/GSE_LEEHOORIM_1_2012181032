#pragma once
#include "Object.h"
#define MAX_OBJECTS_COUNT 50

class SceneMngr
{
public:
	SceneMngr();
	~SceneMngr();

	void Add(Object** a);
	void Update();

	Object *m_objects[MAX_OBJECTS_COUNT];
};

