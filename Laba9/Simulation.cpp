#include "Simulation.h"

float GetSimulationTime() {
	OldSimTik = NewSimTik;
	QueryPerformanceCounter(&NewSimTik);
	return (float(NewSimTik.QuadPart - OldSimTik.QuadPart)) / frequency.QuadPart;
}

void cameraSimulation(float simulationTime) {
	// ПЕРЕМЕЩЕНИЕ КАМЕРЫ
	bool CameraLeft = GetAsyncKeyState(VK_LEFT);
	bool CameraRight = GetAsyncKeyState(VK_RIGHT);
	bool CameraUp = GetAsyncKeyState(VK_UP);
	bool CameraDown = GetAsyncKeyState(VK_DOWN);
	bool CameraForward = GetAsyncKeyState(VK_ADD);
	bool CameraBackward = GetAsyncKeyState(VK_SUBTRACT);
	camera.setKey(CameraLeft, CameraRight,
		CameraUp, CameraDown,
		CameraForward, CameraBackward);
	camera.simulate(simulationTime);
}

void gameObjectSimulation(float simulationTime) {
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (mapObjects[i][j] != nullptr)
			{
				mapObjects[i][j]->simulate(simulationTime);
			}
		}
	}
	player->simulate(simulationTime);
	/*if (showPlayer)
	{
		player->simulate(simulationTime);
	}

	for (int i = 0; i < 3; i++)
	{
		enemy[i].get()->simulate(simulationTime);

		if (enemy[i].get()->getX() == player.get()->getX() && enemy[i].get()->getY() == player.get()->getY())
		{
			showPlayer = false;
		}
	}*/
	

	for (int i = 0; i < 3; i++)
	{
		enemy[i]->simulate(simulationTime);
	}
}

void movePlayer()
{
	// ПЕРЕМЕЩЕНИЕ ИГРОКА
	bool PlayerLeft = GetAsyncKeyState(65);
	bool PlayerRight = GetAsyncKeyState(68);
	bool PlayerUp = GetAsyncKeyState(87);
	bool PlayerDown = GetAsyncKeyState(83);
	// СКОРОСТЬ ИГРОКА
	float currentSpeed = 5.0f;
	if (PlayerLeft && !player->isMoving() && Array.get()->at(int(player->getX()) + 9).at(int(player->getY()) + 10) == '0'){
		player->move(MoveDirection::LEFT, currentSpeed);
	}
	else if (PlayerLeft && !player->isMoving() && Array.get()->at(int(player->getX()) + 9).at(int(player->getY()) + 10) == '1'
		&& Array.get()->at(int(player->getX()) + 8).at(int(player->getY()) + 10) == '0'){
		player->move(MoveDirection::LEFT, currentSpeed);
		mapObjects[int(player->getX()) + 9][int(player->getY()) + 10]->move(MoveDirection::LEFT, currentSpeed);
		mapObjects[int(player->getX()) + 8][int(player->getY()) + 10] = mapObjects[int(player->getX()) + 9][int(player->getY()) + 10];
		mapObjects[int(player->getX()) + 9][int(player->getY()) + 10] = nullptr;
		Array.get()->at(int(player->getX()) + 9).at(int(player->getY()) + 10) = '0';
		Array.get()->at(int(player->getX()) + 8).at(int(player->getY()) + 10) = '1';
	}
	
	if (PlayerRight && !player->isMoving() && Array.get()->at(int(player->getX()) + 11).at(int(player->getY()) + 10) == '0') {
		player->move(MoveDirection::RIGHT, currentSpeed);
	}
	else if (PlayerRight && !player->isMoving() && Array.get()->at(int(player->getX()) + 11).at(int(player->getY()) + 10) == '1'
		&& Array.get()->at(int(player->getX()) + 12).at(int(player->getY()) + 10) == '0') {
		player->move(MoveDirection::RIGHT, currentSpeed);
		mapObjects[int(player->getX()) + 11][int(player->getY()) + 10]->move(MoveDirection::RIGHT, currentSpeed);
		mapObjects[int(player->getX()) + 12][int(player->getY()) + 10] = mapObjects[int(player->getX()) + 11][int(player->getY()) + 10];
		mapObjects[int(player->getX()) + 11][int(player->getY()) + 10] = nullptr;
		Array.get()->at(int(player->getX()) + 11).at(int(player->getY()) + 10) = '0';
		Array.get()->at(int(player->getX()) + 12).at(int(player->getY()) + 10) = '1';
	}

	if (PlayerUp && !player->isMoving() && Array.get()->at(int(player->getX()) + 10).at(int(player->getY()) + 9) == '0') {
		player->move(MoveDirection::UP, currentSpeed);
	}
	else if (PlayerUp && !player->isMoving() && Array.get()->at(int(player->getX()) + 10).at(int(player->getY()) + 9) == '1'
		&& Array.get()->at(int(player->getX()) + 10).at(int(player->getY()) + 8) == '0') {
		player->move(MoveDirection::UP, currentSpeed);
		mapObjects[int(player->getX()) + 10][int(player->getY()) + 9]->move(MoveDirection::UP, currentSpeed);
		mapObjects[int(player->getX()) + 10][int(player->getY()) + 8] = mapObjects[int(player->getX()) + 10][int(player->getY()) + 9];
		mapObjects[int(player->getX()) + 10][int(player->getY()) + 9] = nullptr;
		Array.get()->at(int(player->getX()) + 10).at(int(player->getY()) + 9) = '0';
		Array.get()->at(int(player->getX()) + 10).at(int(player->getY()) + 8) = '1';
	}
	if (PlayerDown && !player->isMoving() && Array.get()->at(int(player->getX()) + 10).at(int(player->getY()) + 11) == '0') {
		player->move(MoveDirection::DOWN, currentSpeed);
	}
	else if (PlayerDown && !player->isMoving() && Array.get()->at(int(player->getX()) + 10).at(int(player->getY()) + 11) == '1'
		&& Array.get()->at(int(player->getX()) + 10).at(int(player->getY()) + 12) == '0') {
		player->move(MoveDirection::DOWN, currentSpeed);
		mapObjects[int(player->getX()) + 10][int(player->getY()) + 11]->move(MoveDirection::DOWN, currentSpeed);
		mapObjects[int(player->getX()) + 10][int(player->getY()) + 12] = mapObjects[int(player->getX()) + 10][int(player->getY()) + 11];
		mapObjects[int(player->getX()) + 10][int(player->getY()) + 11] = nullptr;
		Array.get()->at(int(player->getX()) + 10).at(int(player->getY()) + 11) = '0';
		Array.get()->at(int(player->getX()) + 10).at(int(player->getY()) + 12) = '1';
	}
}

void simulation() {
	// ОПРЕДЕЛЕНИЕ ВРЕМЕНИ ПРОШЕДШЕГО С МОМЕНТА ПОСЛЕДНЕЙ СИМУЛЯЦИИ В СЕКУНДАХ
	float deltaTime = GetSimulationTime();

	// симуляция камеры
	cameraSimulation(deltaTime);

	// симуляция всех игровых объектов (их плавное перемещение)
	gameObjectSimulation(deltaTime);

	// перемещение главного героя
	movePlayer();
	
	// симуляция монстров
	for (int i = 0; i < 3; i++)
	{
		enemy[i].get()->monsterSimulation();
	}
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
}