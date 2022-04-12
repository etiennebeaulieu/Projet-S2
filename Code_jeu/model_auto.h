#ifndef MODEL_AUTO_H
#define MODEL_AUTO_H

#include <string>
#include <math.h>
#include <iostream>
#include "position.h"



const float  PI = 3.14159265358979f;
const int DEFAULT_SPEED = 1;
const int DEFAULT_HANDLING = 1;
const std::string DEFAULT_NAME = "auto_base";

const float TURNING_RATIO = 0.1;
const float MOVEMENT_RATIO = 10;

class ModelAuto {


public :
	ModelAuto();
	ModelAuto(int pSpeed, int pHandling, std::string pName);
	~ModelAuto();

	void setSpeed(int pSpeed);
	int getSpeed();
	void setHandling(int pHandling);
	int getHandling();
	void setName(std::string pName);
	std::string getName();
	void setPostion(Position pPosition);
	Position getPosition();
	


	Position move(float pAngle, int pMovement);

	
	friend std::istream& operator>>(std::istream&, ModelAuto&);

private:
	std::string name;
	int speed;
	int handling;

	Position position;



};

#endif
