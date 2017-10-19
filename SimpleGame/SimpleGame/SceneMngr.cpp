#include "stdafx.h"
#include "SceneMngr.h"
#include "Object.h"
#include "cstdlib"
#include "ctime"

float objx = rand() % 250;
float objy = rand() % 250;

SceneMngr::SceneMngr()
{
}


SceneMngr::~SceneMngr()
{
}

void SceneMngr::Add()
{
	srand((unsigned int)time(NULL));
	const int MAX_OBJECTS_COUNT = 50;

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		//Object *m_objects[i] = new Object(rand() % 250, rand() % 250, 0, 10, 0, 0, 0, 0, 1, 1, 1) ;
	}
}

void SceneMngr::Update()
{
}
