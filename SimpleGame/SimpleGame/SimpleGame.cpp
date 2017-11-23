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
#include <windows.h>
#include "Mmsystem.h"
#pragma comment(lib, "winmm.lib")

using namespace std;
bool left_mouse = false;
bool right_mouse = false;
bool makeAllow = false;
float enemyCoolTime=0.f;
float allowCoolTime = 0.f;

SceneMngr *g_SceneMngr = NULL;

DWORD prevTime = 0.0f;

void makeMap();


void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - prevTime;
	prevTime = currTime;

	enemyCoolTime += elapsedTime;
	if (!makeAllow)
		allowCoolTime += elapsedTime;

	g_SceneMngr->Update((float)elapsedTime);
	g_SceneMngr->DrawAllObj();
	g_SceneMngr->DeleteObj();

	for (int i = 0; i <MAX_OBJECTS_COUNT; i++)
		g_SceneMngr->AddBulletObj(i);
	for(int i =0; i <MAX_OBJECTS_COUNT ; i++)
		g_SceneMngr->AddArrowObj(i);

	if (enemyCoolTime >= 2000)
	{
		for (int i = 0; i < 1; i++)
			g_SceneMngr->AddCommonObj((float)(std::rand() % 500)-250, (float)(std::rand() % 200) + 190, 1);
		enemyCoolTime = 0;
	}
	if (allowCoolTime >= 200)
	{
		makeAllow = true;
	}
	
	// Renderer Test 기본오브젝트
	
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x,int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			left_mouse = true;
		}
	}
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			left_mouse = false;
		}
	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			right_mouse = true;
		}
	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			if (right_mouse&&makeAllow)
			{
				for (int i = 0; i < 1; i++)
					if((-y + 400)<0)
					g_SceneMngr->AddCommonObj(x-250 , -y + 400 , 2);
				allowCoolTime = 0;
				makeAllow = false;
				right_mouse = false;
			}
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
	glutInitWindowSize(500, 800);
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
	g_SceneMngr = new SceneMngr(500, 800);

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);


	prevTime = timeGetTime();

	makeMap();

	glutMainLoop();

	delete g_SceneMngr;

    return 0;
}

void makeMap()
{
	g_SceneMngr->AddBuildingObj(1,1,-200,320);
	g_SceneMngr->AddBuildingObj(2, 1,200,320);
	g_SceneMngr->AddBuildingObj(3,1, 0,320);
	g_SceneMngr->AddBuildingObj(4, 2, -200, -320);
	g_SceneMngr->AddBuildingObj(5, 2, 200, -320);
	g_SceneMngr->AddBuildingObj(6, 2, 0, -320);
}