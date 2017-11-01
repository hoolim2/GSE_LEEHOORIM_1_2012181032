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

SceneMngr::SceneMngr(int width,int height)
{
	m_renderer = new Renderer(width, height);
	if (!m_renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}


	m_windowWidth = width;
	m_windowHeight = height;

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		m_objects[i] = NULL;
	}
}


SceneMngr::~SceneMngr()
{
}

void SceneMngr::DrawObj()
{
	m_renderer->DrawSolidRect(0, 0, 0, m_windowWidth, 0, 0, 0, 0.4);

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objects[i] != NULL)
		{
			// Renderer Test
			m_renderer->DrawSolidRect(
				m_objects[i]->x,
				m_objects[i]->y,
				0,
				m_objects[i]->size,
				m_objects[i]->r,
				m_objects[i]->g,
				m_objects[i]->b,
				m_objects[i]->a
			);
		}
	}
}

int SceneMngr::Add(float x, float y)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objects[i] == NULL)
		{
			m_objects[i] = new Object(x, y);
			return i;
		}
	}
	return -1;
}

void SceneMngr::Collide()
{
}


void SceneMngr::Update(float elapsedTime)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objects[i] != NULL)
		{
			m_objects[i]->Update(elapsedTime);
		}

	}
}
