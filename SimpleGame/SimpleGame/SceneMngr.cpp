#include "stdafx.h"
#include "iostream"
#include "SceneMngr.h"
#include "Object.h"
#include "cstdlib"
#include "ctime"
#define MAX_OBJECTS_COUNT 50

using namespace std;

float objx = rand() % 250;
float objy = rand() % 250;

SceneMngr::SceneMngr()
{
}


SceneMngr::~SceneMngr()
{
}

void SceneMngr::Add(Object a[], int index)
{
	m_objects[index] = a[index];

	srand((unsigned int)time(NULL));

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		a[i].x = rand() % 500 - 250;
		a[i].y = rand() % 500 - 250;
		a[i].spd = rand() % 5 + 1;
		a[i].vecx = rand() % 5-2.5;
		a[i].vecy = rand() % 5-2.5;
	}
}

void SceneMngr::Collide()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		for (int j = i+1; j < MAX_OBJECTS_COUNT; j++)
		{
			if ((m_objects[i].x - (m_objects[i].size / 2) <= m_objects[j].x + (m_objects[j].size / 2) &&
				m_objects[i].y - (m_objects[i].size / 2) <= m_objects[j].y + (m_objects[j].size / 2))&&
				(m_objects[i].x + (m_objects[i].size / 2) >= m_objects[j].x - (m_objects[j].size / 2) &&
				m_objects[i].y + (m_objects[i].size / 2) >= m_objects[j].y - (m_objects[j].size / 2)))
			{
				m_objects[j].colck = true;
				m_objects[i].colck = true;
			}
		}
	}
}
