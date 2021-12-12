#include "GraphObject.h"
using namespace std;
// �����������
GraphicObject::GraphicObject(void)
{
}
// ������ ������� �������
void GraphicObject::setPosition(float x, float y, float z)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
	for (int i = 0; i < 3; ++i) {
		modelMatrix[12 + i] = position[i];
	}
}
// ������ ���� �������� � �������� ������������ ��� OY
void GraphicObject::setAngle(float a)
{
	angle = a;
}
// ������ ���� ������
void GraphicObject::set�olor(float r, float g, float b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}
// ������� ������
void GraphicObject::draw(void)
{
	glPushMatrix();
	glMultMatrixf(modelMatrix);
	material->apply();
	mesh->draw();
	glColor3f(color[0], color[1], color[2]);
	glPopMatrix();
}
void GraphicObject::setMaterial(shared_ptr<Material> material1)
{
	material = material1;
}
void GraphicObject::setMesh(shared_ptr<Mesh> mesh1) {
	mesh = mesh1;
}