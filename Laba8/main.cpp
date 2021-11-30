#include "Data.h"


using namespace std;

float GetSimulationTime() {
	OldSimTik = NewSimTik;
	QueryPerformanceCounter(&NewSimTik);
	return (float(NewSimTik.QuadPart - OldSimTik.QuadPart)) / frequency.QuadPart;
}
void movePlayer(bool left, bool right, bool up, bool down) {
	float* ptrvalue = player->getPosition();
	int posX = int(ceil(ptrvalue[0]));
	int posY = int(ceil(ptrvalue[1]));
	int posZ = int(ceil(ptrvalue[2]));
	
	if (left) {
		char nextPlaceLeft = Array.get()->at(posX + 10).at(posZ + 11);
		if (nextPlaceLeft == '0') {
			player->move(GameObject::MoveDirection::LEFT, 1.0f);
			nextPlaceLeft = Array.get()->at(posX + 10).at(posZ + 11);
		}
		else if (nextPlaceLeft == '1') {

		}

	}
	else if (right) {
		char nextPlaceRight = Array.get()->at(posX + 10).at(posZ + 9);
		if (nextPlaceRight == '0') {
			player->move(GameObject::MoveDirection::RIGHT, 1.0f);
			nextPlaceRight = Array.get()->at(posX + 10).at(posZ + 9);
		}
		else if (nextPlaceRight == '1') {

		}
	}
	else if (up) {
		char nextPlaceUp = Array.get()->at(posX + 9).at(posZ + 10);
		if (nextPlaceUp == '0') {
			player->move(GameObject::MoveDirection::UP, 1.0f);
			nextPlaceUp = Array.get()->at(posX + 9).at(posZ + 10);
		}
		else if (nextPlaceUp == '1') {

		}
	}
	else if (down) {
		char nextPlaceDown = Array.get()->at(posX + 11).at(posZ + 10);
		if (nextPlaceDown == '0') {
			player->move(GameObject::MoveDirection::DOWN, 1.0f);
			nextPlaceDown = Array.get()->at(posX + 11).at(posZ + 10);
		}
		else if (nextPlaceDown == '1') {

		}
		
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
