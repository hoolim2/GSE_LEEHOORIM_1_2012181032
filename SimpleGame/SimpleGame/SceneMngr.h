#pragma once
#include "Renderer.h"
#include "Object.h"

#define OBJECT_CHARACTER 0
#define OBJECT_BUILDING 1
#define OBJECT_BULLET 2
#define OBJECT_ARROW 3
#define MAX_OBJECTS_COUNT 200
class SceneMngr
{
public:
	SceneMngr(int width, int height);
	~SceneMngr();
	
	Object *m_objects[MAX_OBJECTS_COUNT];

	Renderer *m_renderer;

	int AddCommonObj(float x, float y);
	int AddBulletObj();
	int AddBuildingObj(int index);
	void DeleteObj(int index);
	void DrawAllObj();
	void CollideCheck();
	void Update(float elapsedTime);

	bool BoxCollisionTest(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1);

private:
	int m_windowWidth;
	int m_windowHeight;
};
