#pragma once
class SceneMngr
{
public:
	SceneMngr();
	~SceneMngr();

	void Add();
	void Update();

	Object *m_objects[50];
};

