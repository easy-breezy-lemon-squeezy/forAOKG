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

// ������� ���������� ������ 20 ��
void Simulation()
{
	// ����������� ������� ���������� � ������� ��������� ��������� � ��������
	float deltaTime = GetSimulationTime();
	// ����������� ������
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
	// ������������� ������� ����, ��� ���� ��������� � �����������
	// ��� �� ������� ����� ������� ��� ��� ����� 20 ��
	glutPostRedisplay();
};

// �������, ���������� ��� ��������� �������� ����
void Reshape(int w, int h)
{
	// ���������� ����� ������� ���������, ������ ���� ������� ����
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// ���������� ������� �������� � ���������� ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� �������� glutPostRedisplay
void Display(void)
{
	// �������� ����� �����
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ������������� ����� ������� ������������
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor);

	// �������� ����� ������� ���������
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// ������������� ������
	camera.apply();
	
	light.setPosition(0, 10, 0);
	light.setDiffuse(0.2, 0.2, 0.2, 1.0);
	light.setAmbient(0.7, 0.7, 0.7, 1.0);
	light.setSpecular(0.2, 0.2, 0.2, 1.0);
	light.apply();
	// ������� �������
	for (int i = 0; i < 21; ++i) {
		for (int j = 0; j < 21; ++j) {
			//��������� ������ ����������
			if (passabilityMap[i][j] != 0) {
				//�������
				mapObjects[i][j].draw();
				//���������
				planeGraphicObject.draw();
			}
		}
	}
	// ����� ��������� � ������� �������
	glutSwapBuffers();
};

// ������� ��������� ������� ������
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
	// ������������� ���������� GLUT
	glutInit(&argc, argv);
	// ������������� ������� (������ ������)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	// �������� ����:
// 1. ������������� ������� ����� ���� ����
	glutInitWindowPosition(200, 200);
	// 2. ������������� ������ ����
	glutInitWindowSize(800, 600);
	// 3. ������� ����
	glutCreateWindow("laba6");
	// ������������� �������, ������� ����� ���������� ��� ����������� ����
	glutDisplayFunc(Display);
	// ������������� �������, ������� ����� ���������� ��� ��������� �������� ����
	glutReshapeFunc(Reshape);
	// ������������� ������� ������� ����� ������� ����� 20 ��
	glutIdleFunc(Simulation);
	// ������������� �������, ������� ����� ���������� ��� ������� �� �������
	glutKeyboardFunc(KeyboardFunc);
	QueryPerformanceCounter(&NewSimTik);
	QueryPerformanceFrequency(&frequency);
	glutMainLoop();
}
