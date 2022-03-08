#include "model_auto.h"


ModelAuto::ModelAuto() : ModelAuto(DEFAULT_SPEED, DEFAULT_HANDLING, DEFAULT_NAME) {

}


ModelAuto::ModelAuto(int pSpeed, int pHandling, std::string pName)
{
	speed = pSpeed;
	handling = pHandling;
	name = pName;

	position.x = 0;
	position.y = 0;
	position.angle = 0;
}

ModelAuto::~ModelAuto()
{
}

void ModelAuto::setSpeed(int pSpeed)
{
	speed = pSpeed;
}

int ModelAuto::getSpeed()
{
	return speed;
}

void ModelAuto::setHandling(int pHandling)
{
	handling = pHandling;
}

int ModelAuto::getHandling()
{
	return handling;
}

void ModelAuto::setName(std::string pName)
{
	name = pName;
}

std::string ModelAuto::getName()
{
	return name;
}

void ModelAuto::setPostion(Position pPosition)
{
	position.x = pPosition.x;
	position.y = pPosition.y;
	position.angle = pPosition.angle;
}

Position ModelAuto::getPosition()
{
	return position;
}


Position ModelAuto::move(float pAngle, int pMovement)
{
	Position temp;

	
	temp.angle = TURNING_RATIO*handling * pAngle + position.angle;
	temp.x = sin(temp.angle * PI / 180) * pMovement * MOVEMENT_RATIO * speed + position.x;
	temp.y = cos(temp.angle * PI / 180) * pMovement * MOVEMENT_RATIO * speed + position.y;

	return temp;
}


/**
 * Lit l'auto dans à partir d'un stream
 * Format: Name speed handling
 */
std::istream& operator>>(std::istream& i, ModelAuto& c){
	std::string pName;
	int pSpeed, pHandling;
	i >> pName >> pSpeed >> pHandling;

	c.setName(pName);
	c.setSpeed(pSpeed);
	c.setHandling(pHandling);

	return i;
}