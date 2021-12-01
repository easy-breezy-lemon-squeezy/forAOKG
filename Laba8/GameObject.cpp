#include "GameObject.h"
#include <iostream>

using namespace std;

GameObject::GameObject()
{
	this->progress = 0;
}

void GameObject::setGraphicObject(shared_ptr<GraphicObject> graphcopy) {
	graphic = graphcopy;
}

void GameObject::setPosition(float x, float y, float z) {
	graphic->setPosition(x, y, z);
}

void GameObject::setMesh(shared_ptr<Mesh> mesh) {
	graphic->setMesh(mesh);
}

void GameObject::draw() {
	graphic->draw();
}

float* GameObject::getPosition() {
	return graphic->getPosition();
}


bool GameObject::isMoving()
{
	if (this->state == MoveDirection::STOP)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void GameObject::move(MoveDirection direction, float speed)
{

	this->speed = speed;
	
	switch (direction)
	{
	case MoveDirection::LEFT:
		this->state = MoveDirection::LEFT;
		break;
	case MoveDirection::RIGHT:
		this->state = MoveDirection::RIGHT;
		break;
	case MoveDirection::UP:
		this->state = MoveDirection::UP;
		break;
	case MoveDirection::DOWN:
		this->state = MoveDirection::DOWN;
		break;
	}
}

void GameObject::simulate(float sec)
{
	float* ptrvalue = getPosition();
	float posX = ptrvalue[0];
	float posY = ptrvalue[1];
	float posZ = ptrvalue[2];
	if (this->state == MoveDirection::LEFT)
	{
		if (this->progress < 1.0f)
		{
			this->progress += sec * this->speed;
			//cout << this->progress << endl;
			//cout << posZ << endl;
		
			this->graphic->setPosition(posX, posY, posZ + sec * 2 * this->progress);
		
		}
		if (this->progress >= 1.0f)
		{
			this->state = MoveDirection::STOP;
			this->setPosition(posX, posY, posZ);
			this->progress = 0.0f;
		}
	}
	if (this->state == MoveDirection::RIGHT)
	{
		if (this->progress < 1.0f)
		{
			this->progress += sec * this->speed;
			//cout << this->progress << endl;
			//cout << posZ << endl;

			this->graphic->setPosition(posX, posY, posZ - sec * 2 * this->progress);

		}
		if (this->progress >= 1.0f)
		{
			this->state = MoveDirection::STOP;
			this->setPosition(posX, posY, posZ);
			this->progress = 0.0f;
		}
	}
	if (this->state == MoveDirection::UP)
	{
		if (this->progress < 1.0f)
		{
			this->progress += sec * this->speed;
			//cout << this->progress << endl;
			//cout << posZ << endl;

			this->graphic->setPosition(posX -  sec * 2 * this->progress, posY, posZ);

		}
		if (this->progress >= 1.0f)
		{
			this->state = MoveDirection::STOP;
			this->setPosition(posX, posY, posZ);
			this->progress = 0.0f;
		}
	}
	if (this->state == MoveDirection::DOWN)
	{
		if (this->progress < 1.0f)
		{
			this->progress += sec * this->speed;
			//cout << this->progress << endl;aa
			//cout << posZ << endl;

			this->graphic->setPosition(posX + sec * 2 * this->progress, posY, posZ);

		}
		if (this->progress >= 1.0f)
		{
			this->state = MoveDirection::STOP;
			this->setPosition(posX, posY, posZ);
			this->progress = 0.0f;
		}
	}
}
