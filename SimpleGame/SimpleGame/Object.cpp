#include "stdafx.h"
#include "Object.h"

Object::Object(float dfg, float y1, float z1, float size1, float r1, float g1, float b1, float a1)
{
	x = dfg;
	y = y1;
	z = z1;
	size = size1;
	r = r1;
	g = g1;
	b = b1;
	a = a1;
}


Object::~Object()
{
}
