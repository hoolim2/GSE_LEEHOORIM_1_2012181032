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
bool ch = false;

Renderer *g_Renderer = NULL;
Object b[MAX_OBJECTS_COUNT];
SceneMngr SM;


void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
		//for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
			//g_Renderer->DrawSolidRect(b[i].x, b[i].y, b[i].z, b[i].size, b[i].r, b[i].g, b[i].b, b[i].a);
		for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
			g_Renderer->DrawSolidRect(SM.m_objects[i].x, SM.m_objects[i].y, SM.m_objects[i].z, SM.m_objects[i].size, SM.m_objects[i].r, SM.m_objects[i].g, SM.m_objects[i].b, SM.m_objects[i].a);
		
	if(mousech==true)
		g_Renderer->DrawSolidRect(0,0,0,20,1,1,1,1);
	
	glutSwapBuffers();
}

void Idle(void)
{
	if (ch == true) {
		for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
		{
			SM.m_objects[i].Update();
		}
		SM.Collide();
	}
	
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
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
	
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
		SM.Add(b, i);

	ch = true;
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

