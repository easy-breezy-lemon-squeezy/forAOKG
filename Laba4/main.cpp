#include "GraphObject.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;
const int graphicObjectCount = 4;
GraphicObject graphicObjects[graphicObjectCount];
LARGE_INTEGER OldSimTik, NewSimTik, frequency;

int matrix1[16] = { -1,0,0,0, 0,1,0,0, 0,0,-1,0, 0,0,0,1 };
int matrix2[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
int matrix3[16] = { 0,0,1,0, 0,1,0,0, -1,0,0,0, 0,0,0,1 };
int matrix4[16] = { 0,0,-1,0, 0,1,0,0, 1,0,0,0, 0,0,0,1 };


Camera camera;
Light light;
// ������� ���� ���������� ������ ���������
PhongMaterial material1, material2, material3, material4;

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
	camera.setKey(CameraLeft, CameraRight,
		CameraUp, CameraDown,
		CameraForward, CameraBackward);
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
	// ������������� ����� ������� ������������
	GLfloat globalAmbientColor[] = { 0.8, 0.8, 0.8, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor);

	// �������� ����� ������� ���������
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	// ������������� ������
	camera.apply();

	light.setPosition(500, 200, 200);
	light.setDiffuse(0.5, 0.5, 0.5, 1.0);
	light.setAmbient(0.5, 0.5, 0.5, 1.0);
	light.setSpecular(0.5, 0.5, 0.5, 1.0);
	light.apply();
	/*material.setDiffuse(1.0, 0.0, 0.0, 1.0);
	material.setAmbient(0.4, 0.0, 0.0, 1.0);
	material.setSpecular(1.0, 1.0, 1.0, 1.0);
	material.setEmission(0.0, 0.0, 0.0, 1.0);
	material.setShininess(64.0);*/
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
	shared_ptr<PhongMaterial> material1(new PhongMaterial);
	shared_ptr<PhongMaterial> material2(new PhongMaterial);
	shared_ptr<PhongMaterial> material3(new PhongMaterial);
	shared_ptr<PhongMaterial> material4(new PhongMaterial);
	material1->load("data//materials//material_1.txt");
	material2->load("data//materials//material_2.txt");
	material3->load("data//materials//material_3.txt");
	material4->load("data//materials//material_4.txt");
	graphicObjects[0].set�olor(1.0, 0.0, 0.0);
	graphicObjects[0].setPosition(4, 0, 0);
	for (int i = 0; i < 3; ++i) {
		matrix1[12 + i] = graphicObjects[0].position[i];
	}
	for (int i = 0; i < 16; ++i) {
		graphicObjects[0].modelMatrix[i] = matrix1[i];
	}
	graphicObjects[0].setMaterial(material1);
	graphicObjects[1].set�olor(0.0, 0.0, 1.0);
	graphicObjects[1].setPosition(-4, 0, 0);
	for (int i = 0; i < 3; ++i) {
		matrix2[12 + i] = graphicObjects[1].position[i];
	}
	for (int i = 0; i < 16; ++i) {
		graphicObjects[1].modelMatrix[i] = matrix2[i];
	}
	graphicObjects[1].setMaterial(material2);

	graphicObjects[2].set�olor(0.0, 1.0, 0.0);
	graphicObjects[2].setPosition(0, 0, -4);
	for (int i = 0; i < 3; ++i) {
		matrix3[12 + i] = graphicObjects[2].position[i];
	}
	for (int i = 0; i < 16; ++i) {
		graphicObjects[2].modelMatrix[i] = matrix3[i];
	}
	graphicObjects[2].setMaterial(material3);


	graphicObjects[3].set�olor(1.0, 1.0, 1.0);
	graphicObjects[3].setPosition(0, 0, 4);
	for (int i = 0; i < 3; ++i) {
		matrix4[12 + i] = graphicObjects[3].position[i];
	}
	for (int i = 0; i < 16; ++i) {
		graphicObjects[3].modelMatrix[i] = matrix4[i];
	}
	graphicObjects[3].setMaterial(material4);
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
