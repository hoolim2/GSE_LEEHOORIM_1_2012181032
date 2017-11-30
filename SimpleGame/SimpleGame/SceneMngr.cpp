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
	B_texImage[0] = B_renderer->CreatePngTexture("./Resource/resistance.png");
	B_texImage[1] = B_renderer->CreatePngTexture("./Resource/polite.png");
	B_texImage[2] = B_renderer->CreatePngTexture("./Resource/linksprite_foward.png");
	B_texImage[3] = B_renderer->CreatePngTexture("./Resource/linksprite.png");
	B_texImage[4] = B_renderer->CreatePngTexture("./Resource/background.png");
	B_texImage[5] = B_renderer->CreatePngTexture("./Resource/particle.png");

	

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
	B_renderer->DrawTexturedRect(0, 0, 0, 800, 1, 1, 1, 1, B_texImage[4], 0.9);
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objects[i] != NULL)
		{
			// Renderer Test
			if (m_objects[i]->type == OBJECT_BUILDING)
			{
				if (m_objects[i]->team == 1)
				{
					cout << m_objects[i]->life << endl;
					B_renderer->DrawTexturedRect
					(
						m_objects[i]->x,
						m_objects[i]->y,
						0,
						m_objects[i]->size,
						m_objects[i]->r,
						m_objects[i]->g,
						m_objects[i]->b,
						m_objects[i]->a,
						B_texImage[0],
						0.1
					);
					m_renderer->DrawSolidRectGauge
					(
						m_objects[i]->x,
						m_objects[i]->y+m_objects[i]->size/2,
						0,
						m_objects[i]->size,
						5,
						1,
						0,
						0,
						1,
						(float)m_objects[i]->life/ m_objects[i]->maxLife,
						0.1
					);
				}
				if (m_objects[i]->team == 2)
				{
					B_renderer->DrawTexturedRect
					(
						m_objects[i]->x,
						m_objects[i]->y,
						0,
						m_objects[i]->size,
						m_objects[i]->r,
						m_objects[i]->g,
						m_objects[i]->b,
						m_objects[i]->a,
						B_texImage[1],
						0.1);
					m_renderer->DrawSolidRectGauge
					(
						m_objects[i]->x,
						m_objects[i]->y + m_objects[i]->size/2,
						0,
						m_objects[i]->size,
						5,
						0,
						0,
						1,
						1,
						(float)m_objects[i]->life / m_objects[i]->maxLife,
						0.1
					);
				}
			}
			else if(m_objects[i]->type == OBJECT_CHARACTER)
			{
				if (m_objects[i]->team == 1)
				{
					B_renderer->DrawTexturedRectSeq
					(
						m_objects[i]->x,
						m_objects[i]->y,
						0,
						m_objects[i]->size,
						m_objects[i]->r,
						m_objects[i]->g,
						m_objects[i]->b,
						m_objects[i]->a,
						B_texImage[2],
						m_objects[i]->characterAnmation,
						0,
						10,
						1,
						0.1
					);
					m_renderer->DrawSolidRectGauge
					(
						m_objects[i]->x,
						m_objects[i]->y + m_objects[i]->size + 5,
						0,
						m_objects[i]->size,
						5,
						1,
						0,
						0,
						1,
						(float)m_objects[i]->life / m_objects[i]->maxLife,
						0.1
					);
				}
				else if (m_objects[i]->team == 2)
				{
					B_renderer->DrawTexturedRectSeq
					(
						m_objects[i]->x,
						m_objects[i]->y,
						0,
						m_objects[i]->size,
						m_objects[i]->r,
						m_objects[i]->g,
						m_objects[i]->b,
						m_objects[i]->a,
						B_texImage[3],
						m_objects[i]->characterAnmation,
						0,
						10,
						1,
						0.1
					);
					m_renderer->DrawSolidRectGauge
					(
						m_objects[i]->x,
						m_objects[i]->y + m_objects[i]->size + 5,
						0,
						m_objects[i]->size,
						5,
						0,
						0,
						1,
						1,
						(float)m_objects[i]->life / m_objects[i]->maxLife,
						0.1
					);
				}
			}
			else
			{
				m_renderer->DrawParticle(
					m_objects[i]->x,
					m_objects[i]->y,
					0,
					5,
					1,
					1,
					1,
					1,
					-m_objects[i]->vecx *5,
					-m_objects[i]->vecy *5,
					B_texImage[5],
					m_objects[i]->particleTime
				);
				m_renderer->DrawSolidRect(
					m_objects[i]->x,
					m_objects[i]->y,
					0,
					m_objects[i]->size,
					m_objects[i]->r,
					m_objects[i]->g,
					m_objects[i]->b,
					m_objects[i]->a,
					0.3
				);
			}
		}
	}
}

int SceneMngr::AddCommonObj(float x, float y,int team)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objects[i] == NULL)
		{
			m_objects[i] = new Object(x, y, team, OBJECT_CHARACTER);
			return i;
		}
	}
	return -1;
}

int SceneMngr::AddBuildingObj(int index,int team,int x,int y)
{
	for (int i = 0; i < index; i++)
	{
		if (m_objects[i] == NULL)
		{
			m_objects[i]= new Object(x, y, team, OBJECT_BUILDING);
			return i;
		}
	}
	return -1;
}

int SceneMngr::AddBulletObj(int index)
{
	if (!m_objects[index] == NULL)
	{
		if (m_objects[index]->type == OBJECT_CHARACTER && m_objects[index]->bulletCoolTime >= 1000)
		{
			for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
			{
				if (m_objects[i] == NULL)
				{
					m_objects[i] = new Object(m_objects[index]->x, m_objects[index]->y, m_objects[index]->team, OBJECT_BULLET);
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
		if (m_objects[index]->type == OBJECT_BUILDING && m_objects[index]->arrowCoolTime >= 5000)
		{
			for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
			{
				if (m_objects[i] == NULL)
				{
					m_objects[i] = new Object(m_objects[index]->x, m_objects[index]->y, m_objects[index]->team,OBJECT_ARROW);
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
		int opponentType = -1;
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
					if(!(m_objects[i]->type *m_objects[j]-> type== 12&&
						m_objects[i]->type ==m_objects[j]->type))
					{
						if (!(m_objects[i]->team == m_objects[j]->team))
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
								opponentType = m_objects[j]->type;
								collisionCount++;
							}
						}
					}
				}
			}
			if (collisionCount > 0)
			{
				if (!(m_objects[i]->type == OBJECT_CHARACTER&& opponentType == OBJECT_CHARACTER))
				{
					m_objects[i]->r = 1;
					m_objects[i]->g = 0;
					m_objects[i]->b = 0;
					m_objects[i]->a = 1;
					m_objects[i]->attacked = true;
				}
				DeleteObj();
			}
			else
			{
				if (m_objects[i]->type == OBJECT_CHARACTER)
				{
					if (m_objects[i]->team == 1)
					{
						m_objects[i]->r = 1;
						m_objects[i]->g = 1;
						m_objects[i]->b = 1;
						m_objects[i]->a = 1;
					}
					else if (m_objects[i]->team == 2)
					{
						m_objects[i]->r = 1;
						m_objects[i]->g = 1;
						m_objects[i]->b = 1;
						m_objects[i]->a = 1;
					}
				}
				else if (m_objects[i]->type == OBJECT_BUILDING)
				{
					m_objects[i]->r = 1;
					m_objects[i]->g = 1;
					m_objects[i]->b = 1;
					m_objects[i]->a = 1;
				}
				else if (m_objects[i]->type == OBJECT_BULLET)
				{
					if (m_objects[i]->team == 1)
					{
						m_objects[i]->r = 1;
						m_objects[i]->g = 0;
						m_objects[i]->b = 0;
						m_objects[i]->a = 1;
					}
					else if (m_objects[i]->team == 2)
					{
						m_objects[i]->r = 0;
						m_objects[i]->g = 0;
						m_objects[i]->b = 1;
						m_objects[i]->a = 1;
					}
				}
				else if (m_objects[i]->type == OBJECT_ARROW)
				{
					if (m_objects[i]->team == 1)
					{
						m_objects[i]->r = 0.5;
						m_objects[i]->g = 0.2;
						m_objects[i]->b = 0.7;
						m_objects[i]->a = 1;
					}
					else if (m_objects[i]->team == 2)
					{
						m_objects[i]->r = 1;
						m_objects[i]->g = 1;
						m_objects[i]->b = 0;
						m_objects[i]->a = 1;
					}
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

