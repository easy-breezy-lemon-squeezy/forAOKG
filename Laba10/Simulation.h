#pragma once
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include "Camera.h"
#include "GameObject.h"

extern LARGE_INTEGER OldSimTik, NewSimTik, frequency, newTick, oldTick;
extern int passabilityMap[21][21];
extern Camera camera;
extern shared_ptr <GameObject> player;
extern shared_ptr <GameObject> mapObjects[21][21];
extern shared_ptr <Monster> enemy[3];
extern shared_ptr<vector<vector<char>>> Array;
extern enum class MoveDirection;
extern int real;
extern bool showPlayer;

float GetSimulationTime();

void cameraSimulation(float simulationTime);

void gameObjectSimulation(float simulationTime);

void movePlayer();

void simulation();