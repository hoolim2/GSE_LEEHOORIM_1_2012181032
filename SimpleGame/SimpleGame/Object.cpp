#include "stdafx.h"
#include "Object.h"
#include <cstdlib>
#include "ctime"
#include "iostream"

using namespace std;

Object::Object(float objx, float objy,int teamNum,int def)
{
	//Character
	if (def == OBJECT_CHARACTER) {
		if (teamNum == 1)
		{
			x = objx;
			y = objy;
			z = 0;
			r = 1;
			g = 1;
			b = 1;
			a = 1;
		}
		else if (teamNum == 2)
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
		maxLife = 10;
		life = maxLife;
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
		if (teamNum == 1)
		{
			r = 1;
			g = 0;
			b = 0;
			a = 1;
		}
		else if (teamNum == 2)
		{
			r = 0;
			g = 0;
			b = 1;
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
		if (teamNum == 1)
		{
			r = 0.5;
			g = 0.2;
			b = 0.7;
			a = 1;
		}
		else if (teamNum == 2)
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
		maxLife = 10;
		life = maxLife;
		attacked = false;
		particleTime = 0;
	}
}


void Object::Update(float elapsedTime)
{
	float elapsedTimeSecond = elapsedTime / 1000.f;
	x = x + (spd*vecx)*elapsedTimeSecond;
	y = y + (spd*vecy)*elapsedTimeSecond;
	if (type == 1)
	{
		bulletCoolTime += elapsedTime;
	}
	else if (type == 2)
	{
		arrowCoolTime += elapsedTime;
	}
	if (attacked)
	{
		life -= 10;
		attacked = false;
	}
	particleTime+= elapsedTimeSecond;
	animateTime += elapsedTimeSecond;
	if (animateTime > 0.1) {
		characterAnmation++;
		characterAnmation = characterAnmation % 10;
		animateTime = 0;
	}

	if (type == 3 || type == 4)
	{
		if (x >= 250)
		{
			life -= 100;
		}
		else if (x < -250)
		{
			life -= 100;
		}
	}
	if (type == 1)
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

	if (y >= 400)
	{
		if (type == 3 || type == 4)
			life -= 100;
		vecy = -vecy;
	}
	else if (y < -400)
	{
		if (type == 3 || type == 4)
			life -= 100;
		vecy = -vecy;
	}

	if (life <= 0)
	{
		cout << "is dead" << endl;
	}
	if(life_time ==0)
	{
		cout << "is dead" << endl;
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

Object::~Object()
{
}