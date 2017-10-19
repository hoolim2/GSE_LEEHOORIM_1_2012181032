#pragma once
class Object
{

public:
	float x, y, z, size, r, g, b, a,spd,vecx,vecy;
	Object();
	Object(float x, float y, float z, float size, float r, float g, float b, float a, float spd, float vecx1, float vecy1);
	~Object();
	void Update();
};

