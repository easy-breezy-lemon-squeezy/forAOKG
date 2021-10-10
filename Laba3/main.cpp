#include "GraphObject.h"
#include "Camera.h"
#include <iostream>
using namespace std;
const int graphicObjectCount = 4;
GraphicObject graphicObjects[graphicObjectCount];
LARGE_INTEGER OldSimTik, NewSimTik, frequency;

int matrix1[16] = { -1,0,0,0, 0,1,0,0, 0,0,-1,0, 0,0,0,1 };
int matrix2[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
int matrix3[16] = { 0,0,1,0, 0,1,0,0, -1,0,0,0, 0,0,0,1 };
int matrix4[16] = { 0,0,-1,0, 0,1,0,0, 1,0,0,0, 0,0,0,1 };


Camera camera;

float GetSimulationTime() {
	OldSimTik = NewSimTik;
	QueryPerformanceCounter(&NewSimTik);
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
	bool CameraW = GetAsyncKeyState(0x57);
	bool CameraS = GetAsyncKeyState(0x52);
	camera.setKey(CameraLeft, CameraRight,
		CameraUp, CameraDown,
		CameraForward, CameraBackward,
		CameraW, CameraS);

	camera.simulate(deltaTime);
	// ������������� ������� ����, ��� ���� ��������� � �����������
	glutPostRedisplay();
	// ��� �� ������� ����� ������� ��� ��� ����� 20 ��
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
	// �������� ���� �������
	glEnable(GL_DEPTH_TEST);
	// ������������� ������
	camera.apply();
	// ������� �������
	for (int i = 0; i < graphicObjectCount; i++) {
		graphicObjects[i].draw();
	};
	// ����� ��������� � ������� �������
	glutSwapBuffers();
};

// ������� ��������� ������� ������
void KeyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", (unsigned int)key);
};


int main(int argc, char* argv[]) {
	graphicObjects[0].set�olor(1.0, 0.0, 0.0);
	graphicObjects[0].setPosition(4, 0, 0);
	for (int i = 0; i < 3; ++i) {
		matrix1[12 + i] = graphicObjects[0].position[i];
	}
	for (int i = 0; i < 16; ++i) {
		graphicObjects[0].modelMatrix[i] = matrix1[i];
	}



	graphicObjects[1].set�olor(0.0, 0.0, 1.0);
	graphicObjects[1].setPosition(-4, 0, 0);
	for (int i = 0; i < 3; ++i) {
		matrix2[12 + i] = graphicObjects[1].position[i];
	}
	for (int i = 0; i < 16; ++i) {
		graphicObjects[1].modelMatrix[i] = matrix2[i];
	}


	graphicObjects[2].set�olor(0.0, 1.0, 0.0);
	graphicObjects[2].setPosition(0, 0, -4);
	for (int i = 0; i < 3; ++i) {
		matrix3[12 + i] = graphicObjects[2].position[i];
	}
	for (int i = 0; i < 16; ++i) {
		graphicObjects[2].modelMatrix[i] = matrix3[i];
	}



	graphicObjects[3].set�olor(1.0, 1.0, 1.0);
	graphicObjects[3].setPosition(0, 0, 4);
	for (int i = 0; i < 3; ++i) {
		matrix4[12 + i] = graphicObjects[3].position[i];
	}
	for (int i = 0; i < 16; ++i) {
		graphicObjects[3].modelMatrix[i] = matrix4[i];
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
	glutCreateWindow("laba1");
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
