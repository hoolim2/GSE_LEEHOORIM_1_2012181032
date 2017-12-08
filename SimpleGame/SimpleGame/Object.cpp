#include "stdafx.h"
#include "Object.h"
#include <cstdlib>
#include "ctime"
#include "iostream"

using namespace std;

Object::Object(float objx, float objy, int teamNum, int def)
{
	//Character
	if (def == OBJECT_CHARACTER) {
		if (teamNum == UNIT_ENEMY)
		{
			x = objx;
			y = objy;
			z = 0;
			r = 1;
			g = 1;
			b = 1;
			a = 1;
		}
		else if (teamNum == UNIT_ALLY)
		{
			x = objx;
			y = objy;
			z = 0;
			r = 1;
			g = 1;
			b = 1;
			a = 1;
		}
		size = 50;
		spd = 100;
		vecx = (((float)std::rand() / (float)RAND_MAX) - 0.5f);
		vecy = (((float)std::rand() / (float)RAND_MAX) - 0.5f);
		type = def;
		bulletCoolTime = 0;
		team = teamNum;
		maxLife = 30;
		life = maxLife;
		attacklife = maxLife;
		life_time = 6000;
		attacked = false;
		characterAnmation = 0;
		animateTime = 0;
	}
	//Building
	else if (def == OBJECT_BUILDING)
	{
		x = objx;
		y = objy;
		z = 0;
		size = 100;
		spd = 0;
		r = 1;
		g = 1;
		b = 0;
		a = 1;
		vecx = 0;
		vecy = 0;
		type = def;
		team = teamNum;
		maxLife = 500;
		life = maxLife;
		attacklife = maxLife;
		arrowCoolTime = 0;
		attacked = false;

	}
	//Bullet
	else if (def == OBJECT_BULLET)
	{
		x = objx;
		y = objy;
		z = 0;
		size = 5;
		if (teamNum == UNIT_ENEMY)
		{
			r = 1;
			g = 0.2;
			b = 0.5;
			a = 1;
		}
		else if (teamNum == UNIT_ALLY)
		{
			r = 0.2;
			g = 1;
			b = 0.2;
			a = 1;
		}
		spd = 500;
		vecx = (((float)std::rand() / (float)RAND_MAX) - 0.5f);
		vecy = (((float)std::rand() / (float)RAND_MAX) - 0.5f);
		if (vecy < 0.3&&vecy >0)
			vecy += 0.2;
		if (vecy > -0.3&&vecy <0)
			vecy -= 0.2;
		type = def;
		team = teamNum;
		maxLife = 10;
		life = maxLife;
		attacklife = maxLife;
		attacked = false;
		particleTime = 0;
	}
	//Arrow
	else if (def == OBJECT_ARROW)
	{
		x = objx;
		y = objy;
		z = 0;
		size = 5;
		if (teamNum == UNIT_ENEMY)
		{
			r = 0.5;
			g = 0.2;
			b = 0.7;
			a = 1;
		}
		else if (teamNum == UNIT_ALLY)
		{
			r = 1;
			g = 1;
			b = 0;
			a = 1;
		}
		spd = 500;
		vecx = (((float)std::rand() / (float)RAND_MAX) - 0.5f);
		vecy = (((float)std::rand() / (float)RAND_MAX) - 0.5f);
		if (vecy < 0.3&&vecy >0)
			vecy += 0.2;
		if (vecy > -0.3&&vecy <0)
			vecy -= 0.2;
		type = def;
		team = teamNum;
		maxLife = 20;
		life = maxLife;
		attacklife = maxLife;
		attacked = false;
		particleTime = 0;
	}
}


void Object::Update(float elapsedTime)
{
	float elapsedTimeSecond = elapsedTime / 1000.f;

	x = x + (spd*vecx)*elapsedTimeSecond;
	y = y + (spd*vecy)*elapsedTimeSecond;
	life_time -= elapsedTimeSecond;
	particleTime += elapsedTimeSecond;
	animateTime += elapsedTimeSecond;

	if (attacklife > life)
	{
		attacklife -= elapsedTimeSecond * 10;
	}

	if (type == OBJECT_CHARACTER)
	{
		bulletCoolTime += elapsedTime;
	}
	else if (type == OBJECT_BUILDING)
	{
		arrowCoolTime += elapsedTime;
	}

	if (animateTime > 0.1) {
		characterAnmation++;
		characterAnmation = characterAnmation % 10;
		animateTime = 0;
	}

	if (type == OBJECT_BULLET || type == OBJECT_ARROW)
	{
		if (x >= 350)
		{
			life -= 100000;
		}
		else if (x < -350)
		{
			life -= 100000;
		}
	}
	if (type == OBJECT_CHARACTER)
	{
		if (x >= 200)
		{
			vecx = -vecx;
		}
		else if (x < -200)
		{
			vecx = -vecx;
		}
	}
	if (type == OBJECT_BULLET || type == OBJECT_ARROW)
	{
		if (y >= 500)
		{
			life -= 100000;
		}
		else if (y < -500)
		{
			life -= 100000;
		}
	}
	if (type == OBJECT_CHARACTER)
	{
		if (y >= 350)
		{
			vecx = -vecx;
		}
		else if (y < -350)
		{
			vecx = -vecx;
		}
	}
}

float Object::GetObjX()
{
	return x;
}

float Object::GetObjY()
{
	return y;
}

void Object::DamageCount(int Damage)
{
	life -= Damage;
}

Object::~Object()
{
}