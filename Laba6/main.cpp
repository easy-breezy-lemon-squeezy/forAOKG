#include "Data.h"
#include <iostream>
using namespace std;

float GetSimulationTime() {
	OldSimTik = NewSimTik;
	QueryPerformanceCounter(&NewSimTik);
	static int fps = 0;
	static float time = 0;
	time += float(NewSimTik.QuadPart - OldSimTik.QuadPart);
	fps++;
	if (time > 1000000) {
		cout << fps << endl;
		fps = 0;
		time -= 1000000;
	}
	//cout << float(NewSimTik.QuadPart - OldSimTik.QuadPart) << endl;
	return (float(NewSimTik.QuadPart - OldSimTik.QuadPart)) / frequency.QuadPart;
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
	
	light.setPosition(0, 10, 0);
	light.setDiffuse(0.2, 0.2, 0.2, 1.0);
	light.setAmbient(0.7, 0.7, 0.7, 1.0);
	light.setSpecular(0.2, 0.2, 0.2, 1.0);
	light.apply();
	// выводим объекты
	for (int i = 0; i < 21; ++i) {
		for (int j = 0; j < 21; ++j) {
			//свободные клетки пропускаем
			if (passabilityMap[i][j] != 0) {
				//объекты
				mapObjects[i][j].draw();
				//плоскость
				planeGraphicObject.draw();
			}
		}
	}
	// смена переднего и заднего буферов
	glutSwapBuffers();
};

// Функция обработки нажатия клавиш
void KeyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", (unsigned int)key);
};


int main(int argc, char* argv[]) {
	
	materials.emplace_back(new PhongMaterial);
	materials.emplace_back(new PhongMaterial);
	materials.emplace_back(new PhongMaterial);
	materials.emplace_back(new PhongMaterial);

	mesh.emplace_back(new Mesh);
	mesh.emplace_back(new Mesh);
	mesh.emplace_back(new Mesh);
	mesh.emplace_back(new Mesh);

	mesh.at(0)->load("data//meshes//Box.obj");
	mesh.at(1)->load("data//meshes//ChamferBox.obj");
	mesh.at(2)->load("data//meshes//SimplePlane.obj");
	mesh.at(3)->load("data//meshes//Sphere.obj");
	
	materials.at(0)->load("data//materials//material_1.txt");
	materials.at(1)->load("data//materials//material_2.txt");
	materials.at(2)->load("data//materials//material_3.txt");
	materials.at(3)->load("data//materials//material_4.txt");

	planeGraphicObject.setMesh(mesh.at(2));
	planeGraphicObject.setMaterial(materials.at(0));
	planeGraphicObject.setPosition(0.0, -0.5, 0.0);
	graph3.setMesh(mesh.at(0));
	graph3.setMaterial(materials.at(3));
	graph1.setMesh(mesh.at(0));
	graph1.setMaterial(materials.at(1));
	graph2.setMesh(mesh.at(1));
	graph2.setMaterial(materials.at(2));

	for (int i = 0; i < 21; ++i) {
		for (int j = 0; j < 21; ++j) {
			if (passabilityMap[i][j] == 3) {
				mapObjects[i][j].setGraphicObject(graph3);
				mapObjects[i][j].setPosition(i - 10, 0, j - 10);
			}
			if (passabilityMap[i][j] == 1) {
				mapObjects[i][j].setGraphicObject(graph1);
				mapObjects[i][j].setPosition(i - 10, 0, j - 10);
			}
			if (passabilityMap[i][j] == 2) {
				mapObjects[i][j].setGraphicObject(graph2);
				mapObjects[i][j].setPosition(i - 10, 0, j - 10);
			}
		}
	}
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
