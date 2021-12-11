#include "Simulation.h"

float GetSimulationTime() {
	OldSimTik = NewSimTik;
	QueryPerformanceCounter(&NewSimTik);
	return (float(NewSimTik.QuadPart - OldSimTik.QuadPart)) / frequency.QuadPart;
}
void movePlayer(bool left, bool right, bool up, bool down) {

	float* ptrvaluePlayer = player->getPosition();
	int posPlayerX = int(ceil(ptrvaluePlayer[0]));
	int posPlayerY = int(ceil(ptrvaluePlayer[1]));
	int posPlayerZ = int(ceil(ptrvaluePlayer[2]));



	bool stateMovement = player->isMoving();

	//cout << stateMovement << endl;
	if (left && !player->isMoving()) {

		if (Array.get()->at(posPlayerX + 10).at(posPlayerZ + 11) == '0') {
			player->move(MoveDirection::LEFT, 1.0f);


		}
		else if (Array.get()->at(posPlayerX + 10).at(posPlayerZ + 11) == '1' && Array.get()->at(posPlayerX + 10).at(posPlayerZ + 12) == '0') {

			player->move(MoveDirection::LEFT, 1.0f);


			mapObjects[posPlayerX + 10][posPlayerZ + 11]->move(MoveDirection::LEFT, 1.0f);

			mapObjects[posPlayerX + 10][posPlayerZ + 12] = mapObjects[posPlayerX + 10][posPlayerZ + 11];
			mapObjects[posPlayerX + 10][posPlayerZ + 11] = nullptr;
			Array.get()->at(posPlayerX + 10).at(posPlayerZ + 11) = '0';
			Array.get()->at(posPlayerX + 10).at(posPlayerZ + 12) = '1';

		}

	}
	else if (right && !player->isMoving()) {
		if (Array.get()->at(posPlayerX + 10).at(posPlayerZ + 9) == '0') {
			player->move(MoveDirection::RIGHT, 1.0f);
		}
		else if (Array.get()->at(posPlayerX + 10).at(posPlayerZ + 9) == '1' && Array.get()->at(posPlayerX + 10).at(posPlayerZ + 8) == '0') {

			player->move(MoveDirection::RIGHT, 1.0f);

			mapObjects[posPlayerX + 10][posPlayerZ + 9]->move(MoveDirection::RIGHT, 1.0f);

			mapObjects[posPlayerX + 10][posPlayerZ + 8] = mapObjects[posPlayerX + 10][posPlayerZ + 9];
			mapObjects[posPlayerX + 10][posPlayerZ + 9] = nullptr;
			Array.get()->at(posPlayerX + 10).at(posPlayerZ + 9) = '0';
			Array.get()->at(posPlayerX + 10).at(posPlayerZ + 8) = '1';

		}
	}
	else if (up && !player->isMoving()) {
		if (Array.get()->at(posPlayerX + 9).at(posPlayerZ + 10) == '0') {
			player->move(MoveDirection::UP, 1.0f);
		}
		else if (Array.get()->at(posPlayerX + 9).at(posPlayerZ + 10) == '1' && Array.get()->at(posPlayerX + 8).at(posPlayerZ + 10) == '0') {

			player->move(MoveDirection::UP, 1.0f);

			mapObjects[posPlayerX + 9][posPlayerZ + 10]->move(MoveDirection::UP, 1.0f);

			mapObjects[posPlayerX + 8][posPlayerZ + 10] = mapObjects[posPlayerX + 9][posPlayerZ + 10];
			mapObjects[posPlayerX + 9][posPlayerZ + 10] = nullptr;
			Array.get()->at(posPlayerX + 9).at(posPlayerZ + 10) = '0';
			Array.get()->at(posPlayerX + 8).at(posPlayerZ + 10) = '1';

		}
	}
	else if (down && !player->isMoving()) {
		if (Array.get()->at(posPlayerX + 11).at(posPlayerZ + 10) == '0') {
			player->move(MoveDirection::DOWN, 1.0f);
		}
		else if (Array.get()->at(posPlayerX + 11).at(posPlayerZ + 10) == '1' && Array.get()->at(posPlayerX + 12).at(posPlayerZ + 10) == '0') {

			player->move(MoveDirection::DOWN, 1.0f);
			mapObjects[posPlayerX + 11][posPlayerZ + 10]->move(MoveDirection::DOWN, 1.0f);

			mapObjects[posPlayerX + 12][posPlayerZ + 10] = mapObjects[posPlayerX + 11][posPlayerZ + 10];
			mapObjects[posPlayerX + 11][posPlayerZ + 10] = nullptr;
			Array.get()->at(posPlayerX + 11).at(posPlayerZ + 10) = '0';
			Array.get()->at(posPlayerX + 12).at(posPlayerZ + 10) = '1';

		}

	}

}
// функция вызывается каждые 20 мс
void Simulation()
{

	// ОПРЕДЕЛЕНИЕ ВРЕМЕНИ ПРОШЕДШЕГО С МОМЕНТА ПОСЛЕДНЕЙ СИМУЛЯЦИИ В СЕКУНДАХ
	float deltaTime = GetSimulationTime();
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
	camera.simulate(deltaTime);

	//перемещение игрока
	bool MoveDirectionUp = GetAsyncKeyState(0x57); //W
	bool MoveDirectionDown = GetAsyncKeyState(0x53);  //S
	bool MoveDirectionLeft = GetAsyncKeyState(0x41);  //A
	bool MoveDirectionRight = GetAsyncKeyState(0x44); //D

	movePlayer(MoveDirectionLeft, MoveDirectionRight, MoveDirectionUp, MoveDirectionDown);
	player->simulate(deltaTime);
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			//свободные клетки пропускаем
			if ((Array.get()->at(i).at(j)) != '0') {
				//объекты
				mapObjects[i][j]->simulate(deltaTime);

			}

		}

	}
	// устанавливаем признак того, что окно нуждается в перерисовке
	// эта же функция будет вызвана еще раз через 20 мс
	glutPostRedisplay();
};