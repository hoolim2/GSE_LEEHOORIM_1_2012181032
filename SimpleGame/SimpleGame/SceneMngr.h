#pragma once
#include "Renderer.h"
#include "Object.h"

#define MAX_OBJECTS_COUNT 50

class SceneMngr
{
public:
	SceneMngr(int width, int height);
	~SceneMngr();
	
	Object *m_objects[MAX_OBJECTS_COUNT];

	Renderer *m_renderer;

	int Add(float x, float y);
	void DrawObj();
	void Collide();
	void Update(float elapsedTime);

private:
	int m_windowWidth;
	int m_windowHeight;
};
