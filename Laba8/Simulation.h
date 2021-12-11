#pragma once

#include <Windows.h>
#include <stdio.h>

#include "glew-2.2.0/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "MazeGenerator.h"
#include "Camera.h"
#include "GameObject.h"
#define SIZE 21

extern shared_ptr<vector<vector<char>>> Array;


extern LARGE_INTEGER OldSimTik, NewSimTik, frequency;


extern Camera camera;


extern std::shared_ptr <GameObject> player;
extern std::shared_ptr <GameObject> mapObjects[21][21];
extern enum class MoveDirection;


float GetSimulationTime();
void movePlayer(bool left, bool right, bool up, bool down);
void Simulation();