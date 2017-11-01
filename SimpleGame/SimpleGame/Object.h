#pragma once
class Object
{

public:
	float x, y, z, size, r, g, b, a,spd,vecx,vecy,life_time;
	int life;
	bool colck;
	Object(float x, float y);
	~Object();
	void Update(float elapsedTime);
};

