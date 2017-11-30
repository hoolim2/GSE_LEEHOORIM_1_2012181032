#pragma once
#include "Renderer.h"
#include "Object.h"
class SceneMngr
{
public:
	SceneMngr(int width, int height);
	~SceneMngr();
	
	Object *m_objects[MAX_OBJECTS_COUNT];

	Renderer *m_renderer;
	Renderer *B_renderer;

	int AddCommonObj(float x, float y, int team);
	int AddBulletObj(int index);
	int AddBuildingObj(int index , int team, int x, int y);
	int AddArrowObj(int index);
	void makeMap();
	void DrawAllObj();
	void CollideCheck();
	void DeleteObj();
	void Update(float elapsedTime);

	bool BoxCollisionTest(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1);

private:
	int m_windowWidth;
	int m_windowHeight;
	int B_texImage[4];
};
