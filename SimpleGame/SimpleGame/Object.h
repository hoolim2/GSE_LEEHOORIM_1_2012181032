#pragma once
class Object
{

public:
	float x, y, z, size, r, g, b, a,spd,vecx,vecy,life_time;
	int life,type, bulletTime;
	bool colck, shootbullet;
	Object(float x, float y, int def);
	~Object();
	void Update(float elapsedTime);
	float GetObjX();
	float GetObjY();
};

