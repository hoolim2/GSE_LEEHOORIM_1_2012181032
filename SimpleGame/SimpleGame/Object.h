#pragma once
class Object
{

public:
	float x, y, z, size, r, g, b, a,spd,vecx,vecy,life_time, arrowCoolTime;
	int life, type, bulletCoolTime, team;
	bool colck, shootbullet;
	Object(float x, float y, int teamNum, int def);
	~Object();
	void Update(float elapsedTime);
	float GetObjX();
	float GetObjY();
};

