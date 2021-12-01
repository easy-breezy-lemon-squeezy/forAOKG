#include "Data.h"


using namespace std;

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
	
	if (left) {
		char nextPlaceLeft = Array.get()->at(posPlayerX + 10).at(posPlayerZ + 11);
		if (nextPlaceLeft == '0') {
			nextPlaceLeft = Array.get()->at(posPlayerX + 10).at(posPlayerZ + 11);
			player->move(MoveDirection::LEFT, 1.0f);
			nextPlaceLeft = Array.get()->at(posPlayerX + 10).at(posPlayerZ + 11);
		}
		else if (nextPlaceLeft == '1') {
			char nextNextPlaceLeft = Array.get()->at(posPlayerX + 10).at(posPlayerZ + 12);
			

			if (nextNextPlaceLeft == '0') {
				nextPlaceLeft = Array.get()->at(posPlayerX + 10).at(posPlayerZ + 11);
				cout << nextNextPlaceLeft << endl;
				player->move(MoveDirection::LEFT, 1.0f);
				
				//не двигается жопа
				
				mapObjects[posPlayerX + 10][posPlayerZ + 11]->move(MoveDirection::LEFT, 1.0f);
				
				mapObjects[posPlayerX + 10][posPlayerZ + 12] = mapObjects[posPlayerX + 10][posPlayerZ + 11];
				mapObjects[posPlayerX + 10][posPlayerZ + 11] = nullptr;
				Array.get()->at(posPlayerX + 10).at(posPlayerZ + 11) = '0';
				Array.get()->at(posPlayerX + 10).at(posPlayerZ + 12) = '1';
				nextPlaceLeft = Array.get()->at(posPlayerX + 10).at(posPlayerZ + 11);
			}
			
		}
	}
	else if (right) {
		char nextPlaceRight = Array.get()->at(posPlayerX + 10).at(posPlayerZ + 9);
		if (nextPlaceRight == '0') {
			nextPlaceRight = Array.get()->at(posPlayerX + 10).at(posPlayerZ + 9);
			player->move(MoveDirection::RIGHT, 1.0f);
			nextPlaceRight = Array.get()->at(posPlayerX + 10).at(posPlayerZ + 9);
		}
		else if (nextPlaceRight == '1') {
			char nextNextPlaceRight = Array.get()->at(posPlayerX + 10).at(posPlayerZ + 8);

			if (nextNextPlaceRight == '0') {
				nextPlaceRight = Array.get()->at(posPlayerX + 10).at(posPlayerZ + 9);
			
				player->move(MoveDirection::RIGHT, 1.0f);

				mapObjects[posPlayerX + 10][posPlayerZ + 9]->move(MoveDirection::RIGHT, 1.0f);
				
				mapObjects[posPlayerX + 10][posPlayerZ + 8] = mapObjects[posPlayerX + 10][posPlayerZ + 9];
				mapObjects[posPlayerX + 10][posPlayerZ + 9] = nullptr;
				Array.get()->at(posPlayerX + 10).at(posPlayerZ + 9) = '0';
				Array.get()->at(posPlayerX + 10).at(posPlayerZ + 8) = '1';
				nextPlaceRight = Array.get()->at(posPlayerX + 10).at(posPlayerZ + 9);
			}

		}
	}
	else if (up) {
		char nextPlaceUp = Array.get()->at(posPlayerX + 9).at(posPlayerZ + 10);
		if (nextPlaceUp == '0') {
			nextPlaceUp = Array.get()->at(posPlayerX + 9).at(posPlayerZ + 10);
			player->move(MoveDirection::UP, 1.0f);
			nextPlaceUp = Array.get()->at(posPlayerX + 9).at(posPlayerZ + 10);
		}
		else if (nextPlaceUp == '1') {
			char nextNextPlaceRight = Array.get()->at(posPlayerX + 8).at(posPlayerZ + 10);

			if (nextNextPlaceRight == '0') {
				nextPlaceUp = Array.get()->at(posPlayerX + 9).at(posPlayerZ + 10);

				player->move(MoveDirection::UP, 1.0f);

				mapObjects[posPlayerX + 9][posPlayerZ + 10]->move(MoveDirection::UP, 1.0f);
				
				mapObjects[posPlayerX + 8][posPlayerZ + 10] = mapObjects[posPlayerX + 9][posPlayerZ + 10];
				mapObjects[posPlayerX + 9][posPlayerZ + 10] = nullptr;
				Array.get()->at(posPlayerX + 9).at(posPlayerZ + 10) = '0';
				Array.get()->at(posPlayerX + 8).at(posPlayerZ + 10) = '1';

				nextPlaceUp = Array.get()->at(posPlayerX + 9).at(posPlayerZ + 10);
			}

		}
	}
	else if (down) {
		char nextPlaceDown = Array.get()->at(posPlayerX + 11).at(posPlayerZ + 10);
		if (nextPlaceDown == '0') {
			nextPlaceDown = Array.get()->at(posPlayerX + 11).at(posPlayerZ + 10);
			player->move(MoveDirection::DOWN, 1.0f);
			nextPlaceDown = Array.get()->at(posPlayerX + 11).at(posPlayerZ + 10);
		}
		else if (nextPlaceDown == '1') {
			char nextNextPlaceDown = Array.get()->at(posPlayerX + 12).at(posPlayerZ + 10);

			if (nextNextPlaceDown == '0') {
				nextPlaceDown = Array.get()->at(posPlayerX + 11).at(posPlayerZ + 10);

				player->move(MoveDirection::UP, 1.0f);

				mapObjects[posPlayerX + 12][posPlayerZ + 10] = mapObjects[posPlayerX + 11][posPlayerZ + 10];
				mapObjects[posPlayerX + 11][posPlayerZ + 10] = nullptr;
				Array.get()->at(posPlayerX + 11).at(posPlayerZ + 10) = '0';
				Array.get()->at(posPlayerX + 12).at(posPlayerZ + 10) = '1';
				nextPlaceDown = Array.get()->at(posPlayerX + 11).at(posPlayerZ + 10);
			}

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

// функция, вызываемая при изменении размеров окна
void Reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void Display(void)
{
	// отчищаем буфер цвета
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// устанавливаем общую фоновую освещенность
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor);

	// включаем режим расчета освещения
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// устанавливаем камеру
	camera.apply();
	
	light.setPosition(0, 2, 0);
	light.setDiffuse(0.7, 0.7, 0.7, 1.0);
	light.setAmbient(0.7, 0.7, 0.7, 1.0);
	light.setSpecular(0.7, 0.7, 0.7, 1.0);
	light.apply();
	// выводим объекты
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			//свободные клетки пропускаем
			if ((Array.get()->at(i).at(j)) != '0'){
				//объекты
				mapObjects[i][j]->draw();
				
				//mapObjects[i][j]->move(MoveDirection::LEFT, 1.0f);
			}
		    
		}

	}
	
	player->draw();
	//плоскость
	planeGraphicObject.draw();
	// смена переднего и заднего буферов
	glutSwapBuffers();
};

// Функция обработки нажатия клавиш
void KeyboardFunc(unsigned char key, int x, int y)
{
	
};


int main(int argc, char* argv[]) {
	
	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	// создание окна:
// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);

	// 2. устанавливаем размер окна
	glutInitWindowSize(800, 600);
	// 3. создаем окно
	glutCreateWindow("laba6");
	initGlew();
	initData();
	
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(Display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(Reshape);
	// устанавливаем функцию которая будет вызвана через 20 мс
	glutIdleFunc(Simulation);
	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	glutKeyboardFunc(KeyboardFunc);
	QueryPerformanceCounter(&NewSimTik);
	QueryPerformanceFrequency(&frequency);
	glutMainLoop();
}
