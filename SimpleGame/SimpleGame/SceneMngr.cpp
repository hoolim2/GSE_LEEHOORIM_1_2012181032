#include "stdafx.h"
#include "iostream"
#include "SceneMngr.h"
#include "Object.h"
#include "cstdlib"
#include "ctime"

using namespace std;

float objx = rand() % 250;
float objy = rand() % 250;

SceneMngr::SceneMngr(int width,int height)
{
	m_renderer = new Renderer(width, height);
	B_renderer = new Renderer(width, height);
	B_texBuilding = B_renderer->CreatePngTexture("./Resource/megaman.png");

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

void SceneMngr::DrawAllObj()
{
	m_renderer->DrawSolidRect(0, 0, 0, m_windowWidth, 0, 0, 0, 0.4);

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objects[i] != NULL)
		{
			// Renderer Test
			if (m_objects[i]->type == 2)
			{
				B_renderer->DrawTexturedRect(m_objects[i]->x,
					m_objects[i]->y,
					0,
					m_objects[i]->size,
					m_objects[i]->r,
					m_objects[i]->g,
					m_objects[i]->b,
					m_objects[i]->a,
					B_texBuilding);
			}
			else {
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
}

int SceneMngr::AddCommonObj(float x, float y)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objects[i] == NULL)
		{
			m_objects[i] = new Object(x, y, i, OBJECT_CHARACTER);
			return i;
		}
	}
	return -1;
}

int SceneMngr::AddBuildingObj(int index)
{
	for (int i = 0; i < index; i++)
	{
		if (m_objects[i] == NULL)
		{
			m_objects[i]= new Object(0, 0,i, OBJECT_BUILDING);
			return i;
		}
	}
	return -1;
}

int SceneMngr::AddBulletObj(int index)
{
	if (!m_objects[index] == NULL)
	{
		if (m_objects[index]->type == 2 && m_objects[index]->bulletCoolTime >= 500)
		{
			for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
			{
				if (m_objects[i] == NULL)
				{
					m_objects[i] = new Object(m_objects[index]->x, m_objects[index]->y, index, OBJECT_BULLET);
					m_objects[index]->bulletCoolTime = 0;
					return i;
				}
			}
		}
	}
	return -1;
}

int SceneMngr::AddArrowObj(int index)
{
	if (!m_objects[index] == NULL)
	{
		if (m_objects[index]->type == 1 && m_objects[index]->arrowCoolTime >= 500)
		{
			for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
			{
				if (m_objects[i] == NULL)
				{
					m_objects[i] = new Object(m_objects[index]->x, m_objects[index]->y, index,OBJECT_ARROW);
					m_objects[index]->arrowCoolTime = 0;
					return i;
				}
			}
		}
	}
	return -1;
}

void SceneMngr::CollideCheck()
{
	int collisionCount = 0;

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		collisionCount = 0;
		if (m_objects[i] != NULL)
		{
			for (int j = 0; j < MAX_OBJECTS_COUNT; j++)
			{
				int enemylife = 0;
				if (i == j)
					continue;

				if (m_objects[j] != NULL)
				{
					if (!((m_objects[i]->type == m_objects[j]->type||
						m_objects[i]->team == m_objects[j]->team ||
						m_objects[i]->type * m_objects[j]->type == 6)))
					{
						float left, top, right, bottom, left1, top1, right1, bottom1;

						left = m_objects[i]->x - m_objects[i]->size / 2.0f;
						bottom = m_objects[i]->y - m_objects[i]->size / 2.0f;
						right = m_objects[i]->x + m_objects[i]->size / 2.0f;
						top = m_objects[i]->y + m_objects[i]->size / 2.0f;
						left1 = m_objects[j]->x - m_objects[j]->size / 2.0f;
						bottom1 = m_objects[j]->y - m_objects[j]->size / 2.0f;
						right1 = m_objects[j]->x + m_objects[j]->size / 2.0f;
						top1 = m_objects[j]->y + m_objects[j]->size / 2.0f;
						if (BoxCollisionTest(left, bottom, right, top, left1, bottom1, right1, top1))
						{
							collisionCount++;
						}

					}
				}
			}
			if (collisionCount > 0)
			{
				m_objects[i]->r = 1;
				m_objects[i]->g = 0;
				m_objects[i]->b = 0;
				m_objects[i]->a = 1;
				m_objects[i]->life -= 10;
				DeleteObj();
			}
			else
			{
				if (m_objects[i]->type == 1)
				{
					m_objects[i]->r = 1;
					m_objects[i]->g = 1;
					m_objects[i]->b = 1;
					m_objects[i]->a = 1;
					DeleteObj();
				}
				else if (m_objects[i]->type == 4)
				{
					m_objects[i]->r = 0;
					m_objects[i]->g = 1;
					m_objects[i]->b = 0;
					m_objects[i]->a = 1;
					DeleteObj();
				}
			}
		}
	}
}

bool SceneMngr::BoxCollisionTest(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1)
{
	if (minX > maxX1)
		return false;
	if (maxX < minX1)
		return false;

	if (minY > maxY1)
		return false;
	if (maxY < minY1)
		return false;

	return true;
}


void SceneMngr::Update(float elapsedTime)
{

	CollideCheck();
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objects[i] != NULL)
		{
			m_objects[i]->Update(elapsedTime);
		}
	}
}

void SceneMngr::DeleteObj()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objects[i] != NULL)
		{
			if (m_objects[i]->life <= 0)
			{
				delete m_objects[i];
				m_objects[i] = NULL;
			}
		}
	}
}

