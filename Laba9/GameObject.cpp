#include "GameObject.h"

using namespace std;

GameObject::GameObject() {}

void GameObject::setGraphicObject(shared_ptr<GraphicObject> graphcopy) {
	graphic = graphcopy;
	state = MoveDirection::STOP;
}

void GameObject::setPosition(float x, float y, float z) {
	this->x = x;
	this->y = z;
	graphic->setPosition(x, y, z);
}

void GameObject::setMesh(shared_ptr<Mesh> mesh) {
	graphic->setMesh(mesh);
}

void GameObject::draw() {
	graphic->draw();
}

float GameObject::getX() {
	return x;
}

float GameObject::getY() {
	return y;
}

void GameObject::simulate(float sec)
{
	if (state == MoveDirection::LEFT)
	{

		if (progress < 1.0f)
		{
			progress += sec * speed;
			graphic->setPosition(x - progress,  0, y );
		}
		if (progress >= 1.0f)
		{
			state = MoveDirection::STOP;
			setPosition(x - 1, 0, y);
			progress = 0.0f;
		}
	}
	if (state == MoveDirection::RIGHT)
	{
		if (progress < 1.0f)
		{
			progress += sec * speed;
			graphic->setPosition(x + progress, 0, y);
		}
		if (progress >= 1.0f)
		{
			state = MoveDirection::STOP;
			setPosition(x + 1, 0, y);
			progress = 0.0f;
		}
	}
	if (state == MoveDirection::UP)
	{
		if (progress < 1.0f)
		{
			progress += sec * speed;
			graphic->setPosition(x, 0, y - progress);
		}
		if (progress >= 1.0f)
		{
			state = MoveDirection::STOP;
			setPosition(x, 0, y - 1);
			progress = 0.0f;
		}
	}
	if (state == MoveDirection::DOWN)
	{
		if (progress < 1.0f)
		{
			progress += sec * speed;
			graphic->setPosition(x, 0, y + progress);
		}
		if (progress >= 1.0f)
		{
			state = MoveDirection::STOP;
			setPosition(x, 0, y + 1);
			progress = 0.0f;
		}
	}
}

bool GameObject::isMoving()
{
	if (state == MoveDirection::STOP)
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
		state = MoveDirection::LEFT;
		break;
	case MoveDirection::RIGHT:
		state = MoveDirection::RIGHT;
		break;
	case MoveDirection::UP:
		state = MoveDirection::UP;
		break;
	case MoveDirection::DOWN:
		state = MoveDirection::DOWN;
		break;
	}
}
