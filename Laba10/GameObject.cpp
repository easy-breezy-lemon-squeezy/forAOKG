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
			graphic->setPosition(x - progress, 0, y);
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
void GameObject::setExist(bool value)
{
	this->exist = value;
}
bool GameObject::getExist()
{
	return exist;
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

Monster::Monster() {}

void Monster::setLastStand(int x, int y)
{
	this->lastX = x;
	this->lastY = y;
}

int Monster::getLastStandX() {
	return lastX;
}

int Monster::getLastStandY() {
	return lastY;
}
void Monster::monsterSimulation()
{
	srand(time(NULL));

	if (!this->isMoving())
	{
		if (Array.get()->at(int(this->getX()) + 10).at(int(this->getY()) + 11) != '0' &&
			Array.get()->at(int(this->getX()) + 9).at(int(this->getY()) + 10) != '0' &&
			Array.get()->at(int(this->getX()) + 11).at(int(this->getY()) + 10) != '0') {
			if (RunMap[int(this->getX()) + 10][int(this->getY()) + 9] == 0) {
				RunMap[int(this->getX()) + 10][int(this->getY()) + 9] = 1;
				RunMap[int(this->getX()) + 10][int(this->getY()) + 10] = 0;
				this->move(MoveDirection::UP, 2.0f);
				this->setLastStand(this->getX(), this->getY());
			}
		}
		else
			if (Array.get()->at(int(this->getX()) + 10).at(int(this->getY()) + 9) != '0' &&
				Array.get()->at(int(this->getX()) + 9).at(int(this->getY()) + 10) != '0' &&
				Array.get()->at(int(this->getX()) + 11).at(int(this->getY()) + 10) != '0') {
				if (RunMap[int(this->getX()) + 10][int(this->getY()) + 11] == 0) {
					RunMap[int(this->getX()) + 10][int(this->getY()) + 11] = 1;
					RunMap[int(this->getX()) + 10][int(this->getY()) + 10] = 0;
					this->move(MoveDirection::DOWN, 2.0f);
					this->setLastStand(this->getX(), this->getY());
				}
			}
			else
				if (Array.get()->at(int(this->getX()) + 10).at(int(this->getY()) + 9) != '0' &&
					Array.get()->at(int(this->getX()) + 10).at(int(this->getY()) + 11) != '0' &&
					Array.get()->at(int(this->getX()) + 11).at(int(this->getY()) + 10) != '0') {
					if (RunMap[int(this->getX()) + 9][int(this->getY()) + 10] == 0) {
						RunMap[int(this->getX()) + 9][int(this->getY()) + 10] = 1;
						RunMap[int(this->getX()) + 10][int(this->getY()) + 10] = 0;
						this->move(MoveDirection::LEFT, 2.0f);
						this->setLastStand(this->getX(), this->getY());
					}
				}
				else
					if (Array.get()->at(int(this->getX()) + 10).at(int(this->getY()) + 9) != '0' &&
						Array.get()->at(int(this->getX()) + 10).at(int(this->getY()) + 11) != '0' &&
						Array.get()->at(int(this->getX()) + 9).at(int(this->getY()) + 10) != '0') {
						if (RunMap[int(this->getX()) + 11][int(this->getY()) + 10] == 0) {
							RunMap[int(this->getX()) + 11][int(this->getY()) + 10] = 1;
							RunMap[int(this->getX()) + 10][int(this->getY()) + 10] = 0;
							this->move(MoveDirection::RIGHT, 2.0f);
							this->setLastStand(this->getX(), this->getY());
						}
					}
					else
					{
						if (Array.get()->at(int(this->getX()) + 9).at(int(this->getY()) + 10) != '0' &&
							Array.get()->at(int(this->getX()) + 11).at(int(this->getY()) + 10) != '0')
						{

							if (this->getLastStandX() == this->getX() && this->getLastStandY() == this->getY() + 1)
							{
								if (RunMap[int(this->getX()) + 10][int(this->getY()) + 9] == 0) {
									RunMap[int(this->getX()) + 10][int(this->getY()) + 9] = 1;
									RunMap[int(this->getX()) + 10][int(this->getY()) + 10] = 0;
									this->move(MoveDirection::UP, 2.0f);
									this->setLastStand(this->getX(), this->getY());
								}
								else {
									RunMap[int(this->getX()) + 10][int(this->getY()) + 11] = 1;
									RunMap[int(this->getX()) + 10][int(this->getY()) + 10] = 0;
									this->move(MoveDirection::DOWN, 2.0f);
									this->setLastStand(this->getX(), this->getY());
								}
							}
							else
							{
								if (RunMap[int(this->getX()) + 10][int(this->getY()) + 11] == 0) {
									RunMap[int(this->getX()) + 10][int(this->getY()) + 11] = 1;
									RunMap[int(this->getX()) + 10][int(this->getY()) + 10] = 0;
									this->move(MoveDirection::DOWN, 2.0f);
									this->setLastStand(this->getX(), this->getY());
								}
								else {
									RunMap[int(this->getX()) + 10][int(this->getY()) + 9] = 1;
									RunMap[int(this->getX()) + 10][int(this->getY()) + 10] = 0;
									this->move(MoveDirection::UP, 2.0f);
									this->setLastStand(this->getX(), this->getY());
								}
							}
						}
						else {
							if (Array.get()->at(int(this->getX()) + 10).at(int(this->getY()) + 9) != '0' &&
								Array.get()->at(int(this->getX()) + 10).at(int(this->getY()) + 11) != '0')
							{
								if (this->getLastStandX() == this->getX() + 1 && this->getLastStandY() == this->getY())
								{
									if (RunMap[int(this->getX()) + 9][int(this->getY()) + 10] == 0) {
										RunMap[int(this->getX()) + 9][int(this->getY()) + 10] = 1;
										RunMap[int(this->getX()) + 10][int(this->getY()) + 10] = 0;
										this->move(MoveDirection::LEFT, 2.0f);
										this->setLastStand(this->getX(), this->getY());
									}
									else {
										RunMap[int(this->getX()) + 11][int(this->getY()) + 10] = 1;
										RunMap[int(this->getX()) + 10][int(this->getY()) + 10] = 0;
										this->move(MoveDirection::RIGHT, 2.0f);
										this->setLastStand(this->getX(), this->getY());
									}
								}
								else
								{
									if (RunMap[int(this->getX()) + 11][int(this->getY()) + 10] == 0) {
										RunMap[int(this->getX()) + 11][int(this->getY()) + 10] = 1;
										RunMap[int(this->getX()) + 10][int(this->getY()) + 10] = 0;
										this->move(MoveDirection::RIGHT, 2.0f);
										this->setLastStand(this->getX(), this->getY());
									}
									else {
										RunMap[int(this->getX()) + 9][int(this->getY()) + 10] = 1;
										RunMap[int(this->getX()) + 10][int(this->getY()) + 10] = 0;
										this->move(MoveDirection::LEFT, 2.0f);
										this->setLastStand(this->getX(), this->getY());
									}
								}
							}
							else
							{
								int direction = rand() % 4;

								switch (direction)
								{
								case 0:
									if (Array.get()->at(int(this->getX()) + 11).at(int(this->getY()) + 10) == '0')
									{
										if (!(this->getLastStandX() == this->getX() + 1 && this->getLastStandY() == this->getY()))
										{
											if (RunMap[int(this->getX()) + 11][int(this->getY()) + 10] == 0) {
												RunMap[int(this->getX()) + 11][int(this->getY()) + 10] = 1;
												RunMap[int(this->getX()) + 10][int(this->getY()) + 10] = 0;
												this->move(MoveDirection::RIGHT, 2.0f);
												this->setLastStand(this->getX(), this->getY());
											}
											else {
												RunMap[int(this->getX()) + 9][int(this->getY()) + 10] = 1;
												RunMap[int(this->getX()) + 10][int(this->getY()) + 10] = 0;
												this->move(MoveDirection::LEFT, 2.0f);
												this->setLastStand(this->getX(), this->getY());
											}
										}
									}
									break;
								case 1:
									if (Array.get()->at(int(this->getX()) + 10).at(int(this->getY()) + 11) == '0')
									{
										if (!(this->getLastStandX() == this->getX() && this->getLastStandY() == this->getY() + 1))
										{
											if (RunMap[int(this->getX()) + 10][int(this->getY()) + 11] == 0) {
												RunMap[int(this->getX()) + 10][int(this->getY()) + 11] = 1;
												RunMap[int(this->getX()) + 10][int(this->getY()) + 10] = 0;
												this->move(MoveDirection::DOWN, 2.0f);
												this->setLastStand(this->getX(), this->getY());
											}
											else {
												RunMap[int(this->getX()) + 10][int(this->getY()) + 9] = 1;
												RunMap[int(this->getX()) + 10][int(this->getY()) + 10] = 0;
												this->move(MoveDirection::UP, 2.0f);
												this->setLastStand(this->getX(), this->getY());
											}
										}
									}
									break;
								case 2:
									if (Array.get()->at(int(this->getX()) + 9).at(int(this->getY()) + 10) == '0')
									{
										if (!(this->getLastStandX() == this->getX() - 1 && this->getLastStandY() == this->getY()))
										{
											if (RunMap[int(this->getX()) + 9][int(this->getY()) + 10] == 0) {
												RunMap[int(this->getX()) + 9][int(this->getY()) + 10] = 1;
												RunMap[int(this->getX()) + 10][int(this->getY()) + 10] = 0;
												this->move(MoveDirection::LEFT, 2.0f);
												this->setLastStand(this->getX(), this->getY());
											}
											else {
												RunMap[int(this->getX()) + 11][int(this->getY()) + 10] = 1;
												RunMap[int(this->getX()) + 10][int(this->getY()) + 10] = 0;
												this->move(MoveDirection::RIGHT, 2.0f);
												this->setLastStand(this->getX(), this->getY());
											}
										}
									}
									break;
								case 3:
									if (Array.get()->at(int(this->getX()) + 10).at(int(this->getY()) + 9) == '0')
									{
										if (!(this->getLastStandX() == this->getX() && this->getLastStandY() == this->getY() - 1))
										{
											if (RunMap[int(this->getX()) + 10][int(this->getY()) + 9] == 0) {
												RunMap[int(this->getX()) + 10][int(this->getY()) + 9] = 1;
												RunMap[int(this->getX()) + 10][int(this->getY()) + 10] = 0;
												this->move(MoveDirection::UP, 2.0f);
												this->setLastStand(this->getX(), this->getY());
											}
											else {
												RunMap[int(this->getX()) + 10][int(this->getY()) + 11] = 1;
												RunMap[int(this->getX()) + 10][int(this->getY()) + 10] = 0;
												this->move(MoveDirection::DOWN, 2.0f);
												this->setLastStand(this->getX(), this->getY());
											}
										}
									}
									break;
								}
							}
						}
					}

	}

}