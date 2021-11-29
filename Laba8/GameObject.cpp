#include "GameObject.h"
#include <iostream>

using namespace std;

GameObject::GameObject(){}

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
		this->progress = 0.0f;
		if (this->progress < 1.0f)
		{
			
			this->progress += 1;
			
			this->graphic->setPosition(posX, posY, posZ + this->progress);
			cout << this->progress << endl;   //от 0 до 1
			cout << posZ << endl;            
			if (this->progress >= 1.0f)
			{
				this->state = MoveDirection::STOP;
				this->setPosition(posX, posY, posZ);
				this->progress = 0.0f;
			}
		}
		
	}
	if (this->state == MoveDirection::RIGHT)
	{
		cout << "RIGHT" << endl;
		if (this->progress < 1.0f)
		{
			this->progress += sec * this->speed;
			this->graphic->setPosition(posX - 10 + this->progress, posZ, posY - 10);
			// std::cout << this->progress << std::endl;
		}
		if (this->progress >= 1.0f)
		{
			this->state = MoveDirection::STOP;
			this->setPosition(posX + 1, posY, 0);
			this->progress = 0.0f;
		}
	}
	if (this->state == MoveDirection::UP)
	{
		cout << "UP" << endl;
		if (this->progress < 1.0f)
		{
			this->progress += sec * this->speed;
			this->graphic->setPosition(posX - 10, 0, posY - 10 - this->progress);
			// std::cout << this->progress << std::endl;
		}
		if (this->progress >= 1.0f)
		{
			this->state = MoveDirection::STOP;
			this->setPosition(posX, posY - 1, posZ);
			this->progress = 0.0f;
		}
	}
	if (this->state == MoveDirection::DOWN)
	{
		cout << "DOWN" << endl;
		if (this->progress < 1.0f)
		{
			this->progress += sec * this->speed;
			this->graphic->setPosition(posX - 10, 0, posY - 10 + this->progress);
			// std::cout << this->progress << std::endl;
		}
		if (this->progress >= 1.0f)
		{
			this->state = MoveDirection::STOP;
			this->setPosition(posX, posY + 1, posZ);
			this->progress = 0.0f;
		}
	}
}
