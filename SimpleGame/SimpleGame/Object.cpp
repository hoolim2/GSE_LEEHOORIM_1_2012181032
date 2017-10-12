#include "stdafx.h"
#include "Object.h"

Object::Object(float x1, float y1, float z1, float size1, float r1, float g1, float b1, float a1,float spd1,float vecx1, float vecy1)
{
	x = x1;
	y = y1;
	z = z1;
	size = size1;
	spd = spd1;
	r = r1;
	g = g1;
	b = b1;
	a = a1;
	vecx = vecx1;
	vecy = vecy1;
}

void Object::Update()
{
	x = x + spd*vecx;
	if (x >= 250)
		vecx = -1;
	else if (x< -250)
		vecx = 1;
	y = y + spd*vecy;
	if (y >= 250)
		vecy = -1;
	else if (y< -250)
		vecy = 1;
}

Object::~Object()
{
}