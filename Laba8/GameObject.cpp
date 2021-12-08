#include "GameObject.h"
#include <iostream>

using namespace std;
float initPos = 0;

GameObject::GameObject()
{
	this->progress = 0;
	this->state == MoveDirection::STOP;
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
	/*if (this->state == MoveDirection::STOP) {
		cout << "STOP" << endl;
	}*/
	float* ptrvalue = getPosition();
	float posX = ptrvalue[0];
	float posY = ptrvalue[1];
	float posZ = ptrvalue[2];

	if (this->state == MoveDirection::LEFT)
	{
		
		if (this->progress < 1.0f)
		{
			this->progress += sec * this->speed;
			this->graphic->setPosition(posX, posY, posZ);
		}
		else if (this->progress >= 1.0f)
		{

			this->state = MoveDirection::STOP;

			if (this->state == MoveDirection::STOP)
			{
				cout << "STOP" << endl;
			}
			//this->setPosition(posX, posY, posZ + 1);
			this->setPosition(posX, posY, posZ - initPos + 1);
			initPos = 0;
			this->progress = 0.0f;
		}
	}
	if (this->state == MoveDirection::RIGHT)
	{
		if (this->progress < 1.0f)
		{
			this->progress += sec * this->speed;

			initPos = initPos + (sec * 2 * this->progress);
			this->graphic->setPosition(posX, posY, posZ);

		}
		else if (this->progress >= 1.0f)
		{
			this->state = MoveDirection::STOP;
			this->setPosition(posX, posY, posZ - 1);
			initPos = 0;
			this->progress = 0.0f;
		}
	}
	if (this->state == MoveDirection::UP)
	{
		if (this->progress < 1.0f)
		{
			this->progress += sec * this->speed;
			this->graphic->setPosition(posX, posY, posZ);
		}
		else if (this->progress >= 1.0f)
		{
			this->state = MoveDirection::STOP;
			this->setPosition(posX - 1, posY, posZ);
			initPos = 0;
			this->progress = 0.0f;
		}
	}
	if (this->state == MoveDirection::DOWN)
	{
		if (this->progress < 1.0f)
		{
			this->progress += sec * this->speed;
			this->graphic->setPosition(posX, posY, posZ);
		}
		else if (this->progress >= 1.0f)
		{
			this->state = MoveDirection::STOP;
			this->setPosition(posX + 1, posY, posZ);
			initPos = 0;
			this->progress = 0.0f;
		}
	}

}