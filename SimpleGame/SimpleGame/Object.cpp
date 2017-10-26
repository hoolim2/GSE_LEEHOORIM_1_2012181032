#include "stdafx.h"
#include "Object.h"
#include <cstdlib>
#include "ctime"
#include "iostream"

using namespace std;

Object::Object()
{
	x = 0;
	y = 0;
	z = 0;
	size = 20;
	spd = 1;
	r = 1;
	g = 1;
	b = 1;
	a = 1;
	vecx = 1;
	vecy = -1;
	colck = false;
	life = 10;
	life_time = 6000;
}


void Object::Update(float elapsedTime)
{
	x = x + spd*vecx;
	if (x >= 250)
		vecx = -vecx;
	else if (x< -250)
		vecx = -vecx;
	y = y + spd*vecy;
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