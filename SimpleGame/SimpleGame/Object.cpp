#include "stdafx.h"
#include "Object.h"
#include <cstdlib>
#include "ctime"
#include "iostream"

using namespace std;

Object::Object(float objx, float objy,int def)
{
	//Character
	if (def == 1) {
		x = objx;
		y = objy;
		z = 0;
		size = 20;
		spd = 1;
		r = 1;
		g = 1;
		b = 1;
		a = 1;
		vecx = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		vecy = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		type = def;
		life = 50;
		life_time = 6000;
	}
	//Building
	else if (def == 2)
	{
		x = 0;
		y = 0;
		z = 0;
		size = 50;
		spd = 0;
		r = 1;
		g = 1;
		b = 0;
		a = 1;
		vecx = 0;
		vecy = 0;
		type = def;
		life = 500;
		bulletTime = 0;
	}
	//Bullet
	else if (def == 3)
	{
		x = 0;
		y = 0;
		z = 0;
		size = 5;
		spd = 5;
		r = 1;
		g = 0;
		b = 0;
		a = 1;
		vecx = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		vecy = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		type = def;
		life = 10;
	}
}


void Object::Update(float elapsedTime)
{
	float elapsedTimeSecond = elapsedTime / 1000.f;
	x = x + (spd*vecx)*elapsedTimeSecond;
	y = y + (spd*vecy)*elapsedTimeSecond;
	if (x >= 250)
		vecx = -vecx;
	else if (x< -250)
		vecx = -vecx;

	if (y >= 250)
		vecy = -vecy;
	else if (y< -250)
		vecy = -vecy;

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