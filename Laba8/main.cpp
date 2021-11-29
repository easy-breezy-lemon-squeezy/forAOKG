#include "Data.h"


using namespace std;

float GetSimulationTime() {
	OldSimTik = NewSimTik;
	QueryPerformanceCounter(&NewSimTik);
	return (float(NewSimTik.QuadPart - OldSimTik.QuadPart)) / frequency.QuadPart;
}
void movePlayer(bool left, bool right, bool up, bool down) {

	if (left) {
		player->move(GameObject::MoveDirection::LEFT, 1.0f);
	}
	else if (right) {
		player->move(GameObject::MoveDirection::RIGHT, 1.0f);
	}
	else if (up) {
		player->move(GameObject::MoveDirection::UP, 1.0f);
	}
	else if (down) {
		player->move(GameObject::MoveDirection::DOWN, 1.0f);
	}
	else {
		player->move(GameObject::MoveDirection::STOP, 1.0f);
	}
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

	//����������� ������
	bool MoveDirectionUp = GetAsyncKeyState(0x57); //W
	bool MoveDirectionDown = GetAsyncKeyState(0x53);  //S
	bool MoveDirectionLeft = GetAsyncKeyState(0x41);  //A
	bool MoveDirectionRight = GetAsyncKeyState(0x44); //D
	movePlayer(MoveDirectionLeft, MoveDirectionRight, MoveDirectionUp, MoveDirectionDown);
	player->simulate(deltaTime);
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
	
	light.setPosition(0, 2, 0);
	light.setDiffuse(0.7, 0.7, 0.7, 1.0);
	light.setAmbient(0.7, 0.7, 0.7, 1.0);
	light.setSpecular(0.7, 0.7, 0.7, 1.0);
	light.apply();
	// ������� �������
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {

			//��������� ������ ����������
			if ((Array.get()->at(i).at(j)) != '0'){
				//�������
				mapObjects[i][j]->draw();
			}
		}
	}
	player->draw();
	//���������
	planeGraphicObject.draw();
	// ����� ��������� � ������� �������
	glutSwapBuffers();
};

// ������� ��������� ������� ������
void KeyboardFunc(unsigned char key, int x, int y)
{
	
};


int main(int argc, char* argv[]) {
	
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
	initGlew();
	initData();
	
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