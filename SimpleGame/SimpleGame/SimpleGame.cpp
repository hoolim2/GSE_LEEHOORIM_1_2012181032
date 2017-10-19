/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "Object.h"
#include <cstdlib>
#include "ctime"
#include "SceneMngr.h"

#define MAX_OBJECTS_COUNT 50

bool mousech = true;

Renderer *g_Renderer = NULL;
Object a(0,0,0,10,1,1,1,1,5,0.7,1);
Object *b[50];
SceneMngr SM;


void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
		g_Renderer->DrawSolidRect(a.x, a.y, a.z, a.size, a.r, a.g, a.b, a.a);
		for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
			g_Renderer->DrawSolidRect(b[i]->x, b[i]->y, b[i]->z, b[i]->size, b[i]->r, b[i]->g, b[i]->b, b[i]->a);
		a.Update();
	if(mousech==true)
		g_Renderer->DrawSolidRect(0,0,0,20,1,1,1,1);
	
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			//a.x = x-250;
			//a.y = -y+250;

			//a.vecx = a.vecx*-1;
			//a.vecy = a.vecy*-1;

			if (mousech)
				mousech = false;
			else if (!mousech)
				mousech = true;
		}
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		//Object *m_objects[i] = new Object(rand() % 250, rand() % 250, 0, 10, 0, 0, 0, 0, 1, 1, 1) ;
		b[i]->x = rand() % 500 - 250;
		b[i]->y = rand() % 500 - 250;
	}

	SM.Add(b);
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;

    return 0;
}

