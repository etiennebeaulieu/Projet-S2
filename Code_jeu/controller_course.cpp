#include "controller_course.h"
#include <iostream>

Controller_course::Controller_course()
{
	Controller_course(Model_auto(), ModelCircuit());
}

Controller_course::Controller_course(Model_auto pCar, ModelCircuit pCircuit)
{
	car = pCar;
	circuit = pCircuit;


	cout << circuit;
	demoConsole();
}

Controller_course::~Controller_course()
{
}

void Controller_course::setAuto(Model_auto pCar)
{
	car = pCar;
}

Model_auto Controller_course::getAuto()
{
	return car;
}

void Controller_course::setCircuit(ModelCircuit pCircuit)
{
	circuit = pCircuit;
}

ModelCircuit Controller_course::getCircuit()
{
	return circuit;
}

void Controller_course::startRace()
{
	Position start =  circuit.getStart();
	car.setPostion(start);

	demoConsole();
}

void Controller_course::move(float pAngle, int pMovement)
{
	Position temp = car.move(pAngle, pMovement);

	if (circuit.positionIsActive(temp)) {
		
		cout << " ";
		car.setPostion(temp);
	}
		

	updateScreenConsole();
}

void Controller_course::updateScreenConsole()
{
	gotoXY(car.getPosition().x, car.getPosition().y);
	cout << "$";
}

void Controller_course::updateScreenGUI()
{
}

void Controller_course::gotoXY(int x, int y)
{
	COORD scrn;
	HANDLE houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = x;
	scrn.Y = y;
	SetConsoleCursorPosition(houtput, scrn);
}

void Controller_course::demoConsole()
{
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);

	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);

	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);

	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);

	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);

	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);

	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);

	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);

	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);

	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
	move(0, 1);
}




