#include "controller_course.h"
#include <iostream>

Controller_course::Controller_course()
{
	ModelAuto* car = new ModelAuto();
	ModelCircuit* circuit = new ModelCircuit();
	Controller_course(car, circuit);
}

Controller_course::Controller_course(ModelAuto* pCar, ModelCircuit* pCircuit)
{
	car = *pCar;
	circuit = *pCircuit;

	circuit.generateBorders();
}

Controller_course::~Controller_course()
{
}

void Controller_course::setAuto(ModelAuto pCar)
{
	car = pCar;
}

ModelAuto Controller_course::getAuto()
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
	std::cout << circuit << std::endl;
	car.setPostion(start);
	updateScreenConsole();

	demoConsole();
}

void Controller_course::move(float pAngle, int pMovement)
{
	Position temp = car.move(pAngle, pMovement);
	if (temp.x <= circuit.getWidth() && temp.y <= circuit.getHeight()) {
		if (circuit.positionIsActive(temp)) {
			gotoXY(round(car.getPosition().x), round(car.getPosition().y));
			std::cout << " ";
			car.setPostion(temp);
		}
	}
		

	updateScreenConsole();
}

void Controller_course::updateScreenConsole()
{
	gotoXY(round(car.getPosition().x), round(car.getPosition().y));
	std::cout << "*";
}

void Controller_course::updateScreenGUI()
{
}

void Controller_course::gotoXY(int x, int y)
{
	COORD scrn;
	HANDLE houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = 2*x;
	scrn.Y = y;
	SetConsoleCursorPosition(houtput, scrn);
}

void Controller_course::demoConsole()
{
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	
	

	move(-45, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(-45, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);

	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);

	move(-45, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(-45, 1);
	Sleep(100);


	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	

	move(-45, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(-45, 1);
	Sleep(100);


	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);


	move(-45, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(-45, 1);
	Sleep(100);


	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(100);
	move(0, 1);
	Sleep(5000);
	

}




