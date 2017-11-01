#include "stdafx.h"
#include "Object.h"
#include <cstdlib>
#include "ctime"
#include "iostream"

using namespace std;

Object::Object(float mouse_x, float mouse_y)
{
	x = mouse_x;
	y = mouse_y;
	z = 0;
	size = 20;
	spd = 1;
	r = 1;
	g = 1;
	b = 1;
	a = 1;
	vecx = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
	vecy = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
	colck = false;
	life = 10;
	life_time = 6000;
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

	if (colck)
	{
		r = 1;
		g = 0;
		b = 0;
		life--;
	}
	else if(!colck)
	{
		r = 1;
		g = 1;
		b = 1;
	}
	if (life == 0)
	{
		cout << "is dead" << endl;
	}
	if(life_time ==0)
	{
		cout << "is dead" << endl;
	}
}

Object::~Object()
{
}