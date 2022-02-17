#include "model_auto.h"

Model_auto::Model_auto()
{
	Model_auto(DEFAULT_SPEED, DEFAULT_HANDLING, DEFAULT_NAME);
}

Model_auto::Model_auto(int pSpeed, int pHandling, string pName)
{
	speed = pSpeed;
	handling = pHandling;
	name = pName;

	position.x = 0;
	position.y = 0;
	position.angle = 0;
}

Model_auto::~Model_auto()
{
}

void Model_auto::setSpeed(int pSpeed)
{
	speed = pSpeed;
}

int Model_auto::getSpeed()
{
	return speed;
}

void Model_auto::setHandling(int pHandling)
{
	handling = pHandling;
}

int Model_auto::getHandling()
{
	return handling;
}

void Model_auto::setName(string pName)
{
	name = pName;
}

string Model_auto::getName()
{
	return name;
}

void Model_auto::setPostion(Position pPosition)
{
	position.x = pPosition.x;
	position.y = pPosition.y;
}

Position Model_auto::getPosition()
{
	return position;
}


Position Model_auto::move(float pAngle, int pMovement)
{
	Position temp;

	temp.angle = TURNING_RATIO*handling * pAngle + position.angle;
	temp.x = round(sin(pAngle * PI / 180) * pMovement * MOVEMENT_RATIO * speed) + position.x;
	temp.y = round(cos(pAngle * PI / 180) * pMovement * MOVEMENT_RATIO * speed) + position.y;

	return temp;
}
