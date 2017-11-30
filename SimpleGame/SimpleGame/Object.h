#pragma once
class Object
{

public:
	float x, y, z, size, r, g, b, a,spd,vecx,vecy,life_time, arrowCoolTime, animateTime, particleTime, attacklife;
	int life, maxLife, type, bulletCoolTime, team, characterAnmation;
	bool attacked;
	Object(float x, float y, int teamNum, int def);
	~Object();
	void Update(float elapsedTime);
	float GetObjX();
	float GetObjY();
	void DamageCount(int Damage);
};

